#include "MenuAdmin.h"
#include "MenuAbmCarreras.h"
#include "Validacion.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuAdministrador::MenuAdministrador()
    : _cantidadOpciones(4)
{

}

void MenuAdministrador::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuAdministrador::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRADOR – ABM\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Carreras\n";
    cout << "\t2) Materias\n";
    cout << "\t3) Comisiones\n";
    cout << "\t4) Solicitudes\n";
    cout << "\t0) Volver\n";


}

void MenuAdministrador::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            menuCarreras.mostrar();
            break;

        case 2: {
            MenuABMMaterias menuMaterias;     // <--- creamos objeto
            menuMaterias.mostrar();  // <--- mostramos menú
            break;
        }

        case 3:
            //menuABMComisiones();
            break;

        case 4:
            //menuSolicitudes();
            break; // Cambiar Solicitudes

        case 0:
            break;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuAdministrador::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";

    opcion = Validacion::validarEnteroEnRango("",0,_cantidadOpciones);


  return opcion;
}
