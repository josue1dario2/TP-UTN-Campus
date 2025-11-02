#pragma once
#include <cstring>
#include <iostream>

class Comision {
private:
    int _idComision;
    int _idMateria;
    int _legajoDocente;
    int _anio;
    char _turno[20];
    bool _eliminado;

public:
    Comision();
    Comision(int idComision, int idMateria, int legajoDocente, int anio, const char* turno, bool eliminado = false);

    // Getters
    int getIdComision() const;
    int getIdMateria() const;
    int getLegajoDocente() const;
    int getAnio() const;
    const char* getTurno() const;
    bool getEliminado() const;

    // Setters
    void setIdComision(int v);
    void setIdMateria(int v);
    void setLegajoDocente(int v);
    void setAnio(int v);
    void setTurno(const char* t);
    void setEliminado(bool e);

    // Métodos
    void cargar();
    void mostrar() const;
};
