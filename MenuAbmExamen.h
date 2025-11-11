#pragma once
#include "ManagerExamen.h"

class MenuAbmExamen {
public:
    MenuAbmExamen();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    ManagerExamen _managerExamen;
    int _cantidadOpciones;
};
