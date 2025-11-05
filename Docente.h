#pragma once
#include "Persona.h"

class Docente : public Persona {
public:
    Docente();
    Docente(int legajo, int dni, const char* nombre, const char* apellido,
            const char* telefono, const char* email, Direccion direccion, bool eliminado = false);

    int getLegajo() const;
    void setLegajo(int legajo);

    void cargar();
    void mostrar() const;

private:
    int _legajo;
};
