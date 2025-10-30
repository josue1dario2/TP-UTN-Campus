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
        system("pause");
    } while (opcion != 0);
}

void MenuAlumno::mostrarOpciones() {
    cout << endl;
    cout << "\n\tMENÚ DEL ALUMNO\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Inscripción a Materia (Comisión)\n";
    cout << "\t2) Inscripción a Examen Final\n";
    cout << "\t3) Ver Materias Aprobadas\n";
    cout << "\t4) Ver Materias Pendientes\n";
    cout << "\t5) Ver Mis Comisiones (pendiente)\n";
    cout << "\t6) Ver Mis Mesas (pendiente)\n";
    cout << "\t7) Dar de Baja Inscripción a Materia (pendiente)\n";
    cout << "\t8) Dar de Baja Inscripción a Mesa/Final (pendiente)\n";
    cout << "\t9) Ver Mis Notas / Historial\n";
    cout << "\t10) Solicitud de baja\n";
    cout << "\t11) Reactivar mi legajo\n";
    cout << "\t0) Volver\n";
}

int MenuAlumno::seleccionOpcion() {
    int opcion;
    mostrarOpciones();

    string mensaje="\t----------------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje, 0, _cantidadOpciones);

    while (opcion < 0 || opcion > _cantidadOpciones) {
        cout << "\tOpción incorrecta...\n";
        cout << "\tOpción: ";
        cin >> opcion;
    }

    return opcion;
}


void MenuAlumno::ejecutarOpcion(int opcion) {
    int legajo, idMateria;

    switch (opcion) {
        case 1:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de la comisión a inscribirse: ";
            cin >> idMateria; // o idComision
            _alumnoManager.inscribirseAMateria(legajo, idMateria);
            break;

        case 2:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de la materia: ";
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
            cout << "Ingrese ID de comisión a dar de baja: ";
            cin >> idMateria;
            _alumnoManager.bajaInscripcionMateria(legajo, idMateria);
            break;

        case 8:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            cout << "Ingrese ID de comisión de la mesa a dar de baja: ";
            cin >> idMateria;  // o idComision
            _alumnoManager.bajaInscripcionMesaFinal(legajo, idMateria);
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
