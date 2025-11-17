#pragma once
#include "DocenteManager.h"

class MenuDocente{
public:
    MenuDocente();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:

    DocenteManager _docenteManager;
    int _cantidadOpciones;

};


