#pragma once
#include "Docente.h"
#include "ArchivoDocente.h"
#include "ArchivoComision.h"
#include "ExamenManager.h"
#include "ArchivoExamen.h"
#include "ArchivoMateria.h"
#include "ArchivoInscripcionComision.h"
#include <iostream>

class DocenteManager {
private:
    ArchivoDocente _archivoDocentes;
    ArchivoComision _archivoComisiones;
    ArchivoInscripcionComision _archivoInscripciones;
    ArchivoExamen _archivoExamen;
    ArchivoMateria _archivoMaterias;
    ExamenManager _examenManager;

public:
    DocenteManager();

    // CRUD y gestión del docente
    void listarDocentes();
    void mostrarDocentePorLegajo(int legajo);
    void editarDocente(int legajo);
    void solicitarBaja(int legajo);

    // Operaciones académicas
    void verMisComisiones(int legajo);
    void verAlumnosDeComision(int idComision);
    void cargarNotasParcialTP(int legajoDocente);
    void cargarNotasFinal(int legajoDocente);
    void publicarNotasCursada(int legajoDocente);
    void cerrarActaCursada(int legajoDocente);
    void exportarCSV(int legajoDocente);
};
