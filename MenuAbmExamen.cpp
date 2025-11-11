#include "MenuABMExamen.h"
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
    int opcion;
    mostrarOpciones();
    cout << "\tOpción: ";
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
    return opcion;
}

void MenuABMExamen::ejecutarOpcion(int opcion) {
    int legajo, idComision, numeroParcial, nota;

    switch (opcion) {
        case 1: // Cargar parcial
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

        case 2: // Cargar recuperatorio
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

        case 3: // Cargar final
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            cout << "ID de comisión: ";
            cin >> idComision;
            cout << "Nota (0-10): ";
            cin >> nota;
            _managerExamen.cargarFinal(legajo, idComision, nota);
            break;

        case 4: // Listar exámenes por alumno
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            _managerExamen.mostrarHistorial(legajo);
            break;

        case 5: // Recalcular condición académica
            cout << "\nLegajo del alumno: ";
            cin >> legajo;
            cout << "ID de comisión: ";
            cin >> idComision;
            _managerExamen.recalcularCondicion(legajo, idComision);
            break;

        case 6: // Mostrar todos los exámenes en formato tabla
            _managerExamen.mostrarTodos();
            break;

        case 0:
            cout << "Volviendo al menú anterior...\n";
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}

void ManagerExamen::mostrarTodos() {
    int total = _archivoExamen.contarRegistros();
    if (total == 0) {
        cout << "No hay exámenes registrados.\n";
        return;
    }

    cout << "\n\t=== LISTADO GENERAL DE EXÁMENES ===\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (!ex.getEliminado()) {
            mostrarRegistro(ex);
        }
    }

    mostrarPie();
}
