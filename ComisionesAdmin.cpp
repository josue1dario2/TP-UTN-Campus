#include "ComisionesAdmin.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>

using namespace std;

MenuABMComisionesAdmin::MenuABMComisionesAdmin()
    : _cantidadOpciones(5)
{
}

void MenuABMComisionesAdmin::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMComisionesAdmin::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRACIÓN DE COMISIONES\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Comisión\n";
    cout << "\t2) Modificar Comisión\n";
    cout << "\t3) Baja Lógica de Comisión\n";
    cout << "\t4) Activar Comisión\n";
    cout << "\t5) Listar Comisiones\n";
    cout << "\t0) Volver\n";
}

void MenuABMComisionesAdmin::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            altaComision();
            break;
        case 2:
            modificarComision();
            break;
        case 3:
            bajaLogicaComision();
            break;
        case 4:
            activarComision();
            break;
        case 5:
            listarComisiones();
            break;
        case 0:
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuABMComisionesAdmin::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";

    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);

    return opcion;
}

void MenuABMComisionesAdmin::altaComision()
{

    _managerComison.cargar();
    // Implementar lógica de alta
}

void MenuABMComisionesAdmin::modificarComision()
{
    cout << "Modificar Comisión - En desarrollo\n";
    // Implementar lógica de modificación
}

void MenuABMComisionesAdmin::bajaLogicaComision()
{
    cout << "Baja Lógica de Comisión - En desarrollo\n";
    // Implementar lógica de baja
}

void MenuABMComisionesAdmin::activarComision()
{
    cout << "Activar Comisión - En desarrollo\n";
    // Implementar lógica de activación
}

void MenuABMComisionesAdmin::listarComisiones()
{
    _managerComison.listar();
    cout << endl;
    // Implementar lógica de listado
}
