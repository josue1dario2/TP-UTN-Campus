#include "MenuAdmin.h"
#include "Validacion.h"
#include "utils.h"
#include "ManagerInscripcionComision.h"
#include "InscripcionComision.h"

#include <iostream>
using namespace std;

MenuAdministrador::MenuAdministrador() {
    _cantidadOpciones = 10;
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
    cout << "\t8) Listar Alumnos\n";
    cout << "\t9) Listar Docentes\n";
    cout << "\t10) Borrar DEFINITIVAMENTE registros\n";
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

        case 8:
            _managerAlumno.listarAlumnos();
            break;

        case 9:
            _managerDocente.listarDocentes();
            break;

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
