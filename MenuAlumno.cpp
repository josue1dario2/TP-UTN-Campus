#include "MenuAlumno.h"
#include "Validacion.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuAlumno::MenuAlumno()
{
    _cantidadOpciones = 11;
}

void MenuAlumno::mostrar()
{
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 0) {
            return;
        }

        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuAlumno::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ DEL ALUMNO\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Inscripción a Materia (Comisión)\n";
    cout << "\t2) Inscripción a Examen\n";
    cout << "\t3) Ver Materias Aprobadas\n";
    cout << "\t4) Ver Materias Pendientes\n";
    cout << "\t5) Ver Mis Comisiones\n";
    cout << "\t6) Ver Mis Mesas\n";
    cout << "\t7) Dar de Baja Inscripción a Materia\n";
    cout << "\t8) Dar de Baja Inscripción a Mesa/Final\n";
    cout << "\t9) Ver Mis Notas / Historial\n";
    cout << "\t10) Solicitud de baja\n";
    cout << "\t11) Editar mis datos\n";
    cout << "\t0) Volver\n";
}

void MenuAlumno::ejecutarOpcion(int opcion) {
    int legajo, idMateria, idComision;

    switch (opcion) {
        case 1:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.inscribirseAComision(legajo);
            break;

        case 2:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese el ID de la materia: ";
            cin >> idMateria;
            _alumnoManager.inscribirseAFinal(legajo, idMateria);
            break;

        case 3:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarMateriasAprobadas(legajo);
            break;

        case 4:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarMateriasPendientes(legajo);
            break;

        case 5:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.verMisComisiones(legajo);
            break;

        case 6:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.verMisMesas(legajo);
            break;

        case 7:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de comisión: ";
            cin >> idComision;
            _alumnoManager.bajaInscripcionComision(legajo, idComision);
            break;

        case 8:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de comisión: ";
            cin >> idComision;
            _alumnoManager.bajaInscripcionMesaFinal(legajo, idComision);
            break;

        case 9:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarHistorialNotas(legajo);
            break;

        case 10:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.solicitarBaja(legajo);
            break;

        case 11:
            cout << "Funcionalidad en desarrollo.\n";
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuAlumno::seleccionOpcion() {
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------" << endl;
    cout << "\tOpción: ";
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
    return opcion;
}
