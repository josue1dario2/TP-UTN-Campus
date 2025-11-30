#include "MenuAbmCorrelativa.h"
#include "ArchivoMateria.h"
#include "Materia.h"
#include "utils.h"
#include "Validacion.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

MenuAbmCorrelativa::MenuAbmCorrelativa()
    : _archivo("Correlativas.dat") {}

void MenuAbmCorrelativa::mostrar() {
    int opc;
    do {
        clearScreen();
        cout << "\n=== ABM DE CORRELATIVAS ===\n";
        mostrarOpciones();
        opc = seleccionarOpcion();
        clearScreen();

        switch (opc) {
            case 1: agregarCorrelativa(); break;
            case 2: listarCorrelativas(); break;
            case 3: modificarCorrelativa(); break;
            case 4: bajaLogica(); break;
            case 0: cout << "\nVolviendo...\n"; break;
        }

        pauseScreen();
    } while (opc != 0);
}

void MenuAbmCorrelativa::mostrarOpciones() {
    cout << "\t1) Agregar correlativa\n";
    cout << "\t2) Listar correlativas\n";
    cout << "\t3) Modificar correlativa\n";
    cout << "\t4) Dar de baja correlativa\n";
    cout << "\t0) Volver\n";
    cout << "\t---------------------------\n";
}

int MenuAbmCorrelativa::seleccionarOpcion() {
    return Validacion::validarEnteroEnRango("\tOpción: ", 0, 4);
}

void MenuAbmCorrelativa::agregarCorrelativa() {

    cout << "\n=== Agregar Correlativa ===\n";

    int idObj;
    cout << "Ingrese el ID de la Materia: ";
    cin >> idObj;

    ArchivoMateria archMat("Materias.dat");
    int posObj = archMat.buscarRegistro(idObj);
    if (posObj < 0) {
        cout << "\nLa materia objetivo no existe.\n";
        return;
    }

    int total = _archivo.contarRegistros();
    int usadas = 0;

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateriaObjetivo() == idObj) {
            usadas++;
        }
    }

    if (usadas >= 4) {
        cout << "\nLa materia ya tiene el máximo (4) correlativas.\n";
        return;
    }

    bool seguir = true;
    while (seguir && usadas < 4) {

        int idReq;
        cout <<"Ingrese el ID de la correlativa : ";
        cin >> idReq;

        int posReq = archMat.buscarRegistro(idReq);
        if (posReq < 0) {
            cout << "\nLa materia requisito no existe.\n";
            continue;
        }

        bool yaExiste = false;
        for (int i = 0; i < total; i++) {
            Correlativa c = _archivo.leerRegistro(i);
            if (!c.getEliminado() &&
                c.getIdMateriaObjetivo() == idObj &&
                c.getIdMateriaRequisito() == idReq) {
                yaExiste = true;
                break;
            }
        }

        if (yaExiste) {
            cout << "\nEsa correlativa ya está cargada.\n";
        } else {
            Correlativa nuevo(idObj, idReq, false);

            if (_archivo.agregarRegistro(nuevo) == 1) {
                cout << "\nCorrelativa agregada correctamente.\n";
                usadas++;
            } else {
                cout << "\nError al agregar correlativa.\n";
            }
        }

        if (usadas >= 4) {
            cout << "\n¡Se alcanzó el máximo de 4 correlativas!\n";
            break;
        }

        char opc;
        cout << "\n¿Desea agregar otra correlativa? (s/n): ";
        cin >> opc;

        if (opc != 's' && opc != 'S') seguir = false;
    }
}


void MenuAbmCorrelativa::listarCorrelativas() {

    const int ANCHO_MAT = 47;
    const int ANCHO_COR = 47;

    cout << "\n    +------+-----------------------------------------------+------+-----------------------------------------------+\n";
    cout << "    |  ID  | MATERIA                                       |  ID  | CORRELATIVAS                                  |\n";
    cout << "    +------+-----------------------------------------------+------+-----------------------------------------------+\n";

    ArchivoMateria archMaterias("Materias.dat");
    int totalMaterias = archMaterias.contarRegistros();

    for (int i = 0; i < totalMaterias; i++) {

        Materia mat = archMaterias.leerRegistro(i);
        if (mat.getEliminado()) continue;

        string nombreMat = quitarAcentos(mat.getNombre());
        if (nombreMat.length() > 45) nombreMat = nombreMat.substr(0, 44) + "...";

        bool tiene = false;
        bool primera = true;

        int totalCor = _archivo.contarRegistros();

        for (int j = 0; j < totalCor; j++) {

            Correlativa c = _archivo.leerRegistro(j);
            if (!c.getEliminado() && c.getIdMateriaObjetivo() == mat.getIdMateria()) {

                tiene = true;

                int posReq = archMaterias.buscarRegistro(c.getIdMateriaRequisito());
                string nomReq = "No encontrada";

                if (posReq >= 0) {
                    Materia mr = archMaterias.leerRegistro(posReq);
                    nomReq = quitarAcentos(mr.getNombre());
                }
                if (nomReq.length() > 45) nomReq = nomReq.substr(0, 44) + "...";

                if (primera) {
                    printf("    | %4d | %-45s | %4d | %-45s |\n",
                           mat.getIdMateria(),
                           nombreMat.c_str(),
                           c.getIdMateriaRequisito(),
                           nomReq.c_str());
                    primera = false;
                } else {
                    printf("    |      | %-45s | %4d | %-45s |\n",
                           "",
                           c.getIdMateriaRequisito(),
                           nomReq.c_str());
                }
            }
        }

        if (!tiene) {
            printf("    | %4d | %-45s |      | %-45s |\n",
                   mat.getIdMateria(),
                   nombreMat.c_str(),
                   "Sin correlativas");
        }

        cout << "    +------+-----------------------------------------------+------+-----------------------------------------------+\n";
    }
}

