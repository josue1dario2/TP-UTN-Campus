#include "MenuAbmCarreras.h"
#include "CarreraManager.h"
#include "Validacion.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MenuABMCarreras::MenuABMCarreras(){
    _cantidadOpciones=5;
}

void MenuABMCarreras::mostrar(){
    int opcion;
    do{
        system("cls");
        //cin.ignore(10000, '\n');
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}


void MenuABMCarreras::mostrarOpciones() {
    cout << endl;
    cout << "\n\tABM CARRERAS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Carrera\n";
    cout << "\t2) Modificar Carrera\n";
    cout << "\t3) Baja lógica de Carrera\n";
    cout << "\t4) Activar Carrera\n";
    cout << "\t5) Listar Carreras\n";
    cout << "\t0) Volver\n";
}

void MenuABMCarreras::ejecutarOpcion(int opcion){
  switch(opcion){
    case 1:
        _carreraManager.cargar();
        break;
    case 2:
        _carreraManager.modificar();
        break;
    case 3:
        _carreraManager.borrar();
        break;
    case 4:
        _carreraManager.activar();
        break;
    case 5:
        _carreraManager.listar();
        break;
  }
}


int MenuABMCarreras::seleccionOpcion(){

    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n" << endl;
    cout << "\tOpcion: ";

    opcion = Validacion::validarEnteroEnRango("",0,_cantidadOpciones);

    return opcion;
}


