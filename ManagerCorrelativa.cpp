#include <limits>
#include "ManagerCorrelativa.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

ManagerCorrelativa::ManagerCorrelativa()
    : _archivo("Correlativas.dat"), _archMat("Materias.dat") {}


// ===================== VALIDACIONES ===============================

bool ManagerCorrelativa::existeMateria(int id) {
    return _archMat.buscarRegistro(id) >= 0;
}

bool ManagerCorrelativa::materiaEliminada(int id) {
    int pos = _archMat.buscarRegistro(id);
    if (pos < 0) return true;
    return _archMat.leerRegistro(pos).getEliminado();
}

bool ManagerCorrelativa::existeCorrelativa(int idObj, int idReq) {
    int total = _archivo.contarRegistros();
    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (!c.getEliminado() &&
            c.getIdMateriaObjetivo() == idObj &&
            c.getIdMateriaRequisito() == idReq)
            return true;
    }
    return false;
}

int ManagerCorrelativa::buscarPosCorrelativa(int idObj, int idReq) {
    int total = _archivo.contarRegistros();
    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (!c.getEliminado() &&
            c.getIdMateriaObjetivo() == idObj &&
            c.getIdMateriaRequisito() == idReq)
            return i;
    }
    return -1;
}

int ManagerCorrelativa::contarCorrelativas(int idObj) {
    int total = _archivo.contarRegistros();
    int cant = 0;
    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateriaObjetivo() == idObj)
            cant++;
    }
    return cant;
}


// ===================== LISTADOS AUXILIARES ===============================

void ManagerCorrelativa::listarMateriasActivas(const string& titulo) {
    cout << "\n=== " << titulo << " ===\n";
    int total = _archMat.contarRegistros();

    for (int i = 0; i < total; i++) {
        Materia m = _archMat.leerRegistro(i);
        if (!m.getEliminado()) {
            cout << "   ID: " << m.getIdMateria()
                 << " | " << quitarAcentos(m.getNombre()) << "\n";
        }
    }
}

void ManagerCorrelativa::listarCorrelativasDeMateria(int idObj) {
    cout << "\n=== CORRELATIVAS DE LA MATERIA ===\n";
    int totalCor = _archivo.contarRegistros();

    for (int j = 0; j < totalCor; j++) {
        Correlativa c = _archivo.leerRegistro(j);

        if (!c.getEliminado() && c.getIdMateriaObjetivo() == idObj) {
            int idReq = c.getIdMateriaRequisito();
            int posReq = _archMat.buscarRegistro(idReq);

            string nomReq = "No encontrada";
            if (posReq >= 0) {
                nomReq = quitarAcentos(_archMat.leerRegistro(posReq).getNombre());
            }

            cout << "   ID Req: " << idReq << " | " << nomReq << "\n";
        }
    }
}

int ManagerCorrelativa::pedirMateriaValida(const string& mensaje) {
    int id = Validacion::validarEntero(mensaje);

    if (!existeMateria(id)) {
        cout << "\nERROR: La materia no existe.\n";
        return -1;
    }
    if (materiaEliminada(id)) {
        cout << "\nERROR: La materia está dada de baja.\n";
        return -1;
    }
    return id;
}

int ManagerCorrelativa::pedirCorrelativaValida(int idObj, const string& mensaje) {
    int idReq = Validacion::validarEntero(mensaje);

    if (!existeMateria(idReq)) {
        cout << "\nERROR: No existe esa materia.\n";
        return -1;
    }
    if (materiaEliminada(idReq)) {
        cout << "\nERROR: La materia requisito está dada de baja.\n";
        return -1;
    }
    if (idReq == idObj) {
        cout << "\nERROR: No puede ser igual a la materia objetivo.\n";
        return -1;
    }
    if (existeCorrelativa(idObj, idReq)) {
        cout << "\nERROR: Esa correlativa ya está cargada.\n";
        return -1;
    }
    return idReq;
}


// ===================== AGREGAR ===============================

void ManagerCorrelativa::agregar() {
    cout << "\n=== AGREGAR CORRELATIVA ===\n";

    listarMateriasActivas("MATERIAS ACTIVAS");

    int idObj = pedirMateriaValida("\nIngrese el ID de la materia: ");
    if (idObj < 0) return;

    int usadas = contarCorrelativas(idObj);

    if (usadas >= 4) {
        cout << "\nERROR: La materia ya tiene el máximo (4) correlativas.\n";
        return;
    }

    bool seguir = true;

    while (seguir) {

        // Actualizar cantidad cada vez por si hubo cambios
        usadas = contarCorrelativas(idObj);
        if (usadas >= 4) {
            cout << "\nLa materia YA alcanzó el máximo de 4 correlativas.\n";
            break;
        }

        listarMateriasActivas("MATERIAS DISPONIBLES COMO REQUISITO");

        int idReq = pedirCorrelativaValida(idObj, "\nIngrese ID de la correlativa: ");
        if (idReq < 0) continue;

        Correlativa nueva(idObj, idReq, false);

        if (_archivo.agregarRegistro(nueva) == 1) {
            cout << "\nCorrelativa agregada correctamente.\n";
        } else {
            cout << "\nERROR al guardar correlativa.\n";
        }

        // Volvemos a evaluar después de insertar
        usadas = contarCorrelativas(idObj);

        if (usadas >= 4) {
            cout << "\nSe alcanzó el límite de 4 correlativas permitidas.\n";
            break;
        }

        char opc;
        cout << "\n¿Desea agregar otra correlativa? (s/n): ";
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opc != 's' && opc != 'S')
            seguir = false;
    }
}

