#pragma once
#include <string>
#include <cstring>
#include "Fecha.h"

class Examen {
public:
    Examen();
    Examen(int idExamen, int idComision, int legajoAlumno,
           int tipoExamen,
           Fecha fecha, bool eliminado = false);

    int  getIdExamen() const;      void setIdExamen(int v);
    int  getIdComision() const;    void setIdComision(int v);
    int  getLegajoAlumno() const;  void setLegajoAlumno(int v);
    int  getTipoExamen() const;        void setTipoExamen(int v);
    Fecha getFecha() const;        void setFecha(Fecha f);

    int  getNota() const;          void setNota(int v);
    bool getCorregido() const;     void setCorregido(bool v);
    bool getEliminado() const;     void setEliminado(bool v);

    void inscribir();
    void corregir(int nota);
    void cargar();                 // alumno se inscribe (sin nota)
    void mostrar() const;
    const char* getDescripcionTipoExamen() const;

private:
    int   _idExamen;
    int   _idComision;
    int   _legajoAlumno;
    int   _tipoExamen;         // 1.2.3 (parcial), 4.5.6 (recuperatorio), 7 (final)
    Fecha _fecha;

    int   _nota;           // -1 si aún no fue corregido
    bool  _corregido;      // false al inscribirse, true al corregir
    bool  _eliminado;
};
