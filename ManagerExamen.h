#pragma once
#include "ArchivoExamen.h"
#include "Examen.h"
#include "Fecha.h"

class ManagerExamen {
private:
    ArchivoExamen _archivoExamen;

public:
    ManagerExamen();

    // Altas de exámenes
    void cargarParcial(int legajoAlumno, int idComision, int nota);
    void cargarRecuperatorio(int legajoAlumno, int idComision, int nota);
    void cargarFinal(int legajoAlumno, int idComision, int nota);

    // Consultas académicas
    bool puedeRendirFinal(int legajoAlumno, int idComision);
    bool estaPromocionado(int legajoAlumno, int idComision);
    bool estaRegular(int legajoAlumno, int idComision);
    bool estaLibre(int legajoAlumno, int idComision);

    // Reportes
    void mostrarHistorial(int legajoAlumno);
    void mostrarTodos();
    void recalcularCondicion(int legajoAlumno, int idComision);
};
