#include "MenuAlumno.h"

#include <iostream>
#include <cstdlib>
using namespace std;

MenuAlumno::MenuAlumno()
{
    _cantidadOpciones = 11;
}

void MenuAlumno::mostrar()
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

void MenuAlumno::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ DEL ALUMNO\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Inscripción a Materia (Comisión)\n";
    cout << "\t2) Inscripción a Examen\n";
    cout << "\t3) Ver Materias Aprobadas\n";
    cout << "\t4) Ver Materias Pendientes\n";
    cout << "\t5) Ver Mis Comisiones\n";
    cout << "\t6) Ver Mis Mesas\n";
    cout << "\t7) Dar de Baja Inscripción a Materia\n";
    cout << "\t8) Dar de Baja Inscripción a Mesa/Final\n";
    cout << "\t9) Ver Mis Notas / Historial\n";
    cout << "\t10) Solicitud de baja\n";
    cout << "\t11) Editar mis datos\n";
    cout << "\t0) Volver\n";
}

void MenuAlumno::ejecutarOpcion(int opcion)
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
    case 11:

    break;
  }

}

int MenuAlumno::seleccionOpcion() {
    int opcion;
    mostrarOpciones();

    string mensaje="\t----------------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);


    /*
    cout << "\t--------------------------------" << endl;
    cout << "\tOpción: ";
    cin >> opcion;

    while(opcion < 0 || opcion > _cantidadOpciones){
      cout << "\tOpcion incorrecta..."<<endl;
      cout << "\tOpcion: ";
      cin >> opcion;
    }
    */
    return opcion;

}