void MenuAbmCorrelativa::modificarCorrelativa() {
    cout << "\n=== Modificar Correlativas ===\n";

    ArchivoMateria archMaterias("Materias.dat");

    // === VALIDAR ID MATERIA OBJETIVO ===
    int idObj = Validacion::validarEntero("\tIngrese el ID de la Materia: ");
    int posMatObj = archMaterias.buscarRegistro(idObj);

    if (posMatObj < 0) {
        cout << "\n\tERROR: No existe una materia con ese ID.\n";
        return;
    }

    Materia matObj = archMaterias.leerRegistro(posMatObj);
    if (matObj.getEliminado()) {
        cout << "\n\tERROR: La materia está dada de baja.\n";
        return;
    }

    bool continuar = true;

    while (continuar)
    {
        // =======================================================
        // CARGAR CORRELATIVAS (MAX 4)
        // =======================================================
        int correlativas[4];
        int cant = 0;
        int total = _archivo.contarRegistros();

        for (int i = 0; i < total && cant < 4; i++) {
            Correlativa c = _archivo.leerRegistro(i);
            if (!c.getEliminado() && c.getIdMateriaObjetivo() == idObj) {
                correlativas[cant] = c.getIdMateriaRequisito();
                cant++;
            }
        }

        // Si no tiene correlativas → volver
        if (cant == 0) {
            cout << "\n(La materia NO tiene correlativas)\n";
            cout << "Volviendo al menu...\n";
            return;
        }

        // =======================================================
        // MOSTRAR INFO ACTUAL
        // =======================================================
        cout << "\n---------------------------------------------\n";
        cout << " Materia: " << idObj << " | " << quitarAcentos(matObj.getNombre()) << "\n";
        cout << "---------------------------------------------\n";

        cout << " Correlativas actuales:\n";
        cout << " -------------------------------------\n";

        for (int i = 0; i < cant; i++) {
            int posReq = archMaterias.buscarRegistro(correlativas[i]);
            Materia req = archMaterias.leerRegistro(posReq);
            cout << " - " << req.getIdMateria()
                 << " | " << quitarAcentos(req.getNombre()) << "\n";
        }

        cout << " -------------------------------------\n";

        // =======================================================
        // PEDIR CORRELATIVA A MODIFICAR
        // =======================================================
        int reqViejo = Validacion::validarEntero("\nIngrese el ID de correlativa a MODIFICAR: ");

        // Verificar que reqViejo realmente esté en correlativas[]
        bool existe = false;
        for (int i = 0; i < cant; i++) {
            if (correlativas[i] == reqViejo) existe = true;
        }

        if (!existe) {
            cout << "\nERROR: Esa correlativa NO existe.\n";
            continue;
        }

        // Buscar posición exacta en archivo
        int posCor = -1;
        total = _archivo.contarRegistros();
        for (int i = 0; i < total; i++) {
            Correlativa c = _archivo.leerRegistro(i);
            if (!c.getEliminado() &&
                c.getIdMateriaObjetivo() == idObj &&
                c.getIdMateriaRequisito() == reqViejo) {
                posCor = i;
                break;
            }
        }

        if (posCor < 0) {
            cout << "\nERROR inesperado.\n";
            continue;
        }

        // =======================================================
        // NUEVO ID
        // =======================================================
        int reqNuevo = Validacion::validarEntero("\tIngrese el nuevo ID de la correlativa: ");
        int posReqNuevo = archMaterias.buscarRegistro(reqNuevo);

        // === Validar existencia
        if (posReqNuevo < 0) {
            cout << "\n\tERROR: No existe una materia con ese ID.\n";
            continue;
        }

        // === Validar que no esté eliminada
        Materia matReqNuevo = archMaterias.leerRegistro(posReqNuevo);
        if (matReqNuevo.getEliminado()) {
            cout << "\n\tERROR: Esa materia está dada de baja.\n";
            continue;
        }

        // === No puede ser la misma materia
        if (reqNuevo == idObj) {
            cout << "\n\tERROR: Una materia no puede ser correlativa de sí misma.\n";
            continue;
        }

        // === EVITAR DUPLICADOS
        bool duplicado = false;
        for (int i = 0; i < cant; i++) {
            if (correlativas[i] == reqNuevo) {
                duplicado = true;
                break;
            }
        }

        if (duplicado) {
            cout << "\n\tERROR: Esa correlativa YA está cargada.\n";
            continue;
        }

        // =======================================================
        // GUARDAR MODIFICACIÓN
        // =======================================================
        Correlativa c = _archivo.leerRegistro(posCor);
        c.setIdMateriaRequisito(reqNuevo);

        if (_archivo.modificarRegistro(c, posCor))
            cout << "\n✓ Correlativa modificada correctamente.\n";
        else
            cout << "\n✗ Error al modificar correlativa.\n";

        // =======================================================
        // ¿SEGUIR MODIFICANDO?
        // =======================================================
        char opc;
        cout << "\n¿Desea modificar otra correlativa? (s/n): ";
        cin >> opc;

        if (opc != 's' && opc != 'S') {
            continuar = false;
        }
    }
}


