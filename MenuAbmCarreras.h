#pragma once

#include "MenuAbmCarreras.h"
#include "CarreraManager.h"

class MenuABMCarreras{
public:
    MenuABMCarreras();
    void mostrar();
protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);


private:
    //PersonalManager _personalManager;
    CarreraManager _carreraManager;
    int _cantidadOpciones;
};

