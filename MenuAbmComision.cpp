#include "MenuAbmComision.h"
#include "ManagerComision.h"
#include "Validacion.h"
#include "utils.h"

#include <iostream>
using namespace std;

MenuAbmComision::MenuAbmComision() {
    _cantidadOpciones = 6;
}

void MenuAbmComision::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 0) {
            cout << "\n\tVolviendo...\n";
            return;
        }

        ejecutarOpcion(opcion);
        pauseScreen();

    } while (opcion != 0);
}

void MenuAbmComision::mostrarOpciones() {
    cout << "\n\tABM COMISIONES\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Comisión\n";
    cout << "\t2) Modificar Comisión\n";
    cout << "\t3) Baja lógica de Comisión\n";
    cout << "\t4) Listar Comisiones\n";
    cout << "\t5) Listar por Materia\n";
    cout << "\t6) Reactivar Comisión\n";
    cout << "\t0) Volver\n";
}

int MenuAbmComision::seleccionOpcion() {
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAbmComision::ejecutarOpcion(int opcion) {
    ManagerComision manager;

    switch (opcion) {

        case 1:
            cout << "\n\t=== ALTA DE COMISIÓN ===\n";
            manager.cargar();
            break;

        case 2:
            cout << "\n\t=== MODIFICAR COMISIÓN ===\n";
            manager.modificar();
            break;

        case 3:
            cout << "\n\t=== BAJA LÓGICA DE COMISIÓN ===\n";
            manager.borrar();
            break;

        case 4:
            cout << "\n\t=== LISTADO DE COMISIONES ===\n";
            manager.listar();
            break;

        case 5: {
            cout << "\n\t=== LISTAR COMISIONES POR MATERIA ===\n";
            int idMateria = Validacion::validarEnteroEnRango(
                "\tIngrese el ID de la materia: ", 1, 9999
            );
            manager.mostrarComisionesPorMateria(idMateria);
            break;
        }

        case 6:
            cout << "\n\t=== REACTIVAR COMISIÓN ===\n";
            manager.activar();
            break;
    }
}
