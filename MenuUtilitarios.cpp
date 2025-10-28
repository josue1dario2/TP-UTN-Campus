#include <iostream>
#include "MenuUtilitarios.h"
#include <cstdlib>

using namespace std;

MenuUtilitarios::MenuUtilitarios()
{
    _cantidadOpciones=3;
    _cantidadOpcionesSeguridad=11;
}

void MenuUtilitarios::mostrar()
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

void MenuUtilitarios::mostrarOpciones()
{
    system("cls");
    cout << endl;
    cout << "\n\tMENÚ UTILITARIOS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t1 - Realizar copia de seguridad\n";
    cout << "\t2 - Restaurar copia de seguridad\n";
    cout << "\t3 - Exportar datos (CSV)\n";
    cout << "\t--------------------------------------\n";
    cout << "\t0 - Volver\n";

}

void MenuUtilitarios::mostrarOpcionesSeguridad()
{
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
}

void MenuUtilitarios::ejecutarOpcion(int opcion)
{
    switch(opcion){
    case 1:
        realizarCopiaSeguridad();
    break;
    case 2:
        restaurarCopiaSeguridad();
    break;
    case 3:
        exportarDatosCSV();
    break;
    }
}
int MenuUtilitarios::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    string mensaje="\t--------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);
    return opcion;

}


void MenuUtilitarios::realizarCopiaSeguridad() {
    int opcion;
    do {
        system("cls");
        cout << "\n\tREALIZAR COPIA DE SEGURIDAD\n";
        cout << "\t--------------------------------------\n";
        mostrarOpcionesSeguridad();
        cout << "\t--------------------------------------\n";
        cout << "\t 0 - SALIR\n";
        cout << "\tSeleccione una opción: ";
        opcion = validar.validarEnteroEnRango("",0,_cantidadOpcionesSeguridad);
        system("cls");
        // Reemplazar Manager
        cout << "\n\n\tRealizando copia de seguridad para opción " << opcion << "...\n";
        system("pause");
    } while (opcion != 0);

}


void MenuUtilitarios::restaurarCopiaSeguridad() {
    int opcion;
    do {
        system("cls");
        cout << "\n\tRESTAURAR COPIA DE SEGURIDAD\n";
        cout << "\t--------------------------------------\n";
        mostrarOpcionesSeguridad();
        cout << "\t--------------------------------------\n";
        cout << "\t 0 - SALIR\n";
        cout << "\tSeleccione una opción: ";
        opcion = validar.validarEnteroEnRango("",0,_cantidadOpcionesSeguridad);
        system("cls");
        // Reemplazar Manager
        cout << "\n\n\tRestaurando copia de seguridad para opción " << opcion << "...\n";
        system("pause");

    } while (opcion != 0);

}

void MenuUtilitarios::exportarDatosCSV() {
    int opcion;
    do {
        system("cls");
        cout << "\n\tEXPORTAR ARCHIVOS CSV\n";
        cout << "\t--------------------------------------\n";
        mostrarOpcionesSeguridad();
        cout << "\t--------------------------------------\n";
        cout << "\t 0 - SALIR\n";
        cout << "\tSeleccione una opción: ";
        opcion = validar.validarEnteroEnRango("",0,_cantidadOpcionesSeguridad);
        system("cls");

        // Reemplazar Manager
        cout << "\n\n\tRestaurando copia de seguridad para opción " << opcion << "...\n";
        system("pause");
    } while (opcion != 0);

}
