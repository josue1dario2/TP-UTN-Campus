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
    void cargarParcial(int legajoAlumno, int idMateria, int nota);
    void cargarRecuperatorio(int legajoAlumno, int idMateria, int nota);
    void cargarFinal(int legajoAlumno, int idMateria, int nota);

    // Consultas académicas
    bool puedeRendirFinal(int legajoAlumno, int idMateria);
    bool estaPromocionado(int legajoAlumno, int idMateria);
    bool estaRegular(int legajoAlumno, int idMateria);
    bool estaLibre(int legajoAlumno, int idMateria);

    // Reportes
    void mostrarHistorial(int legajoAlumno);
    void recalcularCondicion(int legajoAlumno, int idMateria);
};
