#include "MenuAbmCorrelativa.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
using namespace std;

MenuAbmCorrelativa::MenuAbmCorrelativa() {}

void MenuAbmCorrelativa::mostrar() {
    int opc;
    do {
        clearScreen();

        cout << "\n=== ABM DE CORRELATIVAS ===\n";
        mostrarOpciones();

        opc = seleccionarOpcion();
        clearScreen();

        switch (opc) {
            case 1: _manager.agregar(); break;
            case 2: _manager.listar(); break;
            case 3: _manager.modificar(); break;
            case 4: _manager.borrar(); break;
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
