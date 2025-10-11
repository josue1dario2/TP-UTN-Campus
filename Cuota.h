#pragma once
#include <string>
#include "Fecha.h"

class Cuota {
private:
    int   _idCuota;
    int   _idAlumno;
    char  _periodo[20];
    float _monto;
    Fecha _fechaVencimiento;
    bool  _estaPagada;

public:
    Cuota();
    Cuota(int idCuota, int idAlumno, const char* periodo,
          float monto, const Fecha& fechaVenc, bool estaPagada);

    void setIdCuota(int v);
    void setIdAlumno(int v);
    void setPeriodo(const char* s);
    void setMonto(float v);
    void setFechaVencimiento(const Fecha& f);
    void setEstaPagada(bool v);

    int         getIdCuota() const;
    int         getIdAlumno() const;
    const char* getPeriodo() const;
    float       getMonto() const;
    Fecha       getFechaVencimiento() const;
    bool        getEstaPagada() const;

    void marcarPagada();

    void cargar();
    void mostrar() const;
    std::string toString() const;
};
