#pragma once
#include "ArchivoExamen.h"
#include "Examen.h"
#include "Fecha.h"

class ManagerExamen {
private:
    ArchivoExamen _archivoExamen;

public:
    ManagerExamen();

    // =======================================================
    // ALTAS DE EXÁMENES
    // =======================================================
    void cargarParcial(int legajoAlumno, int idComision, int nota);
    void cargarRecuperatorio(int legajoAlumno, int idComision, int nota);
    void cargarFinal(int legajoAlumno, int idComision, int nota);

    // --- VALIDACIONES ---
    bool puedeRendirFinal(int legajoAlumno, int idComision);
    bool estaPromocionado(int legajoAlumno, int idComision);
    bool estaRegular(int legajoAlumno, int idComision);
    bool estaLibre(int legajoAlumno, int idComision);

    bool finalAprobado(int legajo, int idMateria);

    // Recuperatorios
    bool recuperatorioPendiente(int legajo, int idMateria, int numeroParcial);
    bool recuperatorioYaRendido(int legajo, int idMateria, int numeroParcial);
    void inscribirARecuperatorio(int legajoAlumno);

    // --- REPORTES ---
    void mostrarTodos();
    void mostrarHistorial(int legajoAlumno);
    void recalcularCondicion(int legajoAlumno, int idComision);

    float promedioConReglas(int legajo, int idMateria);
};
