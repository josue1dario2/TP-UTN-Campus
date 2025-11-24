#include "MenuPrincipal.h"
#include "Validacion.h"
#include "utils.h"
#include "ValidadorAcceso.h"
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
    ValidadorAcceso validador;
    int legajo;

    switch (opcion) {

        case 1: { // Alumno
            if (validador.validarLegajoAlumno(legajo)) {
                MenuAlumno menu(legajo);
                menu.mostrar();
            }
        } break;

        case 2: { // Docente
            if (validador.validarLegajoDocente(legajo)) {
                MenuDocente menu(legajo);
                menu.mostrar();
            }
        } break;

        case 3: { // Admin
            if (validador.validarCodigoAdmin()) {
                MenuAdministrador menu;
                menu.mostrar();
            }
        } break;

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
