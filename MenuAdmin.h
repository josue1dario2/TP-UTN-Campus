#pragma once

#include "MenuAbmCarreras.h"
#include "MenuAbmComisiones.h"
#include "MenuAbmMaterias.h"
#include "Validacion.h"

class MenuAdministrador{
public:
    MenuAdministrador();
    void mostrar();
protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);



    MenuABMCarreras menuCarreras;
    MenuABMComisiones menuComisiones;
    MenuABMMaterias menuMaterias;
private:
    Validacion validar;
    //PersonalManager _personalManager;
    //mostrarMenuPrincipal();
    int _cantidadOpciones;
};