void MenuAbmCorrelativa::bajaLogica() {
    cout << "\n=== Baja de Correlativas ===\n";

    ArchivoMateria archMaterias("Materias.dat");

    int idObj = Validacion::validarEntero("\tIngrese el ID de la Materia: ");
    int posMatObj = archMaterias.buscarRegistro(idObj);

    if (posMatObj < 0) {
        cout << "\n\tERROR: No existe una materia con ese ID.\n";
        return;
    }

    Materia matObj = archMaterias.leerRegistro(posMatObj);
    if (matObj.getEliminado()) {
        cout << "\n\tERROR: La materia está dada de baja.\n";
        return;
    }

    bool continuar = true;

    while (continuar) {

        // CARGAR CORRELATIVAS EN ARRAY
        int correlativas[4];
        int cant = 0;

        int total = _archivo.contarRegistros();
        for (int i = 0; i < total && cant < 4; i++) {
            Correlativa c = _archivo.leerRegistro(i);
            if (!c.getEliminado() && c.getIdMateriaObjetivo() == idObj) {
                correlativas[cant] = c.getIdMateriaRequisito();
                cant++;
            }
        }

        if (cant == 0) {
            cout << "\n(La materia NO tiene correlativas)\n";
            cout << "Volviendo al menu...\n";
            return;
        }

        // MOSTRAR LA MATERIA Y SUS CORRELATIVAS
        cout << "\n---------------------------------------------\n";
        cout << " Materia: " << idObj << " | " << quitarAcentos(matObj.getNombre()) << "\n";
        cout << "---------------------------------------------\n";

        cout << " Correlativas actuales:\n";
        cout << " -------------------------------------\n";

        for (int i = 0; i < cant; i++) {
            int posReq = archMaterias.buscarRegistro(correlativas[i]);
            Materia req = archMaterias.leerRegistro(posReq);

            cout << " - " << req.getIdMateria() << " | "
                 << quitarAcentos(req.getNombre()) << "\n";
        }

        cout << " -------------------------------------\n";

        int idReq = Validacion::validarEntero("\nIngrese el ID de correlativa a borrar: ");

        int posToDelete = -1;
        for (int i = 0; i < total; i++) {
            Correlativa c = _archivo.leerRegistro(i);
            if (!c.getEliminado() &&
                c.getIdMateriaObjetivo() == idObj &&
                c.getIdMateriaRequisito() == idReq) {
                posToDelete = i;
                break;
            }
        }

        if (posToDelete < 0) {
            cout << "\nERROR: Esa correlativa NO existe.\n";
            continue;
        }

        if (_archivo.bajaLogica(posToDelete))
            cout << "\nCorrelativa eliminada correctamente.\n";
        else
            cout << "\nError al procesar baja.\n";

        // Ver si quedan correlativas
        bool quedan = false;
        total = _archivo.contarRegistros();

        for (int i = 0; i < total; i++) {
            Correlativa c = _archivo.leerRegistro(i);
            if (!c.getEliminado() && c.getIdMateriaObjetivo() == idObj) {
                quedan = true;
                break;
            }
        }

        if (!quedan) {
            cout << "\n(La materia ya no tiene correlativas)\n";
            cout << "Volviendo al menu...\n";
            return;
        }

        char opc;
        cout << "\n¿Desea borrar otra correlativa? (s/n): ";
        cin >> opc;

        if (opc != 's' && opc != 'S') continuar = false;
    }
}


