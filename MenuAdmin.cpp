#include "MenuAdmin.h"
#include "MenuAbmComisiones.h"
#include "MenuAbmMaterias.h"
#include "MenuAbmCarreras.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuAdministrador::MenuAdministrador() {
    _cantidadOpciones = 4;
}

void MenuAdministrador::mostrar() {
    int opcion;
    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void MenuAdministrador::mostrarOpciones() {
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRADOR – ABM\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Carreras\n";
    cout << "\t2) Materias\n";
    cout << "\t3) Comisiones\n";
    cout << "\t4) Solicitudes\n";
    cout << "\t0) Volver\n";
    cout << "\t--------------------------------\n";
}

int MenuAdministrador::seleccionOpcion() {
    int opcion;
    mostrarOpciones();

    string mensaje = "\t----------------------------------------------\n";
    mensaje += "\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje, 0, _cantidadOpciones);
    return opcion;
}

void MenuAdministrador::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1: {
            cout << "Funcionalidad de Carreras pendiente de implementación.\n";
            break;
        }

        case 2: {
            cout << "Funcionalidad de Materias pendiente de implementación.\n";
            break;
        }

        case 3: {
            MenuAbmComisiones menuComisiones;
            menuComisiones.mostrar();
            break;
        }

        case 4:
            cout << "Gestión de solicitudes aún no implementada.\n";
            break;

        case 0:
            cout << "Volviendo al menú principal...\n";
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
