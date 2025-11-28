#pragma once

#include "ManagerAlumno.h"
#include "Validacion.h"
#include <string>

class MenuAlumno {
private:
    int _cantidadOpciones;
    int _legajoAlumno;
    std::string _nombreCompleto;
    ManagerAlumno _alumnoManager;

public:
    MenuAlumno(int legajoAlumno);
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
};
