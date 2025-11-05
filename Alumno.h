#pragma once
#include "Persona.h"
#include "Fecha.h"

class Alumno : public Persona {
public:
    Alumno();
    Alumno(int legajo, int dni, const char* nombre, const char* apellido,
           const char* telefono, const char* email, Direccion direccion,
           Fecha fechaNacimiento, bool eliminado = false);

    int getLegajo() const;
    void setLegajo(int legajo);

    Fecha getFechaNacimiento() const;
    void setFechaNacimiento(Fecha fechaNacimiento);

    void cargar();
    void mostrar() const;

private:
    int _legajo;
    Fecha _fechaNacimiento;
};
