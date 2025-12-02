#pragma once
#include "ManagerCorrelativa.h"

class MenuAbmCorrelativa {
private:
    ManagerCorrelativa _manager;

    void mostrarOpciones();
    int seleccionarOpcion();

public:
    MenuAbmCorrelativa();
    void mostrar();
};

