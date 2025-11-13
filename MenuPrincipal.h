#pragma once

#include "MenuAdmin.h"
#include "MenuAlumno.h"
#include "MenuDocente.h"
#include "MenuUtilitarios.h"

class MenuPrincipal{
public:
    MenuPrincipal();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);



    MenuUtilitarios menu;
    MenuAlumno menuAlumno;
    MenuDocente menuDocente;
    MenuAdministrador menuAdministrador;


private:
    int _cantidadOpciones;
};

