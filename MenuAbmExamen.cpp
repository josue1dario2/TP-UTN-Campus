#include "MenuAbmExamen.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
using namespace std;

MenuABMExamen::MenuABMExamen() {
    _cantidadOpciones = 6;
}

void MenuABMExamen::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMExamen::mostrarOpciones() {
    cout << endl;
    cout << "\n\t=== ABM DE EXÁMENES ===\n";
    cout << "\t-------------------------------------------\n";
    cout << "\t1) Cargar Parcial\n";
    cout << "\t2) Cargar Recuperatorio\n";
    cout << "\t3) Cargar Final\n";
    cout << "\t4) Listar Exámenes por Alumno\n";
    cout << "\t5) Recalcular Condición Académica\n";
    cout << "\t6) Mostrar Todos los Exámenes\n";
    cout << "\t0) Volver\n";
    cout << "\t-------------------------------------------\n";
}

int MenuABMExamen::seleccionOpcion() {
    mostrarOpciones();
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuABMExamen::ejecutarOpcion(int opcion) {
    int legajo, idComision, numeroParcial, nota;

    switch (opcion) {

        case 1:
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            cout << "ID de comisión: ";
            cin >> idComision;
            cout << "Número de parcial (1-3): ";
            cin >> numeroParcial;
            cout << "Nota (0-10): ";
            cin >> nota;
            _managerExamen.cargarParcial(legajo, idComision, numeroParcial, nota);
            break;

        case 2:
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            cout << "ID de comisión: ";
            cin >> idComision;
            cout << "Número de parcial (1-3): ";
            cin >> numeroParcial;
            cout << "Nota (0-10): ";
            cin >> nota;
            _managerExamen.cargarRecuperatorio(legajo, idComision, numeroParcial, nota);
            break;

        case 3:
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            cout << "ID de comisión: ";
            cin >> idComision;
            cout << "Nota (0-10): ";
            cin >> nota;
            _managerExamen.cargarFinal(legajo, idComision, nota);
            break;

        case 4:
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            _managerExamen.mostrarHistorial(legajo);
            break;

        case 5:
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            cout << "ID de comisión: ";
            cin >> idComision;
            _managerExamen.recalcularCondicion(legajo, idComision);
            break;

        case 6:
            _managerExamen.mostrarTodos();
            break;

        case 0:
            cout << "Volviendo...\n";
            break;
    }
}
