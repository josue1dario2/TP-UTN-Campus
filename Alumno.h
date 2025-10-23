#pragma once
#include "Persona.h"
#include "Fecha.h"

class Alumno : public Persona {
public:
    Alumno();
    Alumno(int legajo, int dni, const char* nombre, const char* apellido,
           const char* telefono, const char* email, Direccion direccion,
           Fecha fechaIngreso, bool eliminado = false);

    int getLegajo() const;
    void setLegajo(int legajo);

    Fecha getFechaIngreso() const;
    void setFechaIngreso(Fecha fechaIngreso);

    std::string toString() const;

private:
    int _legajo;
    Fecha _fechaIngreso;
};
