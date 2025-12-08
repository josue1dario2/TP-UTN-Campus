#include "MenuAdmin.h"
#include "Validacion.h"
#include "utils.h"
#include "ManagerInscripcionComision.h"

#include <iostream>
using namespace std;

MenuAdministrador::MenuAdministrador() {
    _cantidadOpciones = 10;
}

void MenuAdministrador::mostrar() {
    int opcion;
    do {
        clearScreen();
        mostrarOpciones();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 0) return;

        ejecutarOpcion(opcion);
        pauseScreen();

    } while (opcion != 0);
}

void MenuAdministrador::mostrarOpciones() {

    cout << "\n========== MENÚ ADMINISTRADOR ==========\n";

    cout << "\n>> GESTIÓN ACADÉMICA\n";
    cout << "  1) ABM Carreras\n";
    cout << "  2) ABM Materias\n";
    cout << "  3) ABM Comisiones\n";
    cout << "  4) ABM Correlativas\n";

    cout << "\n>> GESTIÓN DE USUARIOS\n";
    cout << "  5) Alta de Alumno\n";
    cout << "  6) Alta de Docente\n";
    cout << "  7) Listar Alumnos\n";
    cout << "  8) Listar Docentes\n";

    cout << "\n>> PROCESOS Y SOLICITUDES\n";
    cout << "  9) Solicitudes de Baja de Comisiones\n";

    cout << "\n>> HERRAMIENTAS DEL SISTEMA\n";
    cout << " 10) Borrado DEFINITIVO de registros\n";

    cout << "\n-----------------------------------------\n";
    cout << "  0) Volver\n";
}

int MenuAdministrador::seleccionOpcion() {
    cout << "\nSeleccione una opcion: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAdministrador::ejecutarOpcion(int opcion) {
    switch (opcion) {

        // -------- GESTIÓN ACADÉMICA --------
        case 1: menuCarrera.mostrar(); break;
        case 2: menuMateria.mostrarMenuABMMaterias(); break;
        case 3: menuComision.mostrar(); break;
        case 4: menuCorrelativa.mostrar(); break;

        // -------- GESTIÓN DE USUARIOS --------
        case 5: _managerAlumno.registrarAlumno(); break;
        case 6: _managerDocente.registrarDocente(); break;
        case 7: _managerAlumno.listarAlumnos(); break;
        case 8: _managerDocente.listarDocentes(); break;

        // -------- PROCESOS Y SOLICITUDES --------
        case 9: {
            ManagerInscripcionComision mic;
            mic.procesarSolicitudesPendientes();
            break;
        }

        // -------- BORRADO DEFINITIVO --------
        case 10:
            menuBorradoDefinitivo();
            break;

        case 0:
            return;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}

void MenuAdministrador::menuBorradoDefinitivo() {

    int opcion;
    do {
        clearScreen();
        cout << "\n\t=== BORRADO DEFINITIVO ===\n";
        cout << "\t1) Borrar alumno definitivamente\n";
        cout << "\t2) Borrar docente definitivamente\n";
        cout << "\t0) Volver\n";
        cout << "\t---------------------------\n";
        cout << "\tOpción: ";

        opcion = Validacion::validarEnteroEnRango("", 0, 2);

        switch (opcion) {
            case 1:
                _managerAlumno.borrarDefinitivo();
                break;

            case 2:
                _managerDocente.borrarDefinitivo();
                break;

            case 0:
                return;
        }

        pauseScreen();

    } while (opcion != 0);
}
