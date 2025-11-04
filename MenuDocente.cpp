#include "Validacion.h"
#include "MenuDocente.h"
#include "DocenteManager.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;

MenuDocente::MenuDocente() {
    _cantidadOpciones = 10;
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
    cout << endl;
    cout << "\n\tMENÚ DEL DOCENTE\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Ver Mis Comisiones\n";
    cout << "\t2) Ver Alumnos de una Comisión\n";
    cout << "\t3) Cargar Notas (Parcial/TP)\n";
    cout << "\t4) Publicar Notas de Cursada\n";
    cout << "\t5) Cerrar Acta de Cursada\n";
    cout << "\t6) Ver Mis Mesas de Examen\n";
    cout << "\t7) Cargar Notas de Final\n";
    cout << "\t8) Exportar CSV (mis comisiones/mesas)\n";
    cout << "\t9) Solicitar baja (cerrar legajo)\n";
    cout << "\t10) Editar mis datos\n";
    cout << "\t0) Volver\n";
    cout << "\t--------------------------------\n";
}

int MenuDocente::seleccionOpcion() {
    int opcion;
    mostrarOpciones();
    cout << "\tOpción: ";
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
    return opcion;
}

void MenuDocente::ejecutarOpcion(int opcion) {
    DocenteManager docenteManager;
    int legajo = 0;
    int idComision = 0;

    switch (opcion) {
        case 1:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.verMisComisiones(legajo);
            break;
        case 2:
            cout << "Ingrese ID de comisión: ";
            cin >> idComision;
            docenteManager.verAlumnosDeComision(idComision);
            break;
        case 3:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.cargarNotasParcialTP(legajo);
            break;
        case 4:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.publicarNotasCursada(legajo);
            break;
        case 5:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.cerrarActaCursada(legajo);
            break;
        case 6:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.verMisComisiones(legajo);
            break;
        case 7:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.cargarNotasFinal(legajo);
            break;
        case 8:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.exportarCSV(legajo);
            break;
        case 9:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.solicitarBaja(legajo);
            break;
        case 10:
            cout << "Ingrese su legajo: ";
            cin >> legajo;
            docenteManager.editarDocente(legajo);
            break;
        case 0:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}
