#include "MenuPrincipal.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <limits>
using namespace std;

MenuPrincipal::MenuPrincipal() {
    _cantidadOpciones = 4;
}

void MenuPrincipal::mostrar() {
    int opcion;

    do {
        clearScreen();
        mostrarOpciones();
        cout << "\t----------------------------------------------\n";
        cout << "\tOpción: ";

        opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);

        clearScreen();
        ejecutarOpcion(opcion);

        if (opcion != 0) pauseScreen();

    } while (opcion != 0);
}

void MenuPrincipal::mostrarOpciones() {
    cout << "\n\tSISTEMA DE GESTIÓN DE CAMPUS – MENÚ PRINCIPAL\n";
    cout << "\t----------------------------------------------\n";
    cout << "\t1 - Alumno\n";
    cout << "\t2 - Docente\n";
    cout << "\t3 - Administrador\n";
    cout << "\t4 - Utilitarios\n";
    cout << "\t----------------------------------------------\n";
    cout << "\t0 - Salir\n";
}

void MenuPrincipal::ejecutarOpcion(int opcion) {

    int legajo;
    int codigo;

    switch (opcion) {

        case 1: {
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            MenuAlumno menu(legajo);
            menu.mostrar();
        } break;


        case 2: // Docente
            cout << "Ingrese su legajo de docente: ";
            cin >> legajo;
        {
            MenuDocente menu(legajo);
            menu.mostrar();
        }
        break;

        case 3: // Admin
            cout << "Ingrese código de administrador: ";
            cin >> codigo;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (codigo == 1234) {
                MenuAdministrador menu;
                menu.mostrar();
            } else {
                cout << "Código incorrecto.\n";
            }
            break;

        case 4:
        {
            MenuUtilitarios mu;
            mu.mostrarMenuPrincipal();
        }
            break;

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
