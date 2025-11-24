#pragma once
#include "ArchivoInscripcionComision.h"
#include "InscripcionComision.h"
#include <iostream>
#include <iomanip>

class ManagerInscripcionComision {
private:
    ArchivoInscripcionComision _archivo;

    void mostrarEncabezado();
    void mostrarRegistro(const InscripcionComision& reg);
    void mostrarPie();

public:
    ManagerInscripcionComision();

    void cargar();     // Crear inscripción (con validaciones)
    void listar();     // Mostrar inscripciones activas y pendientes
    void borrar();     // Baja definitiva (estado = 2)

    bool estaInscripto(int legajo, int idComision);   // Evita duplicados
    void procesarSolicitudesPendientes();
};
