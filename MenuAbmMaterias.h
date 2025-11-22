#pragma once
#include "ManagerMateria.h"

class MenuABMMaterias {
public:
    MenuABMMaterias();
    void mostrarMenuABMMaterias();

private:
    int _cantidadOpciones;
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
};
