#pragma once
#include "ArchivoAlumno.h"
#include "ArchivoMateria.h"
#include "ArchivoComision.h"
#include "ArchivoInscripcionComision.h"
#include "ArchivoExamen.h"
#include "ArchivoDocente.h"
#include "ManagerExamen.h"
#include <iostream>

class ManagerReportes {
private:
    ArchivoAlumno _archivoAlumnos;
    ArchivoMateria _archivoMaterias;
    ArchivoComision _archivoComisiones;
    ArchivoInscripcionComision _archivoInscripciones;
    ArchivoExamen _archivoExamenes;
    ArchivoDocente _archivoDocentes;
    ManagerExamen _managerExamen;

    // Funciones auxiliares privadas
    float calcularPromedioAlumno(int legajo);
    int contarMateriasAprobadas(int legajo);
    int contarMateriasPromocionadas(int legajo);
    int contarMateriasRegulares(int legajo);
    int contarMateriasLibres(int legajo);
    int contarInscriptosEnComision(int idComision);

public:
    ManagerReportes();

    // ===== ALTA PRIORIDAD =====
    void reporteRendimientoAcademico(int legajo);
    void listadoAlumnosPorComision(int idComision);
    void estadisticasPorMateria(int idMateria);
    void finalesPendientesPorAlumno(int legajo);
    void reporteComisionesPorCupo();

    // ===== MEDIA PRIORIDAD =====
    void rankingAlumnosPorPromedio();
    void calendarioFinales();
    void historialNotasPorMateria(int legajo, int idMateria);
    void alumnosEnRiesgoAcademico();
    void cargaHorariaDocentes();

    // ===== BAJA PRIORIDAD (ANALÍTICOS) =====
    void tasaAprobacionPorCuatrimestre();
    void materiasConMayorIndiceLibre();
    void tiempoPromedioCarrera();
};
