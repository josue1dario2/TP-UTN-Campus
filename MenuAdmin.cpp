#include "MenuAdmin.h"
#include "AlumnoAdmin.h"
#include "DocenteAdmin.h"
#include "CarreraAdmin.h"
#include "ComisionesAdmin.h"
#include "MateriasAdmin.h"
#include "Validacion.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuAdministrador::MenuAdministrador()
    : _cantidadOpciones(6)
{

}

void MenuAdministrador::mostrar() {
    int opcion;
    //cin.ignore();
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
    cout << "\t1) Alumno\n";
    cout << "\t2) Carreras\n";
    cout << "\t3) Comisiones\n";
    cout << "\t4) Docente\n";
    cout << "\t5) Materias\n";
    cout << "\t6) Solicitudes\n";
    cout << "\t0) Volver\n";

}

void MenuAdministrador::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:{
            MenuABMAlumnosAdmin _menuABMAlumnosAdmin;
            _menuABMAlumnosAdmin.mostrar();
            break;
        }
        case 2: {
            MenuABMCarrerasAdmin _menuABMCarrerasAdmin; // <--- creamos objeto
            _menuABMCarrerasAdmin.mostrar();  // <--- mostramos menú
            break;
        }

        case 3: {
            MenuABMComisionesAdmin _menuABMComisionesAdmin; // <--- creamos objeto
            _menuABMComisionesAdmin.mostrar();  // <--- mostramos menú

            break;
        }
        case 4: {
            MenuABMDocentesAdmin _menuABMADocentesAdmin;     // <--- creamos objeto
            _menuABMADocentesAdmin.mostrar();  // <--- mostramos menú
            break; // Cambiar Solicitudes
        }
        case 5: {
            MenuABMMateriasAdmin _menuABMMateriasAdmin;     // <--- creamos objeto
            _menuABMMateriasAdmin.mostrar();  // <--- mostramos menú
            break;
        }
        case 6:
            cout << "En proceso de creación";
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
    //if(cin.peek() == '\n') cin.ignore();
    opcion = Validacion::validarEnteroEnRango("",0,_cantidadOpciones);


  return opcion;
}
