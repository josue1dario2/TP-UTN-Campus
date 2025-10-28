#include "MenuABMComisiones.h"

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
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    } while (opcion !=0);
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
    opcion = validar.validarEntero("");

    while(opcion < 0 || opcion > _cantidadOpciones){
        cout << "Opcion incorrecta..."<<endl;
        cout << "Opcion: ";
        opcion = validar.validarEntero("");
    }
    return opcion;

}

