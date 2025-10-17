#pragma once
#include "Fecha.h"

class MesaExamen {
public:
    MesaExamen();
    MesaExamen(int idMesa, const Fecha& fecha, int turno,bool eliminado = false);

    void setIdMesa(int v);
    void setFecha(const Fecha& f);
    void setTurno(int t);
    void setEliminado(bool eliminado);

    int   getIdMesa()  const;
    Fecha getFecha()   const;
    int   getTurno()   const;
    const char* turnoTexto() const; // "FEBRERO"|"JULIO"|"DICIEMBRE"
    bool  getEliminado() const;

    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int   _idMesa;
    Fecha _fecha;
    int   _turno;   // 1=FEBRERO, 2=JULIO, 3=DICIEMBRE  (cambia si querés M/T/N)
    bool _eliminado;

};
