#include "MenuAbmCorrelativa.h"
#include "ArchivoMateria.h"
#include "Materia.h"
#include "utils.h"
#include "Validacion.h"
#include <iostream>
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

    ArchivoMateria archMaterias("Materias.dat");

    // Validar ID Materia Objetivo
    int idMatObj = Validacion::validarEntero("\tID Materia OBJETIVO: ");
    int posObj = archMaterias.buscarRegistro(idMatObj);

    if (posObj < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << idMatObj << ".\n";
        return;
    }

    Materia matObj = archMaterias.leerRegistro(posObj);
    if (matObj.getEliminado()) {
        cout << "\n\tERROR: La materia con ID " << idMatObj << " está dada de baja.\n";
        return;
    }

    // Validar ID Materia Requisito
    int idMatReq = Validacion::validarEntero("\tID Materia REQUISITO: ");
    int posReq = archMaterias.buscarRegistro(idMatReq);

    if (posReq < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << idMatReq << ".\n";
        return;
    }

    Materia matReq = archMaterias.leerRegistro(posReq);
    if (matReq.getEliminado()) {
        cout << "\n\tERROR: La materia con ID " << idMatReq << " está dada de baja.\n";
        return;
    }

    if (idMatObj == idMatReq) {
        cout << "\n\tERROR: Una materia no puede ser correlativa de sí misma.\n";
        return;
    }

    Correlativa c(idMatObj, idMatReq);

    if (_archivo.agregarRegistro(c))
        cout << "\n\t✓ Correlativa agregada correctamente.\n";
    else
        cout << "\n\t✗ Error al agregar correlativa.\n";
}

void MenuAbmCorrelativa::listarCorrelativas() {
    cout << "\n\t=== LISTADO DE CORRELATIVAS ===\n";

    int total = _archivo.contarRegistros();

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);

        if (!c.getEliminado()) {
            cout << "\tMateria OBJ: " << c.getIdMateriaObjetivo()
                 << "  |  Requisito: " << c.getIdMateriaRequisito()
                 << endl;
        }
    }
}

void MenuAbmCorrelativa::modificarCorrelativa() {
    cout << "\n=== Modificar Correlativa ===\n";

    ArchivoMateria archMaterias("Materias.dat");

    // Validar ID Materia Objetivo
    int idObj = Validacion::validarEntero("\tID Materia OBJETIVO: ");
    int posMatObj = archMaterias.buscarRegistro(idObj);

    if (posMatObj < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << idObj << ".\n";
        return;
    }

    Materia matObj = archMaterias.leerRegistro(posMatObj);
    if (matObj.getEliminado()) {
        cout << "\n\tERROR: La materia con ID " << idObj << " está dada de baja.\n";
        return;
    }

    // Validar ID Materia Requisito Viejo
    int reqViejo = Validacion::validarEntero("\tID Materia REQUISITO a modificar: ");
    int posReqViejo = archMaterias.buscarRegistro(reqViejo);

    if (posReqViejo < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << reqViejo << ".\n";
        return;
    }

    // Buscar la correlativa
    int total = _archivo.contarRegistros();
    int pos = -1;

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (c.getIdMateriaObjetivo() == idObj &&
            c.getIdMateriaRequisito() == reqViejo &&
            !c.getEliminado()) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "\n\tERROR: No existe esa correlativa.\n";
        return;
    }

    // Validar ID Materia Requisito Nuevo
    int reqNuevo = Validacion::validarEntero("\tNuevo ID Materia requisito: ");
    int posReqNuevo = archMaterias.buscarRegistro(reqNuevo);

    if (posReqNuevo < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << reqNuevo << ".\n";
        return;
    }

    Materia matReqNuevo = archMaterias.leerRegistro(posReqNuevo);
    if (matReqNuevo.getEliminado()) {
        cout << "\n\tERROR: La materia con ID " << reqNuevo << " está dada de baja.\n";
        return;
    }

    if (reqNuevo == idObj) {
        cout << "\n\tERROR: Una materia no puede ser correlativa de sí misma.\n";
        return;
    }

    Correlativa c = _archivo.leerRegistro(pos);
    c.setIdMateriaRequisito(reqNuevo);

    if (_archivo.modificarRegistro(c, pos))
        cout << "\n\t✓ Correlativa modificada correctamente.\n";
    else
        cout << "\n\t✗ Error al modificar correlativa.\n";
}

void MenuAbmCorrelativa::bajaLogica() {
    cout << "\n=== Baja de Correlativa ===\n";

    ArchivoMateria archMaterias("Materias.dat");

    // Validar ID Materia Objetivo
    int idObj = Validacion::validarEntero("\tID Materia OBJETIVO: ");
    int posMatObj = archMaterias.buscarRegistro(idObj);

    if (posMatObj < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << idObj << ".\n";
        return;
    }

    Materia matObj = archMaterias.leerRegistro(posMatObj);
    if (matObj.getEliminado()) {
        cout << "\n\tERROR: La materia con ID " << idObj << " está dada de baja.\n";
        return;
    }

    // Validar ID Materia Requisito
    int req = Validacion::validarEntero("\tID Materia REQUISITO a dar de baja: ");
    int posReq = archMaterias.buscarRegistro(req);

    if (posReq < 0) {
        cout << "\n\tERROR: No existe una materia con el ID " << req << ".\n";
        return;
    }

    // Buscar la correlativa
    int total = _archivo.contarRegistros();
    int pos = -1;

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (c.getIdMateriaObjetivo() == idObj &&
            c.getIdMateriaRequisito() == req &&
            !c.getEliminado()) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "\n\tERROR: No existe correlativa para dar de baja.\n";
        return;
    }

    if (_archivo.bajaLogica(pos))
        cout << "\n\t✓ Correlativa dada de baja correctamente.\n";
    else
        cout << "\n\t✗ Error al procesar baja.\n";
}
