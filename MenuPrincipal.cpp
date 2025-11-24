#include "MenuPrincipal.h"
#include "Validacion.h"
#include "utils.h"
#include "ArchivoAlumno.h"
#include "ArchivoDocente.h"
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
    int intentos;
    const int MAX_INTENTOS = 3;

    switch (opcion) {

        case 1: { // Alumno
            ArchivoAlumno archivoAlumnos("Alumnos.dat");
            intentos = 0;
            bool legajoValido = false;

            while (intentos < MAX_INTENTOS && !legajoValido) {
                cout << "\n\tIngrese su legajo: ";
                cin >> legajo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int pos = archivoAlumnos.buscarRegistro(legajo);

                if (pos != -1) {
                    Alumno alu = archivoAlumnos.leerRegistro(pos);
                    if (!alu.getEliminado()) {
                        legajoValido = true;
                        MenuAlumno menu(legajo);
                        menu.mostrar();
                    } else {
                        intentos++;
                        cout << "\n\t⚠ El alumno con legajo " << legajo << " está dado de baja.\n";
                        if (intentos < MAX_INTENTOS) {
                            cout << "\tIntentos restantes: " << (MAX_INTENTOS - intentos) << "\n";
                        }
                    }
                } else {
                    intentos++;
                    cout << "\n\t✗ Legajo no encontrado.\n";
                    if (intentos < MAX_INTENTOS) {
                        cout << "\tIntentos restantes: " << (MAX_INTENTOS - intentos) << "\n";
                    }
                }
            }

            if (!legajoValido) {
                cout << "\n\t⚠ Número máximo de intentos alcanzado.\n";
                cout << "\tRegresando al menú principal...\n";
            }
        } break;


        case 2: { // Docente
            ArchivoDocente archivoDocentes("Docentes.dat");
            intentos = 0;
            bool legajoValido = false;

            while (intentos < MAX_INTENTOS && !legajoValido) {
                cout << "\n\tIngrese su legajo de docente: ";
                cin >> legajo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                int pos = archivoDocentes.buscarRegistro(legajo);

                if (pos != -1) {
                    Docente doc = archivoDocentes.leerRegistro(pos);
                    if (!doc.getEliminado()) {
                        legajoValido = true;
                        MenuDocente menu(legajo);
                        menu.mostrar();
                    } else {
                        intentos++;
                        cout << "\n\t⚠ El docente con legajo " << legajo << " está dado de baja.\n";
                        if (intentos < MAX_INTENTOS) {
                            cout << "\tIntentos restantes: " << (MAX_INTENTOS - intentos) << "\n";
                        }
                    }
                } else {
                    intentos++;
                    cout << "\n\t✗ Legajo no encontrado.\n";
                    if (intentos < MAX_INTENTOS) {
                        cout << "\tIntentos restantes: " << (MAX_INTENTOS - intentos) << "\n";
                    }
                }
            }

            if (!legajoValido) {
                cout << "\n\t⚠ Número máximo de intentos alcanzado.\n";
                cout << "\tRegresando al menú principal...\n";
            }
        }
        break;

        case 3: { // Admin
            intentos = 0;
            bool codigoCorrecto = false;

            while (intentos < MAX_INTENTOS && !codigoCorrecto) {
                cout << "\n\tIngrese código de administrador: ";
                cin >> codigo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (codigo == 1234) {
                    codigoCorrecto = true;
                    MenuAdministrador menu;
                    menu.mostrar();
                } else {
                    intentos++;
                    cout << "\n\t✗ Código incorrecto.\n";
                    if (intentos < MAX_INTENTOS) {
                        cout << "\tIntentos restantes: " << (MAX_INTENTOS - intentos) << "\n";
                    }
                }
            }

            if (!codigoCorrecto) {
                cout << "\n\t⚠ Número máximo de intentos alcanzado.\n";
                cout << "\tAcceso denegado. Regresando al menú principal...\n";
            }
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
