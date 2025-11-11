#pragma once
#include "ArchivoInscripcionComision.h"
#include "InscripcionComision.h"
#include <iostream>
#include <iomanip>

class ManagerInscripcionComision {
private:
    ArchivoInscripcionComision _archivo;

    void mostrarEncabezado();
    void mostrarRegistro(const InscripcionComision& reg);
    void mostrarPie();

public:
    ManagerInscripcionComision();

    void cargar();
    void listar();
    void borrar();

    bool estaInscripto(int legajo, int idComision);
};
