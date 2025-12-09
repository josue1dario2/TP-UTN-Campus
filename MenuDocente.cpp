#include "MenuDocente.h"
#include "ArchivoDocente.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Constructor sin parámetros (NECESARIO)
MenuDocente::MenuDocente() {
    _cantidadOpciones = 9;
    _legajoDocente = 0;
    _nombreCompleto = "Sin identificar";
}

// Constructor con legajo (LOGIN del docente)
MenuDocente::MenuDocente(int legajoDocente) {
    _cantidadOpciones = 9;
    _legajoDocente = legajoDocente;

    ArchivoDocente archivoDocentes("Docentes.dat");
    int pos = archivoDocentes.buscarRegistro(legajoDocente);

    if (pos >= 0) {
        Docente doc = archivoDocentes.leerRegistro(pos);
        _nombreCompleto = string(doc.getNombre()) + " " + string(doc.getApellido());
    } else {
        _nombreCompleto = "Desconocido";
    }
}

void MenuDocente::mostrar() {
    int opcion;
    _salirDelMenu = false;

    do {
        clearScreen();
        mostrarOpciones();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 8) {
            if (_manager.solicitarBaja(_legajoDocente)) {
                pauseScreen();
                return;
            } else {
                pauseScreen();
                continue;
            }
        }

        if (opcion == 0) return;

        ejecutarOpcion(opcion);

        if (opcion != 0) pauseScreen();

    } while (true);
}

void MenuDocente::mostrarOpciones() {
    cout << "\n========== MENÚ DEL DOCENTE ==========\n";
    cout << "Docente: " << _nombreCompleto << " (Legajo: " << _legajoDocente << ")\n";
    cout << "-----------------------------------------\n";
    cout << ">> COMISIONES Y ALUMNOS\n";
    cout << "  1) Ver Mis Comisiones\n";
    cout << "  2) Ver Alumnos de una Comisión\n\n";

    cout << ">> EVALUACIONES\n";
    cout << "  3) Corregir Exámenes (Parciales / Recuperatorios)\n";
    cout << "  4) Cargar Nota de Examen Final\n\n";

    cout << ">> CURSADA\n";
    cout << "  5) Publicar Notas de Cursada\n";
    cout << "  6) Cerrar Acta de Cursada\n\n";

    cout << ">> HERRAMIENTAS\n";
    cout << "  7) Exportar CSV\n";
    cout << "  8) Solicitar Baja\n";
    cout << "  9) Editar Mis Datos\n";
    cout << "-----------------------------------------\n";
    cout << "  0) Volver\n\n";
}

int MenuDocente::seleccionOpcion() {
    cout << "Opción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuDocente::ejecutarOpcion(int opcion) {

    switch (opcion) {
        case 1:
            _manager.verMisComisiones(_legajoDocente);
            break;

        case 2: {
            int idComision = Validacion::validarEntero("\tIngrese ID de comisión: ");
            _manager.verAlumnosDeComision(idComision);
            break;
        }

        case 3:
            _manager.corregirParciales(_legajoDocente);
            break;

        case 4:
            _manager.cargarNotasFinal(_legajoDocente);
            break;

        case 5:
            _manager.publicarNotasCursada(_legajoDocente);
            break;

        case 6:
            _manager.cerrarActaCursada(_legajoDocente);
            break;

        case 7:
            _manager.exportarCSV(_legajoDocente);
            break;

        case 8:
            // Se maneja arriba en mostrar()
            break;

        case 9:
            _manager.editarDocente(_legajoDocente);
            break;

        case 0:
            cout << "Volviendo al menú principal...\n";
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
