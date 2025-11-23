#pragma once
#include "ArchivoCorrelativa.h"
#include "Correlativa.h"
#include <iostream>

class MenuAbmCorrelativa {
private:
    ArchivoCorrelativa _archivo;

    void mostrarOpciones();
    int seleccionarOpcion();

    void agregarCorrelativa();
    void listarCorrelativas();
    void modificarCorrelativa();
    void bajaLogica();

public:
    MenuAbmCorrelativa();
    void mostrar();
};
