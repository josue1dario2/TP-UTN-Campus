#pragma once
#include "Fecha.h"
#include <string>

class EvaluacionBase
{
private:
    Fecha _fecha;
    int _nota;

public:
    EvaluacionBase();
    EvaluacionBase(const Fecha &fecha, int nota);

    void setFecha(const Fecha &fecha);
    void setNota(int nota);

    Fecha getFecha() const;
    int getNota() const;

    void cargar();
    void mostrar() const;
    std::string toString() const;
};
