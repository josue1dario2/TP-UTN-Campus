#pragma once
#include <iostream>

class Calificacion {
private:
    int  _idCalificacion;
    int  _idEvaluacion;
    int  _idAlumno;
    int  _idInscripcion;
    int  _nota;
    char _condicion[20];    // "Aprobado", "Desaprobado", "Ausente"
    bool _eliminado;

public:
    Calificacion();
    Calificacion(int idCalificacion, int idEvaluacion, int idAlumno,
                 int idInscripcion, int nota, const char* condicion,
                 bool eliminado = false);

    void setIdCalificacion(int idCalificacion);
    void setIdEvaluacion(int idEvaluacion);
    void setIdAlumno(int idAlumno);
    void setIdInscripcion(int idInscripcion);
    void setNota(int nota);
    void setCondicion(const char* condicion);
    void setEliminado(bool eliminado);

    int  getIdCalificacion() const;
    int  getIdEvaluacion() const;
    int  getIdAlumno() const;
    int  getIdInscripcion() const;
    int  getNota() const;
    const char* getCondicion() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;
};
