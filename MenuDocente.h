#pragma once
#include "ManagerDocente.h"

class MenuDocente {
public:
    MenuDocente();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    int _cantidadOpciones;
    ManagerDocente _docenteManager;
};
