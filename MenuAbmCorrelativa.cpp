#include "MenuAbmCorrelativa.h"
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

    int idMatObj = Validacion::validarEntero("\tID Materia OBJETIVO: ");
    int idMatReq = Validacion::validarEntero("\tID Materia REQUISITO: ");

    if (idMatObj == idMatReq) {
        cout << "\nUna materia no puede ser correlativa de sí misma.\n";
        return;
    }

    Correlativa c(idMatObj, idMatReq);

    if (_archivo.agregarRegistro(c))
        cout << "\nCorrelativa agregada.\n";
    else
        cout << "\nError al agregar.\n";
}

void MenuAbmCorrelativa::listarCorrelativas() {
    cout << "\n=== LISTADO DE CORRELATIVAS ===\n";

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

    int idObj = Validacion::validarEntero("\tID Materia OBJETIVO: ");
    int reqViejo = Validacion::validarEntero("\tID Materia REQUISITO a modificar: ");

    int total = _archivo.contarRegistros();
    int pos = -1;

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (c.getIdMateriaObjetivo() == idObj &&
            c.getIdMateriaRequisito() == reqViejo) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "\nNo existe esa correlativa.\n";
        return;
    }

    int reqNuevo = Validacion::validarEntero("\tNuevo ID Materia requisito: ");

    if (reqNuevo == idObj) {
        cout << "\nUna materia no puede ser correlativa de sí misma.\n";
        return;
    }

    Correlativa c = _archivo.leerRegistro(pos);
    c.setIdMateriaRequisito(reqNuevo);

    if (_archivo.modificarRegistro(c, pos))
        cout << "\nCorrelativa modificada.\n";
    else
        cout << "\nError al modificar.\n";
}

void MenuAbmCorrelativa::bajaLogica() {
    cout << "\n=== Baja de Correlativa ===\n";

    int idObj = Validacion::validarEntero("\tID Materia OBJETIVO: ");
    int req = Validacion::validarEntero("\tID Materia REQUISITO a dar de baja: ");

    int total = _archivo.contarRegistros();
    int pos = -1;

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (c.getIdMateriaObjetivo() == idObj &&
            c.getIdMateriaRequisito() == req) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        cout << "\nNo existe correlativa para dar de baja.\n";
        return;
    }

    if (_archivo.bajaLogica(pos))
        cout << "\nCorrelativa dada de baja.\n";
    else
        cout << "\nError al procesar baja.\n";
}
