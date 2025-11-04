#include <iostream>
#include <limits>
#include "MenuUtilitarios.h"
#include "utils.h"

using namespace std;

void MenuUtilitarios::mostrarMenuPrincipal() {
    int opcion;
    do {
        clearScreen();
        cout << "\n\tMENÚ UTILITARIOS\n";
        cout << "\t---------------------------\n";
        cout << "\t1 - Realizar copia de seguridad\n";
        cout << "\t2 - Restaurar copia de seguridad\n";
        cout << "\t3 - Exportar datos (CSV)\n";
        cout << "\t---------------------------\n";
        cout << "\t0 - Volver\n";
        cout << "\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        clearScreen();
        switch (opcion) {
            case 1: realizarCopiaSeguridad(); break;
            case 2: restaurarCopiaSeguridad(); break;
            case 3: exportarDatosCSV(); break;
            case 0: cout << "Volviendo al menú anterior...\n"; break;
            default: cout << "Opción inválida. Intente nuevamente.\n"; break;
        }

        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}

void MenuUtilitarios::realizarCopiaSeguridad() {
    int opcion;
    do {
        clearScreen();
        cout << "\n\tREALIZAR COPIA DE SEGURIDAD\n";
        cout << "\t--------------------------------------\n";
        cout << "\t 1 - ALUMNOS\n";
        cout << "\t 2 - DOCENTES\n";
        cout << "\t 3 - CARRERAS\n";
        cout << "\t 4 - MATERIAS\n";
        cout << "\t 5 - COMISIONES\n";
        cout << "\t 6 - INSCRIPCIONES\n";
        cout << "\t 7 - MESAS DE EXAMEN\n";
        cout << "\t 8 - EVALUACIONES\n";
        cout << "\t 9 - CALIFICACIONES\n";
        cout << "\t10 - CORRELATIVAS\n";
        cout << "\t--------------------------------------\n";
        cout << "\t11 - TODOS LOS ARCHIVOS\n";
        cout << "\t--------------------------------------\n";
        cout << "\t 0 - SALIR\n";
        cout << "\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion >= 1 && opcion <= 11) {
            cout << "Realizando copia de seguridad para opción " << opcion << "...\n";
        } else if (opcion != 0) {
            cout << "Opción inválida. Intente nuevamente.\n";
        }

        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}

void MenuUtilitarios::restaurarCopiaSeguridad() {
    int opcion;
    do {
        clearScreen();
        cout << "\n\tRESTAURAR COPIA DE SEGURIDAD\n";
        cout << "\t--------------------------------------\n";
        cout << "\t 1 - ALUMNOS\n";
        cout << "\t 2 - DOCENTES\n";
        cout << "\t 3 - CARRERAS\n";
        cout << "\t 4 - MATERIAS\n";
        cout << "\t 5 - COMISIONES\n";
        cout << "\t 6 - INSCRIPCIONES\n";
        cout << "\t 7 - MESAS DE EXAMEN\n";
        cout << "\t 8 - EVALUACIONES\n";
        cout << "\t 9 - CALIFICACIONES\n";
        cout << "\t10 - CORRELATIVAS\n";
        cout << "\t--------------------------------------\n";
        cout << "\t11 - TODOS LOS ARCHIVOS\n";
        cout << "\t--------------------------------------\n";
        cout << "\t 0 - SALIR\n";
        cout << "\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion >= 1 && opcion <= 11) {
            cout << "Restaurando copia de seguridad para opción " << opcion << "...\n";
        } else if (opcion != 0) {
            cout << "Opción inválida. Intente nuevamente.\n";
        }

        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}

void MenuUtilitarios::exportarDatosCSV() {
    int opcion;
    do {
        clearScreen();
        cout << "\n\tEXPORTAR ARCHIVOS CSV\n";
        cout << "\t--------------------------------------\n";
        cout << "\t 1 - ALUMNOS\n";
        cout << "\t 2 - DOCENTES\n";
        cout << "\t 3 - CARRERAS\n";
        cout << "\t 4 - MATERIAS\n";
        cout << "\t 5 - COMISIONES\n";
        cout << "\t 6 - INSCRIPCIONES\n";
        cout << "\t 7 - MESAS DE EXAMEN\n";
        cout << "\t 8 - EVALUACIONES\n";
        cout << "\t 9 - CALIFICACIONES\n";
        cout << "\t10 - CORRELATIVAS\n";
        cout << "\t--------------------------------------\n";
        cout << "\t11 - TODOS LOS ARCHIVOS\n";
        cout << "\t--------------------------------------\n";
        cout << "\t 0 - SALIR\n";
        cout << "\tSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion >= 1 && opcion <= 11) {
            cout << "Exportando datos CSV para opción " << opcion << "...\n";
        } else if (opcion != 0) {
            cout << "Opción inválida. Intente nuevamente.\n";
        }

        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}
