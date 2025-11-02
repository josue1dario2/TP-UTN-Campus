#pragma once
#include "Validacion.h"
#include "ArchivoComision.h"

class MenuAbmComisiones{
public:
    MenuAbmComisiones();
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
    ArchivoComision _archivoComision;
    Validacion validar;
    //PrincipalManager _principalManager;
    //mostrarMenuPrincipal();
    int _cantidadOpciones;
};


