#include "CarreraAdmin.h"

#include "Validacion.h"
#include "utils.h"
#include <iostream>

using namespace std;

MenuABMCarrerasAdmin::MenuABMCarrerasAdmin()
    : _cantidadOpciones(5)
{
}

void MenuABMCarrerasAdmin::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMCarrerasAdmin::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRACIÓN DE CARRERAS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Carrera\n";
    cout << "\t2) Modificar Carrera\n";
    cout << "\t3) Baja Lógica de Carrera\n";
    cout << "\t4) Activar Carrera\n";
    cout << "\t5) Listar Carreras\n";
    cout << "\t0) Volver\n";
}

void MenuABMCarrerasAdmin::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            altaCarrera();
            break;
        case 2:
            modificarCarrera();
            break;
        case 3:
            bajaLogicaCarrera();
            break;
        case 4:
            activarCarrera();
            break;
        case 5:
            listarCarreras();
            break;
        case 0:
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuABMCarrerasAdmin::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";
    //if(cin.peek() == '\n') cin.ignore();
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);

    return opcion;
}

void MenuABMCarrerasAdmin::altaCarrera()
{
    _carreraManager.cargar();
}

void MenuABMCarrerasAdmin::modificarCarrera()
{
    _carreraManager.modificar();
}

void MenuABMCarrerasAdmin::bajaLogicaCarrera()
{
    _carreraManager.borrar();
}

void MenuABMCarrerasAdmin::activarCarrera()
{
    _carreraManager.activar();
}

void MenuABMCarrerasAdmin::listarCarreras()
{
    //ManagerCarrera _carreraManager;
    _carreraManager.listar();

}

