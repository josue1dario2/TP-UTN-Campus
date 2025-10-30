#pragma once
#include "AlumnoManager.h"

class MenuAlumno{
public:
    MenuAlumno();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    AlumnoManager _alumnoManager;
    int _cantidadOpciones;

};

