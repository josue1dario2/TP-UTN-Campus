#pragma once
#include "ManagerDocente.h"
#include <string>

class MenuDocente {
private:
    int _cantidadOpciones;
    int _legajoDocente;
    std::string _nombreCompleto;
    ManagerDocente _manager;

public:
    MenuDocente();
    MenuDocente(int legajoDocente);

    void mostrar();
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
};
