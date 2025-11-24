#include "MenuDocente.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Constructor sin parámetros (NECESARIO)
MenuDocente::MenuDocente() {
    _cantidadOpciones = 10;
    _legajoDocente = 0;
}

// Constructor con legajo (LOGIN del docente)
MenuDocente::MenuDocente(int legajoDocente) {
    _cantidadOpciones = 10;
    _legajoDocente = legajoDocente;
}

void MenuDocente::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}

void MenuDocente::mostrarOpciones() {
    cout << "\n\tMENÚ DEL DOCENTE\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Ver Mis Comisiones\n";
    cout << "\t2) Ver Alumnos de una Comisión\n";
    cout << "\t3) Cargar Notas (Parcial / TP)\n";
    cout << "\t4) Publicar Notas de Cursada\n";
    cout << "\t5) Cerrar Acta de Cursada\n";
    cout << "\t6) Ver Mis Mesas de Examen\n";
    cout << "\t7) Cargar Notas de Final\n";
    cout << "\t8) Exportar CSV\n";
    cout << "\t9) Solicitar Baja\n";
    cout << "\t10) Editar Mis Datos\n";
    cout << "\t0) Volver\n";
}

int MenuDocente::seleccionOpcion() {
    mostrarOpciones();
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuDocente::ejecutarOpcion(int opcion) {

    switch (opcion) {
        case 1:
            _manager.verMisComisiones(_legajoDocente);
            break;

        case 2: {
            int idComision = Validacion::validarEntero("\tIngrese ID de comision: ");
            _manager.verAlumnosDeComision(idComision);
            break;
        }

        case 3:
            _manager.cargarNotasParcialTP(_legajoDocente);
            break;

        case 4:
            _manager.publicarNotasCursada(_legajoDocente);
            break;

        case 5:
            _manager.cerrarActaCursada(_legajoDocente);
            break;

        case 6:
            _manager.verMisComisiones(_legajoDocente);
            break;

        case 7:
            _manager.cargarNotasFinal(_legajoDocente);
            break;

        case 8:
            _manager.exportarCSV(_legajoDocente);
            break;

        case 9:
            _manager.solicitarBaja(_legajoDocente);
            break;

        case 10:
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
