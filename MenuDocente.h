#pragma once
#include "ManagerDocente.h"

class MenuDocente {
private:
    int _cantidadOpciones;
    int _legajoDocente;
    ManagerDocente _manager;

public:
    MenuDocente();
    MenuDocente(int legajoDocente);

    void mostrar();
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
};
