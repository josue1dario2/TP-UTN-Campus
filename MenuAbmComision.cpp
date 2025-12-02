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
    cout << "\t------------------------------------------\n";
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
    cout << "\t------------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAbmComision::ejecutarOpcion(int opcion) {
    ManagerComision manager;

    switch (opcion) {

        case 1:
            manager.alta();
            break;

        case 2:
            manager.modificar();
            break;

        case 3:
            manager.borrar();
            break;

        case 4:
            manager.listarComisiones();
            break;

        case 5:
            manager.listarPorMateria();
            break;

        case 6:
            manager.activar();
            break;
    }
}
