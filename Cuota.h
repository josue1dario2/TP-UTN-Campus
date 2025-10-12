#pragma once
#include "Fecha.h"
#include <string>

class Cuota {
public:
    Cuota();
    Cuota(int idCuota, double monto, const Fecha& fechaVencimiento, bool pagada);

    // Setters
    void setIdCuota(int idCuota);
    void setMonto(double monto);
    void setFechaVencimiento(const Fecha& fechaVencimiento);
    void setPagada(bool pagada);

    // Getters
    int getIdCuota() const;
    double getMonto() const;
    Fecha getFechaVencimiento() const;
    bool getPagada() const;

    // Métodos
    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int _idCuota;
    double _monto;
    Fecha _fechaVencimiento;
    bool _pagada;
};

