#pragma once
#include "Docente.h"
#include "ArchivoDocente.h"
#include "ArchivoComision.h"
#include "ArchivoInscripcionComision.h"
#include "ArchivoExamen.h"
#include "ArchivoMateria.h"
#include "ManagerExamen.h"
#include <iostream>

class ManagerDocente {
private:
    ArchivoDocente _archivoDocentes;
    ArchivoComision _archivoComisiones;
    ArchivoInscripcionComision _archivoInscripciones;
    ArchivoExamen _archivoExamen;
    ArchivoMateria _archivoMaterias;
    ManagerExamen _examenManager;

    // Métodos auxiliares para presentación
    void mostrarEncabezado();
    void mostrarRegistro(const Docente& doc);
    void mostrarPie();

public:
    ManagerDocente();

    // CRUD y gestión
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