// ===================== LISTAR ===============================

void ManagerCorrelativa::listar() {
    cout << "\n=== LISTA DE CORRELATIVAS ===\n";

    int totalMat = _archMat.contarRegistros();
    int totalCor = _archivo.contarRegistros();

    cout << "+------+----------------------------------------+------+----------------------------------------+\n";
    cout << "| ID   | MATERIA                                | ID   | CORRELATIVA                            |\n";
    cout << "+------+----------------------------------------+------+----------------------------------------+\n";

    for (int i = 0; i < totalMat; i++) {

        Materia mat = _archMat.leerRegistro(i);
        if (mat.getEliminado()) continue;

        string matNom = quitarAcentos(mat.getNombre());
        if (matNom.length() > 38) matNom = matNom.substr(0, 37) + "...";

        bool primera = true;
        bool tieneCor = false;

        for (int j = 0; j < totalCor; j++) {

            Correlativa c = _archivo.leerRegistro(j);
            if (c.getEliminado()) continue;
            if (c.getIdMateriaObjetivo() != mat.getIdMateria()) continue;

            tieneCor = true;

            int idReq = c.getIdMateriaRequisito();
            int posReq = _archMat.buscarRegistro(idReq);

            string nomReq = "No encontrada";
            if (posReq >= 0)
                nomReq = quitarAcentos(_archMat.leerRegistro(posReq).getNombre());

            if (nomReq.length() > 38) nomReq = nomReq.substr(0, 37) + "...";

            cout << "| " << setw(4) << left << (primera ? to_string(mat.getIdMateria()) : "")
                 << " | " << setw(38) << left << (primera ? matNom : "")
                 << " | " << setw(4) << left << idReq
                 << " | " << setw(38) << left << nomReq
                 << " |\n";

            primera = false;
        }

        if (!tieneCor) {
            cout << "| " << setw(4) << left << mat.getIdMateria()
                 << " | " << setw(38) << left << matNom
                 << " | " << setw(4) << left << ""
                 << " | " << setw(38) << left << "Sin correlativas"
                 << " |\n";
        }

        cout << "+------+----------------------------------------+------+----------------------------------------+\n";
    }
}


// ===================== MODIFICAR ===============================

void ManagerCorrelativa::modificar() {
    cout << "\n=== MODIFICAR CORRELATIVA ===\n";

    listarMateriasActivas("MATERIAS DISPONIBLES");

    int idObj = pedirMateriaValida("\nIngrese ID de la materia: ");
    if (idObj < 0) return;

    if (contarCorrelativas(idObj) == 0) {
        cout << "\tLa materia NO tiene correlativas.\n";
        return;
    }

    bool seguir = true;

    while (seguir) {

        listarCorrelativasDeMateria(idObj);

        int idViejo = Validacion::validarEntero("\nIngrese ID correlativa a modificar: ");

        int pos = buscarPosCorrelativa(idObj, idViejo);
        if (pos < 0) {
            cout << "\tERROR: Esa correlativa no existe.\n";
            continue;
        }

        int idNuevo = pedirCorrelativaValida(idObj, "\tNuevo ID requisito: ");
        if (idNuevo < 0) continue;

        Correlativa c = _archivo.leerRegistro(pos);
        c.setIdMateriaRequisito(idNuevo);

        if (_archivo.modificarRegistro(c, pos))
            cout << "\tCorrelativa modificada con éxito.\n";
        else
            cout << "\tERROR al modificar.\n";

        char opc;
        cout << "\n¿Desea modificar otra correlativa? (s/n): ";
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opc != 's' && opc != 'S') seguir = false;
    }
}


// ===================== BORRAR ===============================

void ManagerCorrelativa::borrar() {
    cout << "\n=== BORRAR CORRELATIVA ===\n";

    listarMateriasActivas("MATERIAS ACTIVAS");

    int idObj = pedirMateriaValida("\nIngrese ID de la materia: ");
    if (idObj < 0) return;

    if (contarCorrelativas(idObj) == 0) {
        cout << "\tLa materia NO tiene correlativas.\n";
        return;
    }

    bool seguir = true;

    while (seguir) {

        listarCorrelativasDeMateria(idObj);

        int idReq = Validacion::validarEntero("\nIngrese ID correlativa a borrar: ");

        int pos = buscarPosCorrelativa(idObj, idReq);

        if (pos < 0) {
            cout << "\tERROR: Esa correlativa no existe.\n";
        } else {
            if (_archivo.bajaLogica(pos))
                cout << "\tCorrelativa eliminada.\n";
            else
                cout << "\tERROR al eliminar.\n";
        }

        if (contarCorrelativas(idObj) == 0) {
            cout << "\nLa materia ya NO tiene más correlativas.\n";
            break;
        }

        char opc;
        cout << "\n¿Desea borrar otra correlativa? (s/n): ";
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opc != 's' && opc != 'S') seguir = false;
    }
}


// ===================== UTILIDAD PARA INSCRIPCIÓN ===============================

bool ManagerCorrelativa::tieneCorrelativas(int idMateria) {
    int total = _archivo.contarRegistros();

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);

        if (!c.getEliminado() &&
            c.getIdMateriaObjetivo() == idMateria)
            return true;
    }
    return false;
}
