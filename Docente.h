#pragma once
#include "Persona.h"

class Docente : public Persona {
public:
    Docente();
    Docente(int legajo, int dni, const char* nombre, const char* apellido,
            const char* telefono, const char* email, Direccion direccion,
            const char* rol, bool eliminado = false);

    int getLegajo() const;
    void setLegajo(int legajo);

    const char* getRol() const;
    void setRol(const char* rol);

    void cargar();
    void mostrar() const;

private:
    int _legajo;
    char _rol[20];
};
