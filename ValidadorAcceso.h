#pragma once

#include "ArchivoAlumno.h"
#include "ArchivoDocente.h"
#include <string>

class ValidadorAcceso {
private:
    int intentosActuales;

    // Métodos auxiliares para mensajes
    void mostrarIntentosRestantes(int intentosRestantes) const;
    void mostrarBloqueo() const;

public:
    ValidadorAcceso();

    // Métodos de validación específicos
    bool validarLegajoAlumno(int& legajoValidado);
    bool validarLegajoDocente(int& legajoValidado);
    bool validarCodigoAdmin();

    // Reset del contador
    void resetearIntentos();
};
