#include "MateriasAdmin.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>

using namespace std;

MenuABMMateriasAdmin::MenuABMMateriasAdmin()
    : _cantidadOpciones(5)
{
}

void MenuABMMateriasAdmin::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMMateriasAdmin::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRACIÓN DE MATERIAS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Materia\n";
    cout << "\t2) Modificar Materia\n";
    cout << "\t3) Baja Lógica de Materia\n";
    cout << "\t4) Activar Materia\n";
    cout << "\t5) Listar Materias\n";
    cout << "\t0) Volver\n";
}

void MenuABMMateriasAdmin::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            altaMateria();
            break;
        case 2:
            modificarMateria();
            break;
        case 3:
            bajaLogicaMateria();
            break;
        case 4:
            activarMateria();
            break;
        case 5:
            listarMaterias();
            break;
        case 0:
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuABMMateriasAdmin::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";
    //if(cin.peek() == '\n') cin.ignore();
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);

    return opcion;
}

void MenuABMMateriasAdmin::altaMateria()
{
    _managerMateria.alta();
}

void MenuABMMateriasAdmin::modificarMateria()
{

    _managerMateria.modificacion();
}

void MenuABMMateriasAdmin::bajaLogicaMateria()
{
    _managerMateria.borrar();

}

void MenuABMMateriasAdmin::activarMateria()
{
    _managerMateria.activar();

}

void MenuABMMateriasAdmin::listarMaterias()
{
    _managerMateria.listar();

}
