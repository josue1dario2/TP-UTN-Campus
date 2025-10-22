#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include "Fecha.h"

class Inscripcion {
public:
    Inscripcion();
    Inscripcion(int idInscripcion, int legajoAlumno, int idComision,
                Fecha fechaInscripcion, const char* estado, bool eliminado = false);

    int   getIdInscripcion() const;  void setIdInscripcion(int v);
    int   getLegajoAlumno() const;   void setLegajoAlumno(int v);
    int   getIdComision() const;     void setIdComision(int v);
    Fecha getFechaInscripcion() const; void setFechaInscripcion(Fecha f);

    const char* getEstado() const;   void setEstado(const char* v); // "Regular", "Libre", "Aprobada", "Baja"
    bool  getEliminado() const;      void setEliminado(bool v);

    std::string toString() const;
    void cargar();
    void mostrar() const;

private:
    int   _idInscripcion;
    int   _legajoAlumno;
    int   _idComision;
    Fecha _fechaInscripcion;
    char  _estado[20];
    bool  _eliminado;
};
