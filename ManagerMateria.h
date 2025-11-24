#pragma once
#include "ArchivoMateria.h"
#include "Materia.h"

class ManagerMateria {
private:
    ArchivoMateria _archivo;

public:
    void alta();
    void baja();
    void modificacion();
    void listarTodas();
    int buscarPorId(int idMateria);
    int generarIdNuevo();

};
