#pragma once

#include "ManagerAlumno.h"
#include "Validacion.h"

class MenuAlumno {
private:
    int _cantidadOpciones;
    ManagerAlumno _alumnoManager;

public:
    MenuAlumno();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
};
