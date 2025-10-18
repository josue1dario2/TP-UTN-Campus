#pragma once
#include "Fecha.h"
#include <string>

class Evaluacion
{
public:
    Evaluacion();
    Evaluacion(int idEvaluacion, int idMateria, const char *tipo, const Fecha &fecha, bool eliminado = false);

    void setIdEvaluacion(int idEvaluacion);
    void setIdMateria(int idMateria);
    void setTipo(const char* tipo);
    void setFecha(const Fecha &fecha);
    void setEliminado(bool eliminado);

    int getIdEvaluacion() const;
    int getIdMateria() const;
    const char *tipo() const;
    Fecha getFecha() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int   _idEvaluacion;
    int   _idMateria;
    char  _tipo[20];          // "Parcial", "Recup", "TP", "Final"
    Fecha _fecha;
    bool _eliminado;
};
