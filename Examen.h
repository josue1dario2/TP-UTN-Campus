#pragma once
#include <string>
#include <cstring>
#include "Fecha.h"

class Examen {
public:
    Examen();
    Examen(int idExamen, int idComision, int legajoAlumno,
           const char* tipo,
           int numero,
           Fecha fecha, bool eliminado = false);

    int  getIdExamen() const;      void setIdExamen(int v);
    int  getIdComision() const;    void setIdComision(int v);
    int  getLegajoAlumno() const;  void setLegajoAlumno(int v);

    const char* getTipo() const;   void setTipo(const char* v);
    int  getNumero() const;        void setNumero(int v);
    Fecha getFecha() const;        void setFecha(Fecha f);

    int  getNota() const;          void setNota(int v);
    bool getCorregido() const;     void setCorregido(bool v);
    bool getEliminado() const;     void setEliminado(bool v);

    void inscribir();
    void corregir(int nota);

    std::string toString() const;
    void cargar();                 // alumno se inscribe (sin nota)
    void mostrar() const;          // imprime

private:
    int   _idExamen;
    int   _idComision;
    int   _legajoAlumno;

    char  _tipo[10];       // "Parcial" | "Final"
    int   _numero;         // 1..3 (parcial), 0 (final)
    Fecha _fecha;

    int   _nota;           // -1 si aún no fue corregido
    bool  _corregido;      // false al inscribirse, true al corregir
    bool  _eliminado;
};
