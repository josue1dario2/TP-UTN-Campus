#include "MenuAlumno.h"
#include "utils.h"
#include <iostream>
using namespace std;

MenuAlumno::MenuAlumno(int legajo) {
    _cantidadOpciones = 11;
    _legajoAlumno = legajo;
}

void MenuAlumno::mostrar() {
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

void MenuAlumno::mostrarOpciones() {
    cout << "\n\tMENÚ DEL ALUMNO (Legajo: " << _legajoAlumno << ")\n";
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
    cout << "\t11) Editar mis datos\n";
    cout << "\t0) Volver\n";
}

int MenuAlumno::seleccionOpcion() {
    cout << "\t------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAlumno::ejecutarOpcion(int opcion) {
    int idMateria, idComision;

    switch (opcion) {

        case 1:
            _alumnoManager.inscribirseAComision(_legajoAlumno);
            break;

        case 2:
            cout << "ID Materia: ";
            cin >> idMateria;
            _alumnoManager.inscribirseAFinal(_legajoAlumno, idMateria);
            break;

        case 3:
            _alumnoManager.mostrarMateriasAprobadas(_legajoAlumno);
            break;

        case 4:
            _alumnoManager.mostrarMateriasPendientes(_legajoAlumno);
            break;

        case 5:
            _alumnoManager.verMisComisiones(_legajoAlumno);
            break;

        case 6:
            _alumnoManager.verMisMesas(_legajoAlumno);
            break;

        case 7:
            cout << "ID Comisión: ";
            cin >> idComision;
            _alumnoManager.solicitarBajaComision(_legajoAlumno, idComision);
            break;

        case 8:
            cout << "ID Materia: ";
            cin >> idMateria;
            _alumnoManager.bajaInscripcionExamenFinal(_legajoAlumno, idMateria);
            break;

        case 9:
            _alumnoManager.mostrarHistorialNotas(_legajoAlumno);
            break;

        case 10:
            _alumnoManager.solicitarBaja(_legajoAlumno);
            break;

        case 11:
            _alumnoManager.editarDatos(_legajoAlumno);
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
