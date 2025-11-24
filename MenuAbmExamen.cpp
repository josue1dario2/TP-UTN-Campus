#include "MenuAbmExamen.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
using namespace std;

MenuAbmExamen::MenuAbmExamen() {
    _cantidadOpciones = 6;
}

void MenuAbmExamen::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuAbmExamen::mostrarOpciones() {
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

int MenuAbmExamen::seleccionOpcion() {
    mostrarOpciones();
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAbmExamen::ejecutarOpcion(int opcion) {
    int legajo, idComision, numeroParcial, nota;

    switch (opcion) {

        case 1:
            legajo = Validacion::validarEntero("\n\tLegajo del alumno: ");
            idComision = Validacion::validarEntero("\tID de comision: ");
            nota = Validacion::validarEnteroEnRango("\tNota (0-10): ", 0, 10);
            _managerExamen.cargarParcial(legajo, idComision, nota);
            break;

        case 2:
            legajo = Validacion::validarEntero("\n\tLegajo del alumno: ");
            idComision = Validacion::validarEntero("\tID de comision: ");
            nota = Validacion::validarEnteroEnRango("\tNota (0-10): ", 0, 10);
            _managerExamen.cargarRecuperatorio(legajo, idComision, nota);
            break;

        case 3:
            legajo = Validacion::validarEntero("\n\tLegajo del alumno: ");
            idComision = Validacion::validarEntero("\tID de comision: ");
            nota = Validacion::validarEnteroEnRango("\tNota (0-10): ", 0, 10);
            _managerExamen.cargarFinal(legajo, idComision, nota);
            break;

        case 4:
            legajo = Validacion::validarEntero("\n\tLegajo del alumno: ");
            _managerExamen.mostrarHistorial(legajo);
            break;

        case 5:
            legajo = Validacion::validarEntero("\n\tLegajo del alumno: ");
            idComision = Validacion::validarEntero("\tID de comision: ");
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
