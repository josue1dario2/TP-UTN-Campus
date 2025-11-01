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
    AlumnoManager _alumnoManager;
    Validacion validar;
    //PersonalManager _personalManager;
    int _cantidadOpciones;

};

