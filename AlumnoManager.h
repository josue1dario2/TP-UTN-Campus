#pragma once
#include "ArchivoAlumno.h"
#include "ArchivoMateria.h"
#include "ManagerExamen.h"
#include "ArchivoInscripcionComision.h"
#include "InscripcionComision.h"

class AlumnoManager {
private:
    ArchivoAlumno _archivoAlumnos;
    ArchivoMateria _archivoMaterias;
    ManagerExamen _examenManager;
    ArchivoInscripcionComision _archivoInscripcionesComision;


public:
    AlumnoManager();

    // --- Gestión básica ---
    void registrarAlumno();
    void listarAlumnos(bool incluirBorrados= false);
    void modificarAlumno();
    void bajaLogicaAlumno();

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

    // --- Inscripciones a comisiones ---
    void inscribirseAComision(int legajo);
    void verMisComisiones(int legajo);
    void bajaInscripcionComision(int legajo, int idComision); // opcional

    // --- Exámenes y mesas ---
    void verMisMesas(int legajo);
    void verMisInscripciones(int legajo);
    void bajaInscripcionMesaFinal(int legajo, int idComision); // baja de final
};
