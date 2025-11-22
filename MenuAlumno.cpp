#include "MenuAlumno.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
using namespace std;

MenuAlumno::MenuAlumno() {
    _cantidadOpciones = 11;
}

void MenuAlumno::mostrar() {
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

void MenuAlumno::mostrarOpciones() {
    cout << "\n\tMENÚ DEL ALUMNO\n";
    cout << "\t------------------------------------\n";
    cout << "\t1) Inscribirse a Materia (Comisión)\n";
    cout << "\t2) Inscribirse a Examen Final\n";
    cout << "\t3) Ver Materias Aprobadas\n";
    cout << "\t4) Ver Materias Pendientes\n";
    cout << "\t5) Ver Mis Comisiones\n";
    cout << "\t6) Ver Mis Mesas Finales\n";
    cout << "\t7) Solicitar Baja de Comisión\n";
    cout << "\t8) Baja Inscripción a Examen Final\n";
    cout << "\t9) Ver Historial de Notas\n";
    cout << "\t10) Solicitar Baja del Alumno\n";
    cout << "\t11) Editar mis datos (No implementado)\n";
    cout << "\t0) Volver\n";
}

int MenuAlumno::seleccionOpcion() {
    cout << "\t------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAlumno::ejecutarOpcion(int opcion) {
    int legajo, idMateria, idComision;

    switch (opcion) {

        case 1: // Inscripción a comisión
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.inscribirseAComision(legajo);
            break;

        case 2: // Inscripción a examen final
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de materia: ";
            cin >> idMateria;
            _alumnoManager.inscribirseAFinal(legajo, idMateria);
            break;

        case 3: // Ver aprobadas
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarMateriasAprobadas(legajo);
            break;

        case 4: // Ver pendientes
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarMateriasPendientes(legajo);
            break;

        case 5: // Ver comisiones inscriptas
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.verMisComisiones(legajo);
            break;

        case 6: // Ver mesas finales
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.verMisMesas(legajo);
            break;

        case 7: // Solicitar baja de comisión
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de comisión: ";
            cin >> idComision;
            _alumnoManager.solicitarBajaComision(legajo, idComision);
            break;

        case 8: // Baja de examen final
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de materia: ";
            cin >> idMateria;
            _alumnoManager.bajaInscripcionExamenFinal(legajo, idMateria);
            break;

        case 9: // Historial de notas
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarHistorialNotas(legajo);
            break;

        case 10: // Solicitar baja del alumno
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
