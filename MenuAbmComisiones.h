#pragma once

#include "ManagerComision.h"

class MenuABMComisiones {
public:
    MenuABMComisiones();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    int _cantidadOpciones;
};
