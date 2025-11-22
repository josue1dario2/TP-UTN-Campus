#include "MenuAbmMaterias.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
using namespace std;

MenuABMMaterias::MenuABMMaterias() {
    _cantidadOpciones = 6;
}

void MenuABMMaterias::mostrarMenuABMMaterias() {
    int opcion;

    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 0) return;

        ejecutarOpcion(opcion);
        pauseScreen();

    } while (opcion != 0);
}

void MenuABMMaterias::mostrarOpciones() {
    cout << "\n\tABM DE MATERIAS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t1) Alta de Materia\n";
    cout << "\t2) Modificar Materia\n";
    cout << "\t3) Baja lógica de Materia\n";
    cout << "\t4) Listar Materias activas\n";
    cout << "\t5) Asignar/Modificar Docente Titular (opcional)\n";
    cout << "\t6) Configurar Correlativas (opcional)\n";
    cout << "\t0) Volver\n";
}

int MenuABMMaterias::seleccionOpcion() {
    mostrarOpciones();
    cout << "\t--------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuABMMaterias::ejecutarOpcion(int opcion) {
    ManagerMateria manager;

    switch (opcion) {

        case 1:
            cout << "\n\t=== ALTA DE MATERIA ===\n";
            manager.alta();
            break;

        case 2:
            cout << "\n\t=== MODIFICAR MATERIA ===\n";
            manager.modificacion();
            break;

        case 3:
            cout << "\n\t=== BAJA LÓGICA DE MATERIA ===\n";
            manager.baja();
            break;

        case 4:
            cout << "\n\t=== LISTADO DE MATERIAS ===\n";
            manager.listarTodas();
            break;

        case 5:
            cout << "\n\tFuncionalidad opcional (Docente titular)\n";
            break;

        case 6:
            cout << "\n\tFuncionalidad opcional (Correlativas)\n";
            break;

        default:
            cout << "\n\tOpción inválida.\n";
            break;
    }
}
