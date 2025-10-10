#pragma once
#include "EvaluacionBase.h"
#include <string>

class InstanciaEvaluacion : public EvaluacionBase {
private:
    int  _idEvaluacion{0};
    int  _idInscripcion{0};
    char _tipo[20]{};

public:
    InstanciaEvaluacion();

    InstanciaEvaluacion(const Fecha& fecha, int nota,
                        int idEvaluacion, int idInscripcion,
                        const std::string& tipo);

    void setIdEvaluacion(int v);
    void setIdInscripcion(int v);
    void setTipo(const std::string& v);

    int getIdEvaluacion() const;
    int getIdInscripcion() const;
    std::string getTipo() const;

    std::string toString() const;
};
