#include "ValidadorAcceso.h"
#include <iostream>
#include <limits>

using namespace std;

ValidadorAcceso::ValidadorAcceso() : intentosActuales(0) {}

void ValidadorAcceso::resetearIntentos() {
    intentosActuales = 0;
}

void ValidadorAcceso::mostrarIntentosRestantes() const {
    int restantes = MAX_INTENTOS - intentosActuales;
    if (restantes > 0) {
        cout << "\tIntentos restantes: " << restantes << "\n";
    }
}

void ValidadorAcceso::mostrarBloqueo() const {
    cout << "\n\t⚠ Número máximo de intentos alcanzado.\n";
    cout << "\tRegresando al menú principal...\n";
}

bool ValidadorAcceso::validarLegajoAlumno(int& legajoValidado) {
    ArchivoAlumno archivoAlumnos("Alumnos.dat");
    resetearIntentos();

    while (intentosActuales < MAX_INTENTOS) {
        cout << "\n\tIngrese su legajo: ";
        int legajo;
        cin >> legajo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int pos = archivoAlumnos.buscarRegistro(legajo);

        if (pos != -1) {
            Alumno alu = archivoAlumnos.leerRegistro(pos);
            if (!alu.getEliminado()) {
                legajoValidado = legajo;
                return true;  // Éxito
            } else {
                intentosActuales++;
                cout << "\n\t⚠ El alumno con legajo " << legajo << " está dado de baja.\n";
                if (intentosActuales < MAX_INTENTOS) {
                    mostrarIntentosRestantes();
                }
            }
        } else {
            intentosActuales++;
            cout << "\n\t✗ Legajo no encontrado.\n";
            if (intentosActuales < MAX_INTENTOS) {
                mostrarIntentosRestantes();
            }
        }
    }

    mostrarBloqueo();
    return false;  // Bloqueo por intentos
}

bool ValidadorAcceso::validarLegajoDocente(int& legajoValidado) {
    ArchivoDocente archivoDocentes("Docentes.dat");
    resetearIntentos();

    while (intentosActuales < MAX_INTENTOS) {
        cout << "\n\tIngrese su legajo de docente: ";
        int legajo;
        cin >> legajo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int pos = archivoDocentes.buscarRegistro(legajo);

        if (pos != -1) {
            Docente doc = archivoDocentes.leerRegistro(pos);
            if (!doc.getEliminado()) {
                legajoValidado = legajo;
                return true;  // Éxito
            } else {
                intentosActuales++;
                cout << "\n\t⚠ El docente con legajo " << legajo << " está dado de baja.\n";
                if (intentosActuales < MAX_INTENTOS) {
                    mostrarIntentosRestantes();
                }
            }
        } else {
            intentosActuales++;
            cout << "\n\t✗ Legajo no encontrado.\n";
            if (intentosActuales < MAX_INTENTOS) {
                mostrarIntentosRestantes();
            }
        }
    }

    mostrarBloqueo();
    return false;  // Bloqueo por intentos
}

bool ValidadorAcceso::validarCodigoAdmin() {
    resetearIntentos();

    while (intentosActuales < MAX_INTENTOS) {
        cout << "\n\tIngrese código de administrador: ";
        int codigo;
        cin >> codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (codigo == 1234) {
            return true;  // Éxito
        }

        intentosActuales++;
        cout << "\n\t✗ Código incorrecto.\n";
        if (intentosActuales < MAX_INTENTOS) {
            mostrarIntentosRestantes();
        }
    }

    mostrarBloqueo();
    cout << "\tAcceso denegado.\n";
    return false;  // Bloqueo por intentos
}
