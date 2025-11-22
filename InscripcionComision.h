#pragma once
#include "Fecha.h"

class InscripcionComision {
private:
    int _legajoAlumno;
    int _idComision;
    Fecha _fecha;

    // Estados:
    // 0 = Activa
    // 1 = Pendiente de baja
    // 2 = Baja aprobada
    int _estado;

public:
    InscripcionComision();
    InscripcionComision(int legajo, int idComision);

    void setLegajoAlumno(int legajo);
    void setIdComision(int idComision);
    void setFecha(Fecha f);
    void setEstado(int estado);

    int getLegajoAlumno() const;
    int getIdComision() const;
    Fecha getFecha() const;
    int getEstado() const;

    void cargar();
    void mostrar() const;
};
