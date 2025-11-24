#pragma once
#include "ArchivoAlumno.h"
#include "ArchivoMateria.h"
#include "ArchivoInscripcionComision.h"
#include "ArchivoExamen.h"
#include "ArchivoCorrelativa.h"
#include "ManagerExamen.h"
#include "InscripcionComision.h"
#include "Alumno.h"

class ManagerAlumno {
private:
    ArchivoAlumno _archivoAlumnos;
    ArchivoMateria _archivoMaterias;
    ArchivoInscripcionComision _archivoInscripcionesComision;
    ManagerExamen _examenManager;

    void mostrarEncabezado();
    void mostrarRegistro(const Alumno& alu);
    void mostrarPie();

public:
    ManagerAlumno();

    bool cumpleCorrelativas(int legajoAlumno, int idMateriaObjetivo);

    // Gestión básica
    void registrarAlumno();
    void listarAlumnos();
    void mostrarAlumnoPorLegajo(int legajo);
    int buscarAlumno(int legajo);

    // Consultas académicas
    void mostrarHistorialNotas(int legajo);
    void mostrarMateriasAprobadas(int legajo);
    void mostrarMateriasPendientes(int legajo);
    void verCondicionMateria(int legajo, int idMateria);

    // Acciones académicas
    void inscribirseAFinal(int legajo, int idMateria);
    void solicitarBaja(int legajo);
    void reactivarAlumno(int legajo);

    // Inscripciones a comisiones
    void inscribirseAComision(int legajo);
    void verMisComisiones(int legajo);
    void solicitarBajaComision(int legajo, int idComision);
    void bajaInscripcionComision(int legajo, int idComision);

    // Exámenes y mesas
    void verMisMesas(int legajo);
    void bajaInscripcionExamenFinal(int legajo, int idMateria);
};
