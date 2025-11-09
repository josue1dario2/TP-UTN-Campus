#pragma once
#include "Persona.h"
#include "Fecha.h"

class Docente : public Persona {
public:
    Docente();
    Docente(int legajo, int dni, const char* nombre, const char* apellido,
            const char* telefono, const char* email,
            Direccion direccion, Fecha fechaNacimiento,
            Fecha fechaIngreso, bool eliminado = false);

    int getLegajo() const;
    void setLegajo(int legajo);

    Fecha getFechaIngreso() const;
    void setFechaIngreso(Fecha fechaIngreso);

    void cargar();
    void mostrar() const;

private:
    int _legajo;
    Fecha _fechaIngreso;
};
