#include "MenuAlumno.h"
#include <iostream>
#include <cstdlib>
using namespace std;

MenuAlumno::MenuAlumno() {
    _cantidadOpciones = 11;
}

void MenuAlumno::mostrar() {
    int opcion;
    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void MenuAlumno::mostrarOpciones() {
    cout << endl;
    cout << "\n\t===== MENÚ DEL ALUMNO =====\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Ver mis datos personales\n";
    cout << "\t2) Ver historial de notas\n";
    cout << "\t3) Ver materias aprobadas\n";
    cout << "\t4) Ver materias pendientes\n";
    cout << "\t5) Ver mis inscripciones (comisiones y exámenes)\n";
    cout << "\t6) Inscribirme a comisión\n";                // NUEVO
    cout << "\t7) Dar de baja inscripción a comisión\n";    // NUEVO
    cout << "\t8) Inscribirme a examen final\n";
    cout << "\t9) Dar de baja inscripción a final\n";
    cout << "\t10) Solicitar baja de legajo\n";
    cout << "\t11) Reactivar legajo\n";
    cout << "\t0) Volver\n";
    cout << "\t--------------------------------\n";
}

int MenuAlumno::seleccionOpcion() {
    int opcion;
    mostrarOpciones();

    string mensaje = "\t----------------------------------------------\n";
    mensaje += "\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje, 0, _cantidadOpciones);
    return opcion;
}

void MenuAlumno::ejecutarOpcion(int opcion) {
    int legajo, idMateria, idComision;

    switch (opcion) {
        case 1:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarAlumnoPorLegajo(legajo);
            break;

        case 2:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.mostrarHistorialNotas(legajo);
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
            _alumnoManager.verMisInscripciones(legajo);
            break;

        case 6:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.inscribirseAComision(legajo);
            break;

        case 7:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de la comisión a dar de baja: ";
            cin >> idComision;
            _alumnoManager.bajaInscripcionComision(legajo, idComision);
            break;

        case 8:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de la materia (para examen final): ";
            cin >> idMateria;
            _alumnoManager.inscribirseAFinal(legajo, idMateria);
            break;

        case 9:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de la comisión del examen final: ";
            cin >> idComision;
            _alumnoManager.bajaInscripcionMesaFinal(legajo, idComision);
            break;

        case 10:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.solicitarBaja(legajo);
            break;

        case 11:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            _alumnoManager.reactivarAlumno(legajo);
            break;

        case 0:
            cout << "Volviendo al menú principal...\n";
            break;

        default:
            cout << "Opción no válida.\n";
            break;
    }
}
