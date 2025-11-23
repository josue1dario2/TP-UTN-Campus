#pragma once
#include "ArchivoComision.h"
#include "Comision.h"
#include "Validacion.h"
#include <iostream>
#include <iomanip>

class ManagerComision {
private:
    ArchivoComision _archivo;

    void mostrarEncabezado();
    void mostrarRegistro(const Comision& c);
    void mostrarPie();
    Comision ingresarDatos(int idComision);

public:
    ManagerComision();

    void cargar();
    void listar();
    void modificar();
    void borrar();
    void activar();

    void mostrarTodasLasComisiones();
    void mostrarComisionesPorMateria(int idMateria);
    bool existeComision(int idComision);
};
