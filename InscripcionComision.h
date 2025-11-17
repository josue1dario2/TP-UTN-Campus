#pragma once
#include "Fecha.h"

class InscripcionComision {
private:
    int _legajoAlumno;
    int _idComision;
    Fecha _fecha;
    bool _eliminado;

public:
    InscripcionComision();
    InscripcionComision(int legajo, int idComision);

    void setLegajoAlumno(int legajo);
    void setIdComision(int idComision);
    void setFecha(Fecha f);
    void setEliminado(bool e);

    int getLegajoAlumno() const;
    int getIdComision() const;
    Fecha getFecha() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;
};
