#pragma once

#include "Validacion.h"

class MenuDocente{
public:
    MenuDocente();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    Validacion validar;
    //PersonalManager _personalManager;
    int _cantidadOpciones;
    void mostrarSubmenuNotas();
    int seleccionarSubopcionNotas();
};


