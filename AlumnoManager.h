#pragma once
#include "ArchivoAlumno.h"
#include "ArchivoMateria.h"
#include "ArchivoInscripcion.h"
#include "ExamenManager.h"
#include "Inscripcion.h"

class AlumnoManager {
private:
    ArchivoAlumno _archivoAlumnos;
    ArchivoMateria _archivoMaterias;
    ArchivoInscripcion _archivoInscripciones;
    ExamenManager _examenManager;

public:
    AlumnoManager();

    // --- Gestión básica ---
    void registrarAlumno();
    void listarAlumnos();
    void mostrarAlumnoPorLegajo(int legajo);
    int buscarAlumno(int legajo);

    // --- Consultas académicas ---
    void mostrarHistorialNotas(int legajo);
    void mostrarMateriasAprobadas(int legajo);
    void mostrarMateriasPendientes(int legajo);
    void verCondicionMateria(int legajo, int idMateria);

    // --- Acciones académicas ---
    void inscribirseAFinal(int legajo, int idMateria);
    void solicitarBaja(int legajo);
    void reactivarAlumno(int legajo);

    // --- Inscripciones ---
    void verMisComisiones(int legajo);
    void verMisMesas(int legajo);
    void bajaInscripcionMateria(int legajo, int idComision);
    void bajaInscripcionMesaFinal(int legajo, int idComision);
    void inscribirseAMateria(int legajo, int idComision);

};
