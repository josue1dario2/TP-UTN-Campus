#pragma once
#include "Examen.h"
#include "ArchivoExamen.h"
#include <iostream>

class ExamenManager {
private:
    ArchivoExamen _archivoExamen;

    /**
     * Verifica si el alumno ya usó un recuperatorio
     * para un parcial específico dentro de la misma comisión.
     * Ejemplo: si tipoExamen=4,5,6 corresponden a parciales 1,2,3.
     */
    bool _yaUsoRecuperatorio(int legajoAlumno, int idComision, int numeroParcial);

    /**
     * Verifica si ya existe un examen de cierto tipo
     * (parcial, recuperatorio o final) para un alumno en una comisión.
     */
    bool _existeExamen(int legajoAlumno, int idComision, int tipoExamen);

public:
    ExamenManager();

    // --- Carga de notas ---
    /**
     * Registra un parcial (tipoExamen 1–3)
     */
    void cargarParcial(int legajoAlumno, int idComision, int numeroParcial, int nota);

    /**
     * Registra un recuperatorio (tipoExamen 4–6)
     */
    void cargarRecuperatorio(int legajoAlumno, int idComision, int numeroParcial, int nota);

    /**
     * Registra un examen final (tipoExamen = 7)
     */
    void cargarFinal(int legajoAlumno, int idComision, int nota);

    // --- Evaluaciones académicas ---
    bool puedeRendirFinal(int legajoAlumno, int idComision);
    bool estaPromocionado(int legajoAlumno, int idComision);
    bool estaRegular(int legajoAlumno, int idComision);
    bool estaLibre(int legajoAlumno, int idComision);

    // --- Consultas y reportes ---
    void mostrarHistorial(int legajoAlumno);
    void recalcularCondicion(int legajoAlumno, int idComision);
};
