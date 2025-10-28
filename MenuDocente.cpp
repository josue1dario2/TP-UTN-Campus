#include "MenuDocente.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuDocente::MenuDocente()
{
    _cantidadOpciones=10;
}

void MenuDocente::mostrar()
{
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    }while(opcion != 0);
}

void MenuDocente::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ DEL DOCENTE\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Ver Mis Comisiones\n";
    cout << "\t2) Ver Alumnos de una Comisión\n";
    cout << "\t3) Cargar Notas (Parcial/TP)\n";
    cout << "\t4) Publicar Notas de Cursada\n";
    cout << "\t5) Cerrar Acta de Cursada\n";
    cout << "\t6) Ver Mis Mesas de Examen\n";
    cout << "\t7) Cargar Notas de Final\n";
    cout << "\t8) Exportar CSV (mis comisiones/mesas)\n";
    cout << "\t9) Solicitar baja (cerrar legajo)\n";
    cout << "\t10) Editar mis datos\n";
    cout << "\t0) Volver\n";
}

void MenuDocente::ejecutarOpcion(int opcion)
{
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
    case 5:

    break;
    case 6:

    break;
    case 7:

    break;
    case 8:

    break;
    case 9:

    break;
    case 10:

    break;
    }
}
int MenuDocente::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();

    string mensaje="\t----------------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);


    return opcion;

}



