#include "MenuAbmComisiones.h"
#include "Validacion.h"
#include "utils.h"

#include <cstdlib>
#include <iostream>
using namespace std;

MenuABMComisiones::MenuABMComisiones(){
    _cantidadOpciones = 7;
}

void MenuABMComisiones::mostrar()
{
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMComisiones::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tABM COMISIONES\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Comisión\n";
    cout << "\t2) Modificar Comisión\n";
    cout << "\t3) Baja lógica de Comisión\n";
    cout << "\t4) Listar Comisiones\n";
    cout << "\t5) Listar por Materia\n";
    cout << "\t6) Cambiar Cupo\n";
    cout << "\t7) Cambiar Turno/Modalidad/Aula\n";
    cout << "\t0) Volver\n";
}

void MenuABMComisiones::ejecutarOpcion(int opcion)
{
    switch(opcion){
        case 1:

        break;
        case 2:

        break;
        case 3:

        break;
        case 4:

        break;
        case 5:

        break;
        case 6:

        break;
        case 7:

        break;

    }

}

int MenuABMComisiones::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------" << endl;
    cout << "\tOpción: ";

    opcion = Validacion::validarEnteroEnRango("",0,_cantidadOpciones);

    return opcion;

}

