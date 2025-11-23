#include "MenuAbmCarrera.h"
#include "ManagerCarrera.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MenuAbmCarrera::MenuAbmCarrera(){
    _cantidadOpciones=5;
}

void MenuAbmCarrera::mostrar(){
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}


void MenuAbmCarrera::mostrarOpciones() {
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

void MenuAbmCarrera::ejecutarOpcion(int opcion){
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


int MenuAbmCarrera::seleccionOpcion(){

    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n" << endl;
    cout << "\tOpcion: ";

    opcion = Validacion::validarEnteroEnRango("",0,_cantidadOpciones);

    return opcion;
}


