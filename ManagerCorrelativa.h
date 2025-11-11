#pragma once
#include "ArchivoCorrelativa.h"
#include "Correlativa.h"
#include <iostream>
#include <iomanip>

class ManagerCorrelativa {
private:
    ArchivoCorrelativa _archivo;

    void mostrarEncabezado();
    void mostrarRegistro(const Correlativa& reg);
    void mostrarPie();

public:
    ManagerCorrelativa();

    void cargar();
    void listar();
    void borrar();
    void activar();

    bool tieneCorrelativas(int idMateria);
};
