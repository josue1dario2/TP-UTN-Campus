#pragma once
#include "MateriaManager.h"

class MenuABMMaterias {
public:
    MenuABMMaterias();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    MateriaManager _materiaManager;
    int _cantidadOpciones;
};

