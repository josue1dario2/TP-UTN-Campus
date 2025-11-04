#pragma once
#include <string>
#include <cstring>
#include <iostream>

class Comision {
public:
    Comision();
    Comision(int idComision, int idMateria,
             const char* turno, const char* modalidad,
             int cuatrimestre,int anio,int legajoDocente, bool eliminado = false);

    int  getIdComision() const;
    void setIdComision(int v);

    int  getIdMateria() const;
    void setIdMateria(int v);

    const char* getTurno() const;
    void setTurno(const char* v);

    const char* getModalidad() const;
    void setModalidad(const char* v);

    int  getCuatrimestre() const;
    void setCuatrimestre(int v);

    int getAnio() const;
    void setAnio(int anio);

    int  getLegajoDocente() const;
    void setLegajoDocente(int legajo);

    bool getEliminado() const;
    void setEliminado(bool v);

    void cargar();
    void mostrar() const;

private:
    int  _idComision;
    int  _idMateria;
    char _turno[10];     // "Mañana", "Tarde", "Noche"
    char _modalidad[10]; // "Presencial", "Virtual", "Híbrida"
    int  _cuatrimestre;
    int  _anio;
    int  _legajoDocente;
    bool _eliminado;
};
