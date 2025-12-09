#include "MenuAlumno.h"
#include "ArchivoAlumno.h"
#include "utils.h"
#include <iostream>
using namespace std;

MenuAlumno::MenuAlumno(int legajo) {
    _cantidadOpciones = 12;
    _legajoAlumno = legajo;

    ArchivoAlumno archivoAlumnos("Alumnos.dat");
    int pos = archivoAlumnos.buscarRegistro(legajo);

    if (pos >= 0) {
        Alumno alu = archivoAlumnos.leerRegistro(pos);
        _nombreCompleto = string(alu.getNombre()) + " " + string(alu.getApellido());
    } else {
        _nombreCompleto = "Desconocido";
    }
}

void MenuAlumno::mostrar() {
    int opcion;
    _salirDelMenu = false;

    do {
        clearScreen();
        mostrarOpciones();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 11) {
            if (_alumnoManager.solicitarBaja(_legajoAlumno)) {
                pauseScreen();
                return;
            } else {
                pauseScreen();
                continue;
            }
        }

        if (opcion == 0) return;

        ejecutarOpcion(opcion);
        pauseScreen();

    } while (true);
}


void MenuAlumno::mostrarOpciones() {
    cout << "\n========== MENÚ DEL ALUMNO ==========\n";
    cout << "Alumno: " << _nombreCompleto << " (Legajo: " << _legajoAlumno << ")\n";
    cout << "-----------------------------------------\n";

    cout << ">> INSCRIPCIONES\n";
    cout << "  1) Inscribirse a Materia (Comisión)\n";
    cout << "  2) Inscribirse a Examen Final\n";
    cout << "  3) Inscribirse a Parcial\n\n";

    cout << ">> CONSULTAS\n";
    cout << "  4) Ver Mis Comisiones\n";
    cout << "  5) Ver Mis Mesas Finales\n";
    cout << "  6) Ver Materias Aprobadas\n";
    cout << "  7) Ver Materias Pendientes\n";
    cout << "  8) Ver Historial de Notas\n\n";

    cout << ">> BAJAS Y MODIFICACIONES\n";
    cout << "  9) Solicitar Baja de Comisión\n";
    cout << " 10) Baja Inscripción a Examen Final\n";
    cout << " 11) Solicitar Baja del Alumno\n";
    cout << " 12) Editar Mis Datos\n";
    cout << "-----------------------------------------\n";
    cout << "  0) Volver\n\n";
}

int MenuAlumno::seleccionOpcion() {
    cout << "Opción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAlumno::ejecutarOpcion(int opcion) {
    int idMateria, idComision;

    switch (opcion) {

        // *** INSCRIPCIONES ***
        case 1:
            _alumnoManager.inscribirseAComision(_legajoAlumno);
            break;

        case 2:
            cout << "ID Materia: ";
            cin >> idMateria;
            _alumnoManager.inscribirseAFinal(_legajoAlumno, idMateria);
            break;

        case 3:
            _alumnoManager.inscribirseAParcial(_legajoAlumno);
            break;

        // *** CONSULTAS ***
        case 4:
            _alumnoManager.verMisComisiones(_legajoAlumno);
            break;

        case 5:
            _alumnoManager.verMisMesas(_legajoAlumno);
            break;

        case 6:
            _alumnoManager.mostrarMateriasAprobadas(_legajoAlumno);
            break;

        case 7:
            _alumnoManager.mostrarMateriasPendientes(_legajoAlumno);
            break;

        case 8:
            _alumnoManager.mostrarHistorialNotas(_legajoAlumno);
            break;

        // *** BAJAS Y MODIFICACIONES ***
        case 9:
            cout << "ID Comisión: ";
            cin >> idComision;
            _alumnoManager.solicitarBajaComision(_legajoAlumno, idComision);
            break;

        case 10:
            cout << "ID Materia: ";
            cin >> idMateria;
            _alumnoManager.bajaInscripcionExamenFinal(_legajoAlumno, idMateria);
            break;

        case 11:
            _alumnoManager.solicitarBaja(_legajoAlumno);
            break;

        case 12:
            _alumnoManager.editarDatos(_legajoAlumno);
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
