#include <iostream>
#include "MenuCopiaSeguridad.h"
#include <cstdlib>

using namespace std;

MenuCopiaSeguridad::MenuCopiaSeguridad()
{
    _cantidadOpciones=11;
}

void MenuCopiaSeguridad::mostrar(int eleccion)
{
    int opcion;
    do{
        system("cls");
        opcion = seleccionOpcion(eleccion);
        system("cls");
        ejecutarOpcion(opcion,eleccion);

    }while(opcion != 0);
    system("pause");
}

void MenuCopiaSeguridad::mostrarOpciones(int eleccion)
{
    system("cls");
    cout << endl;
    if (eleccion == 1) {
        cout << "\tRealizar copia de seguridad\n";
    } else if (eleccion == 2) {
        cout << "\tRestaurar copia de seguridad\n";
    }
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

void MenuCopiaSeguridad::ejecutarOpcion(int opcion, int eleccion)
{

    /*
    1) Realizar copia de seguridad
    2) Restaurar copia de seguridad
    */
    cout << "\n\tNo es el manager";
    switch(eleccion){
    case 1:
        cout << "\n\tRealizando copia de seguridad, opción:" << opcion<<endl;
        //manager.realizarCopiaSeguridad(opcion));
    break;
    case 2:
        cout << "\n\tRestaurando copia de seguridad, opción:" << opcion<<endl;
        //manager.restaurarCopiaSeguridad(opcion));
    break;

    }
}


int MenuCopiaSeguridad::seleccionOpcion(int eleccion)
{
    int opcion;
    mostrarOpciones(eleccion);
    string mensaje="\t--------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);
    return opcion;

}


