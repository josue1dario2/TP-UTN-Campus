#pragma once
#include <string>
#include <cstring>
#include "Fecha.h"

class Examen {
public:
    Examen();
    Examen(int idExamen,
           int idMateria,
           int legajoAlumno,
           const char* tipo,
           int numeroParcial,
           Fecha fecha,
           bool eliminado = false);

    // Getters y Setters
    int  getIdExamen() const;        void setIdExamen(int v);
    int  getIdMateria() const;       void setIdMateria(int v);
    int  getLegajoAlumno() const;    void setLegajoAlumno(int v);

    const char* getTipo() const;     void setTipo(const char* v);

    int  getNumeroParcial() const;   void setNumeroParcial(int n);

    Fecha getFecha() const;          void setFecha(Fecha f);

    int  getNota() const;            void setNota(int v);
    bool getCorregido() const;       void setCorregido(bool v);
    bool getEliminado() const;       void setEliminado(bool v);

    void inscribir();
    void corregir(int nota);
    void cargar();
    void mostrar() const;

private:
    int   _idExamen;
    int   _idMateria;
    int   _legajoAlumno;
    char  _tipo[15];
    int   _numeroParcial;
    Fecha _fecha;
    int   _nota;
    bool  _corregido;
    bool  _eliminado;
};
