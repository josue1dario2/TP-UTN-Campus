#pragma once

#include "MenuAdmin.h"
#include "MenuAlumno.h"
#include "menu_docente.h"
#include "MenuUtilitarios.h"
#include "PrincipalManager.h"

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
    PrincipalManager _principalManager;
    mostrarMenuPrincipal();
    int _cantidadOpciones;
};

