#include "MenuAbmMaterias.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MenuABMMaterias::MenuABMMaterias() {
    _cantidadOpciones = 7;
}

void MenuABMMaterias::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}

void MenuABMMaterias::mostrarOpciones() {
    cout << endl;
    cout << "\n\tABM MATERIAS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Materia\n";
    cout << "\t2) Modificar Materia\n";
    cout << "\t3) Baja lógica de Materia\n";
    cout << "\t4) Activar materia dada de baja\n";
    cout << "\t5) Listar Materias\n";
    cout << "\t6) Asignar/Modificar Docente Titular (opcional)\n";
    cout << "\t7) Configurar Correlativas (opcional)\n";
    cout << "\t0) Volver\n";
}

void MenuABMMaterias::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1:
            _materiaManager.cargar();
            break;
        case 2:
            _materiaManager.modificar();
            break;
        case 3:
            _materiaManager.borrar();
            break;
        case 4:
            _materiaManager.activar();
            break;
        case 5:
            _materiaManager.listar();
            break;
        case 6:
            cout << "Funcionalidad opcional (Docente Titular)\n";
            break;
        case 7:
            cout << "Funcionalidad opcional (Correlativas)\n";
            break;
        case 0:
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuABMMaterias::seleccionOpcion() {
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n" << endl;
    cout << "\tOpcion: ";
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
    return opcion;
}
