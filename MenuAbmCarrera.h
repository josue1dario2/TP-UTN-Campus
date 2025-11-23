#pragma once

#include "MenuAbmCarrera.h"
#include "ManagerCarrera.h"

class MenuAbmCarrera{
public:
    MenuAbmCarrera();
    void mostrar();
protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);


private:
    //PersonalManager _personalManager;
    ManagerCarrera _carreraManager;
    int _cantidadOpciones;
};

