#pragma once
#include "Persona.h"
#include <string>

class Docente : public Persona
{
public:
    Docente();
    Docente(int idDocente, int legajo, const char *rol, bool eliminado, const char *nombre, const char *apellido, int dni);

    void setIdDocente(int idDocente);
    void setLegajo(int legajo);
    void setRol(const char *rol);
    void setEliminado(bool eliminado);

    int getIdDocente() const;
    int getLegajo() const;
    const char *getRol() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int _idDocente;
    int _legajo;
    char _rol[20];
    bool _eliminado;
};