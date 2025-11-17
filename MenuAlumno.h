#pragma once
#include "AlumnoManager.h"
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
    //PersonalManager _personalManager;
    int _cantidadOpciones;
    AlumnoManager _alumnoManager;
};

