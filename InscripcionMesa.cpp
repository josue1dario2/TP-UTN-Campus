#include "InscripcionMesa.h"
#include <sstream>
#include <iostream>

InscripcionMesa::InscripcionMesa()
    : EvaluacionBase(), _idInscripcionMesa(0), _idAlumno(0),
      _idMesa(0), _estadoInscripcionMesa(0) {}

InscripcionMesa::InscripcionMesa(const Fecha& fecha, int nota,
                                 int idInscripcionMesa, int idAlumno,
                                 int idMesa, int estadoInscripcionMesa)
    : EvaluacionBase(fecha, nota),
      _idInscripcionMesa(idInscripcionMesa),
      _idAlumno(idAlumno),
      _idMesa(idMesa),
      _estadoInscripcionMesa(estadoInscripcionMesa) {}

void InscripcionMesa::setIdInscripcionMesa(int v) { _idInscripcionMesa = v; }
void InscripcionMesa::setIdAlumno(int v)          { _idAlumno = v; }
void InscripcionMesa::setIdMesa(int v)            { _idMesa = v; }
void InscripcionMesa::setEstadoInscripcionMesa(int v) { _estadoInscripcionMesa = v; }

int InscripcionMesa::getIdInscripcionMesa() const { return _idInscripcionMesa; }
int InscripcionMesa::getIdAlumno() const          { return _idAlumno; }
int InscripcionMesa::getIdMesa() const            { return _idMesa; }
int InscripcionMesa::getEstadoInscripcionMesa() const { return _estadoInscripcionMesa; }

std::string InscripcionMesa::toString() const {
    std::ostringstream os;
    os << "InscripcionMesa{"
       << EvaluacionBase::toString()
       << ", idInscripcionMesa=" << _idInscripcionMesa
       << ", idAlumno=" << _idAlumno
       << ", idMesa=" << _idMesa
       << ", estadoInscripcionMesa=" << _estadoInscripcionMesa
       << "}";
    return os.str();
}

void InscripcionMesa::mostrar() const {
    std::cout << toString() << std::endl;
}
