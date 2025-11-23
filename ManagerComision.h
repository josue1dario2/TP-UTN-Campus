#pragma once
#include "ArchivoComision.h"
#include "ArchivoMateria.h"
#include "ManagerMateria.h"
#include "ArchivoDocente.h"
#include "Comision.h"
#include "Validacion.h"
#include <iostream>
#include <iomanip>

class ManagerComision {
private:
    ArchivoComision _archivo;
    ArchivoMateria _archivoMateria;
    ManagerMateria _managerMateria;
    ArchivoDocente _archivoDocentes;


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
};
