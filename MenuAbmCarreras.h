#pragma once

#include "MenuAbmCarreras.h"

class MenuABMCarreras{
public:
    MenuABMCarreras();
    MenuAdministrador();
    void mostrar();
protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);


    /*
    MenuABMCarreras menuCarreras;
    MenuABMComisiones menuComisiones;
    MenuABMMaterias menuMaterias;
    */
private:
    //PersonalManager _personalManager;
    //mostrarMenuPrincipal();
    int _cantidadOpciones;
};

