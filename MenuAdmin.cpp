#include "MenuAdmin.h"


#include <iostream>
#include <cstdlib>
using namespace std;

MenuAdministrador::MenuAdministrador(){
    _cantidadOpciones = 5;
}

void MenuAdministrador::mostrar() {
    int opcion;

    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);

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
            //menuCarreras.mostrarMenuABMCarreras();
            break;
        case 2:
            //menuABMMaterias();
            break;
        case 3:
            //menuABMComisiones();
            break;
        case 4:
            //menuABMComisiones();
            break; // Cambiar Solicitudes
        case 0:
            break;
        default: cout << "Opción inválida.\n"; break;
    }
}

int MenuAdministrador::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
    cout << "\tOpcion incorrecta..."<<endl;
    cout << "\tOpción: ";
    cin >> opcion;
  }
  return opcion;
}
