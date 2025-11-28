#include "ValidadorAcceso.h"
#include "Validacion.h"
#include <iostream>
#include <limits>

using namespace std;

ValidadorAcceso::ValidadorAcceso() : intentosActuales(0) {}

void ValidadorAcceso::resetearIntentos() {
    intentosActuales = 0;
}

void ValidadorAcceso::mostrarIntentosRestantes(int intentosRestantes) const {
    if (intentosRestantes > 0) {
        cout << "\tIntentos restantes: " << intentosRestantes << "\n";
    }
}

void ValidadorAcceso::mostrarBloqueo() const {
    cout << "\n\t*** ACCESO BLOQUEADO ***\n";
    cout << "\tNumero maximo de intentos alcanzado.\n";
    cout << "\tRegresando al menu principal...\n";
}

bool ValidadorAcceso::validarLegajoAlumno(int& legajoValidado) {
    const int MAX_INTENTOS = 3;
    ArchivoAlumno archivoAlumnos("Alumnos.dat");
    resetearIntentos();

    // Verificar si hay alumnos registrados
    int totalAlumnos = archivoAlumnos.contarRegistros();
    if (totalAlumnos == 0) {
        cout << "\n\t*** ERROR: No hay alumnos registrados en el sistema ***\n";
        cout << "\tPor favor, ejecute el inicializador de datos primero:\n";
        cout << "\t  ./build/inicializar_datos\n\n";
        return false;
    }

    while (intentosActuales < MAX_INTENTOS) {
        int legajo = Validacion::validarEntero("\n\tIngrese su legajo: ");

        int pos = archivoAlumnos.buscarRegistro(legajo);

        if (pos >= 0) {  // Solo posiciones válidas (>= 0)
            Alumno alu = archivoAlumnos.leerRegistro(pos);
            if (!alu.getEliminado()) {
                legajoValidado = legajo;
                return true;  // Éxito
            } else {
                intentosActuales++;
                cout << "\n\tADVERTENCIA: El alumno con legajo " << legajo << " esta dado de baja.\n";
                if (intentosActuales < MAX_INTENTOS) {
                    mostrarIntentosRestantes(MAX_INTENTOS - intentosActuales);
                }
            }
        } else {
            intentosActuales++;
            cout << "\n\tERROR: Legajo no encontrado.\n";
            if (intentosActuales < MAX_INTENTOS) {
                mostrarIntentosRestantes(MAX_INTENTOS - intentosActuales);
            }
        }
    }

    mostrarBloqueo();
    return false;  // Bloqueo por intentos
}

bool ValidadorAcceso::validarLegajoDocente(int& legajoValidado) {
    const int MAX_INTENTOS = 3;
    ArchivoDocente archivoDocentes("Docentes.dat");
    resetearIntentos();

    // Verificar si hay docentes registrados
    int totalDocentes = archivoDocentes.contarRegistros();
    if (totalDocentes == 0) {
        cout << "\n\t*** ERROR: No hay docentes registrados en el sistema ***\n";
        cout << "\tPor favor, contacte al administrador o ejecute el inicializador de datos:\n";
        cout << "\t  ./build/inicializar_datos\n\n";
        return false;
    }

    while (intentosActuales < MAX_INTENTOS) {
        int legajo = Validacion::validarEntero("\n\tIngrese su legajo de docente: ");

        int pos = archivoDocentes.buscarRegistro(legajo);

        if (pos >= 0) {  // Solo posiciones válidas (>= 0)
            Docente doc = archivoDocentes.leerRegistro(pos);
            if (!doc.getEliminado()) {
                legajoValidado = legajo;
                return true;  // Éxito
            } else {
                intentosActuales++;
                cout << "\n\tADVERTENCIA: El docente con legajo " << legajo << " esta dado de baja.\n";
                if (intentosActuales < MAX_INTENTOS) {
                    mostrarIntentosRestantes(MAX_INTENTOS - intentosActuales);
                }
            }
        } else {
            intentosActuales++;
            cout << "\n\tERROR: Legajo no encontrado.\n";
            if (intentosActuales < MAX_INTENTOS) {
                mostrarIntentosRestantes(MAX_INTENTOS - intentosActuales);
            }
        }
    }

    mostrarBloqueo();
    return false;  // Bloqueo por intentos
}

bool ValidadorAcceso::validarCodigoAdmin() {
    const int MAX_INTENTOS = 3;
    resetearIntentos();

    while (intentosActuales < MAX_INTENTOS) {
        int codigo = Validacion::validarEntero("\n\tIngrese codigo de administrador: ");

        if (codigo == 1234) {
            return true;  // Éxito
        }

        intentosActuales++;
        cout << "\n\tERROR: Codigo incorrecto.\n";
        if (intentosActuales < MAX_INTENTOS) {
            mostrarIntentosRestantes(MAX_INTENTOS - intentosActuales);
        }
    }

    mostrarBloqueo();
    cout << "\tAcceso denegado.\n";
    return false;  // Bloqueo por intentos
}
