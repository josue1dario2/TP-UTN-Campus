#pragma once
#include "ArchivoComision.h"
#include "Comision.h"
#include <iostream>

class ComisionManager {
private:
    ArchivoComision _archivo;

public:
    ComisionManager();

    // Muestra todas las comisiones (por ahora sin filtrar por docente)
    void mostrarTodasLasComisiones();

    // Muestra las comisiones que pertenecen a una materia específica
    void mostrarComisionesPorMateria(int idMateria);
};
