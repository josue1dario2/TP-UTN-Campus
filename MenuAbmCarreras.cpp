#include "MenuAbmCarreras.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MenuAbmCarreras::MenuAbmCarreras(){
    _cantidadOpciones=4;
}

void MenuAbmCarreras::mostrar(){
int opcion;

  do{
    system("cls");
    opcion = seleccionOpcion();
    system("cls");
    ejecutarOpcion(opcion);
    system("pause");
  }while(opcion != 0);
}


void MenuAbmCarreras::mostrarOpciones() {
    cout << endl;
    cout << "\n\tABM CARRERAS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Carrera\n";
    cout << "\t2) Modificar Carrera\n";
    cout << "\t3) Baja lógica de Carrera\n";
    cout << "\t4) Listar Carreras\n";
    cout << "\t0) Volver\n";


}

void MenuAbmCarreras::ejecutarOpcion(int opcion){
  switch(opcion){
  case 1:
    //_personalManager.cargar();
  break;
  case 2:
   //_personalManager.mostrar();
  break;
  case 3:

  break;
  case 4:

  break;
  }
}


int MenuAbmCarreras::seleccionOpcion(){

    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n" << endl;
    cout << "\tOpcion: ";
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
      cout << "\tOpcion incorrecta..."<<endl;
      cout << "\tOpcion: ";
      cin >> opcion;
    }
    return opcion;
}


