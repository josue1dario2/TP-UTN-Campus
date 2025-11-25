#include "MenuAbmMateria.h"
#include "ArchivoCorrelativa.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
using namespace std;

MenuAbmMateria::MenuAbmMateria() {
    _cantidadOpciones = 7;
}

void MenuAbmMateria::mostrarMenuABMMaterias() {
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
void MenuAbmMateria::mostrarCorrelativasDeMateria(int idMateria) {
    clearScreen();
    cout << "\n=== CORRELATIVAS DE LA MATERIA " << idMateria << " ===\n\n";

    ArchivoCorrelativa arch("Correlativas.dat");

    arch.listarDeMateria(idMateria);

    cout << "\n";
    pauseScreen();
}


void MenuAbmMateria::mostrarOpciones() {
    cout << "\n\tABM DE MATERIAS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t1) Alta de Materia\n";
    cout << "\t2) Modificar Materia\n";
    cout << "\t3) Baja lógica de Materia\n";
    cout << "\t4) Activar Materia\n";
    cout << "\t5) Listar Materias\n";
    cout << "\t6) Configurar Correlativas\n";
    cout << "\t7) Ver correlativas de la materia\n";
    cout << "\t0) Volver\n";
}

int MenuAbmMateria::seleccionOpcion() {
    mostrarOpciones();
    cout << "\t--------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAbmMateria::ejecutarOpcion(int opcion) {
    ManagerMateria manager;

    switch (opcion) {

        case 1:
            manager.alta();
            break;

        case 2:
            manager.modificacion();
            break;

        case 3:
            manager.baja();
            break;

        case 4:
            manager.activar();
            break;
        case 5:
            manager.listarTodas();
            break;

        case 6:
            menuCorrelativa.mostrar();
            break;

        case 7: {
            int idMat = Validacion::validarEntero("\tIngrese ID de materia: ");
            mostrarCorrelativasDeMateria(idMat);
            break;
        }

        default:
            cout << "\n\tOpción inválida.\n";
            break;
    }
}
