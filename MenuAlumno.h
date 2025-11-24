#pragma once

#include "ManagerAlumno.h"
#include "Validacion.h"

class MenuAlumno {
private:
    int _cantidadOpciones;
    int _legajoAlumno;
    ManagerAlumno _alumnoManager;

public:
    MenuAlumno(int legajoAlumno);
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
};
