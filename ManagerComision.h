#pragma once
#include "ArchivoComision.h"
#include "ArchivoMateria.h"
#include "ArchivoDocente.h"
#include "Comision.h"

class ManagerComision {
private:
    ArchivoComision _archivo;
    ArchivoMateria _archMaterias;
    ArchivoDocente _archDocentes;

    // Helpers
    void listarEncabezado();
    void listarRegistro(const Comision& c);
    void listarPie();

    bool obtenerComisionValida(int id, Comision& out);
    bool existeIDMateria(int idMateria);
    bool existeLegajoDocente(int legajo);

    int generarIDComision();

public:

    // ABM
    void alta();
    void modificar();
    void borrar();
    void activar();

    // Listados
    void listarComisiones();
    void listarPorMateria();

    // Auxiliar
    void mostrarComisionesActivas();
    void mostrarComisionesInactivas();
    bool existeComision(int idComision);
    string nombreCompletoDocente(int legajo);

};
