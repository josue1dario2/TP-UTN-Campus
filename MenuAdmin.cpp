#include "MenuAdmin.h"
#include "Validacion.h"
#include "utils.h"
#include "ManagerInscripcionComision.h"
#include "InscripcionComision.h"

#include <iostream>
using namespace std;

MenuAdministrador::MenuAdministrador() {
    _cantidadOpciones = 7;
}

void MenuAdministrador::mostrar() {
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

void MenuAdministrador::mostrarOpciones() {
    cout << "\n\tMENÚ ADMINISTRADOR\n";
    cout << "\t-----------------------------------------\n";
    cout << "\t1) ABM Carreras\n";
    cout << "\t2) ABM Materias\n";
    cout << "\t3) ABM Comisiones\n";
    cout << "\t4) Solicitudes de Baja de Comisiones\n";
    cout << "\t5) ABM Correlativas\n";
    cout << "\t6) Alta de Alumno\n";
    cout << "\t7) Alta de Docente\n";
    cout << "\t0) Volver\n";
}

int MenuAdministrador::seleccionOpcion() {
    mostrarOpciones();
    cout << "\t-----------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAdministrador::ejecutarOpcion(int opcion) {
    switch (opcion) {

        case 1:
            menuCarrera.mostrar();
            break;

        case 2:
            menuMateria.mostrarMenuABMMaterias();
            break;

        case 3:
            menuComision.mostrar();
            break;

        case 4: {
            ManagerInscripcionComision mic;
            mic.procesarSolicitudesPendientes();
            break;
        }

        case 5:
            menuCorrelativa.mostrar();
            break;

        case 6:
            _managerAlumno.registrarAlumno();
            break;

        case 7:
            _managerDocente.registrarDocente();
            break;

        case 0:
            return;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
