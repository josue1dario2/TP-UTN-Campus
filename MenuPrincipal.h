#pragma once

#include "MenuAdmin.h"
#include "MenuAlumno.h"
#include "MenuDocente.h"
#include "MenuUtilitarios.h"
#include "PrincipalManager.h"
#include "Validacion.h"

class MenuPrincipal{
public:
    MenuPrincipal();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    MenuUtilitarios menuUtil;
    MenuAlumno menuAlumno;
    MenuDocente menuDocente;
    MenuAdministrador menuAdministrador;


private:
    Validacion validar;
    PrincipalManager _principalManager;
    //mostrarMenuPrincipal();
    int _cantidadOpciones;
};

