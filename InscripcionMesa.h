#pragma once
#include "EvaluacionBase.h"
#include <string>

class InscripcionMesa : public EvaluacionBase {
private:
    int _idInscripcionMesa = 0;
    int _idAlumno = 0;
    int _idMesa = 0;
    int _estadoInscripcionMesa = 0;

public:
    InscripcionMesa();

    InscripcionMesa(const Fecha& fecha, int nota,
                    int idInscripcionMesa, int idAlumno,
                    int idMesa, int estadoInscripcionMesa);

    void setIdInscripcionMesa(int v);
    void setIdAlumno(int v);
    void setIdMesa(int v);
    void setEstadoInscripcionMesa(int v);

    int getIdInscripcionMesa() const;
    int getIdAlumno() const;
    int getIdMesa() const;
    int getEstadoInscripcionMesa() const;

    std::string toString() const;
    void mostrar() const;
};
