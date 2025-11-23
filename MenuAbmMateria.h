#pragma once
#include "ManagerMateria.h"
#include "MenuAbmCorrelativa.h"

class MenuAbmMateria {
public:
    MenuAbmMateria();
    void mostrarMenuABMMaterias();

private:
    int _cantidadOpciones;
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    MenuAbmCorrelativa menuCorrelativa;
    void mostrarCorrelativasDeMateria(int idMateria);
};
