#pragma once
#include "ArchivoExamen.h"
#include "Examen.h"
#include "Fecha.h"

class ManagerExamen {
private:
    ArchivoExamen _archivoExamen;

    // Métodos auxiliares
    bool _yaUsoRecuperatorio(int legajoAlumno, int idComision, int numeroParcial);
    bool _existeExamen(int legajoAlumno, int idComision, const char* tipo, int numero);

public:
    ManagerExamen();

    // Altas de exámenes
    void cargarParcial(int legajoAlumno, int idComision, int numeroParcial, int nota);
    void cargarRecuperatorio(int legajoAlumno, int idComision, int numeroParcial, int nota);
    void cargarFinal(int legajoAlumno, int idComision, int nota);

    // Consultas de condición académica
    bool puedeRendirFinal(int legajoAlumno, int idComision);
    bool estaPromocionado(int legajoAlumno, int idComision);
    bool estaRegular(int legajoAlumno, int idComision);
    bool estaLibre(int legajoAlumno, int idComision);

    // Reportes
    void mostrarHistorial(int legajoAlumno);
    void recalcularCondicion(int legajoAlumno, int idComision);
};
