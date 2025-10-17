#include "Calificacion.h"
#include <cstring>
using namespace std;

Calificacion::Calificacion() {
    _idCalificacion = 0;
    _idEvaluacion   = 0;
    _idAlumno       = 0;
    _idInscripcion  = 0;
    _nota           = 0;
    _condicion[0]   = '\0';
    _eliminado      = false;
}

Calificacion::Calificacion(int idCalificacion, int idEvaluacion, int idAlumno,
                           int idInscripcion, int nota, const char* condicion,
                           bool eliminado) {
    _idCalificacion = idCalificacion;
    _idEvaluacion   = idEvaluacion;
    _idAlumno       = idAlumno;
    _idInscripcion  = idInscripcion;
    _nota           = nota;
    if (condicion) {
        strncpy(_condicion, condicion, sizeof(_condicion) - 1);
        _condicion[sizeof(_condicion) - 1] = '\0';
    } else {
        _condicion[0] = '\0';
    }
    _eliminado = eliminado;
}

void Calificacion::setIdCalificacion(int idCalificacion) { _idCalificacion = idCalificacion; }
void Calificacion::setIdEvaluacion(int idEvaluacion)     { _idEvaluacion = idEvaluacion; }
void Calificacion::setIdAlumno(int idAlumno)             { _idAlumno = idAlumno; }
void Calificacion::setIdInscripcion(int idInscripcion)   { _idInscripcion = idInscripcion; }
void Calificacion::setNota(int nota)                     { _nota = nota; }
void Calificacion::setCondicion(const char* condicion) {
    if (condicion) {
        strncpy(_condicion, condicion, sizeof(_condicion) - 1);
        _condicion[sizeof(_condicion) - 1] = '\0';
    } else {
        _condicion[0] = '\0';
    }
}
void Calificacion::setEliminado(bool eliminado)          { _eliminado = eliminado; }

int  Calificacion::getIdCalificacion() const { return _idCalificacion; }
int  Calificacion::getIdEvaluacion() const   { return _idEvaluacion; }
int  Calificacion::getIdAlumno() const       { return _idAlumno; }
int  Calificacion::getIdInscripcion() const  { return _idInscripcion; }
int  Calificacion::getNota() const           { return _nota; }
const char* Calificacion::getCondicion() const { return _condicion; }
bool Calificacion::getEliminado() const      { return _eliminado; }


void Calificacion::cargar() {
    cout << "ID Calificacion: ";
    cin  >> _idCalificacion;

    cout << "ID Evaluacion: ";
    cin  >> _idEvaluacion;

    cout << "ID Alumno: ";
    cin  >> _idAlumno;

    cout << "ID Inscripcion (0 si no aplica): ";
    cin  >> _idInscripcion;

    cout << "Nota (0..10): ";
    cin  >> _nota;

    cout << "Condicion (Aprobado/Desaprobado/Ausente): ";
    cin  >> _condicion;

    _eliminado = false;
}

void Calificacion::mostrar() const {
    cout << "IdCalificacion: " << _idCalificacion << '\n';
    cout << "IdEvaluacion:  " << _idEvaluacion   << '\n';
    cout << "IdAlumno:      " << _idAlumno       << '\n';
    cout << "IdInscripcion: " << _idInscripcion  << '\n';
    cout << "Nota:          " << _nota           << '\n';
    cout << "Condicion:     " << (_condicion[0] ? _condicion : "(sin condicion)") << '\n';
    cout << "Eliminado:     " << (_eliminado ? "Si" : "No") << '\n';
}
