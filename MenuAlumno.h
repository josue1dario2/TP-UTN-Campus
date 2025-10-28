#pragma once
#include "Validacion.h"

class MenuAlumno{
public:
    MenuAlumno();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    Validacion validar;
    //PersonalManager _personalManager;
    int _cantidadOpciones;

};

