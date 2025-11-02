#include "Validacion.h"
#include "MenuPrincipal.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuPrincipal::MenuPrincipal(){
    _cantidadOpciones=4;

}


void MenuPrincipal::mostrar()  {
    int opcion;

    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    } while (opcion !=0);

}

void MenuPrincipal::mostrarOpciones()
{
        cout << endl;
        cout << "\n\tSISTEMA DE GESTIÓN DE CAMPUS – MENÚ PRINCIPAL\n";
        cout << "\t----------------------------------------------\n";
        cout << "\t1 - Alumno\n";
        cout << "\t2 - Docente\n";
        cout << "\t3 - Administrador\n";
        cout << "\t4 - Utilitarios\n";
        cout << "\t----------------------------------------------\n";
        cout << "\t0 - Salir\n";


}

void MenuPrincipal::ejecutarOpcion(int opcion){
    switch (opcion) {
        case 1: menuAlumno.mostrar(); break;
        case 2: menuDocente.mostrar(); break;
        case 3: menuAdministrador.mostrar(); break;
        case 4: menu.mostrarMenuPrincipal(); break;
        case 0: cout << "Saliendo...\n"; break;
        default: cout << "Opción inválida.\n"; break;
        }
}

int MenuPrincipal::seleccionOpcion(){
    int opcion;
    mostrarOpciones();
    cout << "\t----------------------------------------------"<<endl;
    cout << "\tOpción: ";
    opcion = Validacion::validarEnteroEnRango("",0,_cantidadOpciones);
    return opcion;






}




