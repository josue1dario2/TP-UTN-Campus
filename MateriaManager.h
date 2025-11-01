#pragma once
#include "ArchivoMateria.h"
#include "Materia.h"

class MateriaManager {
private:
    ArchivoMateria _archivo;

public:
    void alta();
    void baja();
    void modificacion();
    void listarTodas();

private:
    int generarIdNuevo();
    int buscarPorId(int idMateria);
};