#pragma once
#include "ManagerAlumno.h"

class MenuABMAlumnosAdmin {
public:
    MenuABMAlumnosAdmin();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);
    void buscarAlumnoLegajo();

    int pedirLegajoAlumno(const std::string& mensaje, ArchivoAlumno _archivoAlumno);
    void altaAlumno();
    void modificarAlumno();
    void bajaLogicaAlumno();
    void activarAlumno();
    void listarAlumnos();

private:
    int _cantidadOpciones;
    ManagerAlumno _alumnoManager;

};
