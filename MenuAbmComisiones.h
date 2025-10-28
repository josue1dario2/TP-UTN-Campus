#pragma once
#include "Validacion.h"

class MenuABMComisiones{
public:
    MenuABMComisiones();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);


    /*
    MenuUtilitarios menu;
    MenuAlumno menuAlumno;
    MenuDocente menuDocente;
    MenuAdministrador menuAdministrador;
    */

private:
    Validacion validar;
    //PrincipalManager _principalManager;
    //mostrarMenuPrincipal();
    int _cantidadOpciones;
};


