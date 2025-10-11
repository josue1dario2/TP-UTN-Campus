#pragma once
#include "Fecha.h"
#include "OfertaAcademica.h"

class MesaExamen : public OfertaAcademica {
private:
    int   _idMesa;
    Fecha _fecha;
    int   _turno;   // 1=FEBRERO, 2=JULIO, 3=DICIEMBRE  (cambia si querés M/T/N)

public:
    MesaExamen();
    MesaExamen(int idMesa, const Fecha& fecha, int turno);

    void setIdMesa(int v);
    void setFecha(const Fecha& f);
    void setTurno(int t);

    int   getIdMesa()  const;
    Fecha getFecha()   const;
    int   getTurno()   const;
    const char* turnoTexto() const; // "FEBRERO"|"JULIO"|"DICIEMBRE"

    void cargar();
    void mostrar() const;
    std::string toString() const;
};
