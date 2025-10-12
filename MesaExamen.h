#pragma once
#include "OfertaAcademica.h"
#include "Fecha.h"
#include <string>

class MesaExamen : public OfertaAcademica {
public:
    MesaExamen();
    MesaExamen(int idMesa, int idPlanMateria, int modalidad, const char* aula, bool activa, const Fecha& fecha, int turno);

    // Setters
    void setIdMesa(int idMesa);
    void setFecha(const Fecha& fecha);
    void setTurno(int turno);

    // Getters
    int getIdMesa() const;
    Fecha getFecha() const;
    int getTurno() const;

    // Métodos
    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int _idMesa;
    Fecha _fecha;
    int _turno;
};
