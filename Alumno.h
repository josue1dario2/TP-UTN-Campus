#pragma once
#include "Persona.h"
#include "Fecha.h"

class Alumno : public Persona
{
public:
    Alumno();
    Alumno(int idAlumno, int legajo, Fecha fechaIngreso, bool esBecado, bool eliminado);

    void setIdAlumno(int idAlumno);
    void setLegajo(int legajo);
    void setFechaIngreso(const Fecha &fechaIngreso);
    void setEsBecado(bool esBecado);
    void setEliminado(bool eliminado);

    int getIdAlumno() const;
    int getLegajo() const;
    Fecha getFechaIngreso() const;
    bool getEsBecado() const;
    bool getEliminado() const;

    void mostrar() const;

private:
    int _idAlumno;
    int _legajo;
    Fecha _fechaIngreso;
    bool _eliminado;

};
