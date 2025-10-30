#include <iostream>
#include "MenuDatosCSV.h"
#include <cstdlib>

using namespace std;

MenuDatosCSV::MenuDatosCSV()
{
    _cantidadOpciones=11;

}

void MenuDatosCSV::mostrar()
{
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);

    }while(opcion != 0);
    system("pause");
}

void MenuDatosCSV::mostrarOpciones()
{
    system("cls");
    cout << endl;
    cout << "\n\tEXPORTAR DATOS A ARCHIVO CSV\n";
    cout << "\t--------------------------------------\n";
    cout << "\t 1 - ALUMNOS\n";
    cout << "\t 2 - DOCENTES\n";
    cout << "\t 3 - CARRERAS\n";
    cout << "\t 4 - MATERIAS\n";
    cout << "\t 5 - COMISIONES\n";
    cout << "\t 6 - INSCRIPCIONES\n";
    cout << "\t 7 - MESAS DE EXAMEN\n";
    cout << "\t 8 - EVALUACIONES\n";
    cout << "\t 9 - CALIFICACIONES\n";
    cout << "\t10 - CORRELATIVAS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t11 - TODOS LOS ARCHIVOS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t0 - Volver\n";

}

void MenuDatosCSV::ejecutarOpcion(int opcion)
{
    // Borrar y reemplazar por manager
    if (opcion !=0){
        cout << "\n\tBorrar y reemplazar por manager, opcion: " << opcion << endl;
        // managerExportardatos(opcion)
    }

}

int MenuDatosCSV::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    string mensaje="\t--------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);
    return opcion;

}




