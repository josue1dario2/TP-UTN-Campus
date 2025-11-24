#pragma once

#include "Validacion.h"
#include "ArchivoAlumno.h"
#include "ArchivoDocente.h"
#include "ArchivoCarrera.h"
#include "ArchivoMateria.h"
#include "ArchivoComision.h"
#include "ArchivoInscripcionComision.h"
#include "ArchivoExamen.h"
#include "ArchivoCorrelativa.h"


class MenuDatosCSV {
public:
    MenuDatosCSV();
    void mostrar();

protected:
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    int seleccionOpcion();

private:
    Validacion validar;
    int _cantidadOpciones;

    // Métodos de exportación
    void exportarAlumnos();
    void exportarDocentes();
    void exportarCarreras();
    void exportarMaterias();
    void exportarComisiones();
    void exportarInscripciones();
    void exportarMesasExamen();
    void exportarEvaluaciones();
    void exportarCalificaciones();
    void exportarCorrelativas();
    void exportarTodos();
};


