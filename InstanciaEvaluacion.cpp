#include "InstanciaEvaluacion.h"
#include <cstring>
#include <sstream>

InstanciaEvaluacion::InstanciaEvaluacion()
    : EvaluacionBase(), _idEvaluacion(0), _idInscripcion(0) {
    _tipo[0] = '\0';
}

InstanciaEvaluacion::InstanciaEvaluacion(const Fecha& fecha, int nota,
                                         int idEvaluacion, int idInscripcion,
                                         const std::string& tipo)
    : EvaluacionBase(fecha, nota),
      _idEvaluacion(idEvaluacion),
      _idInscripcion(idInscripcion) {
    std::strncpy(_tipo, tipo.c_str(), sizeof(_tipo) - 1);
    _tipo[sizeof(_tipo) - 1] = '\0';
}

void InstanciaEvaluacion::setIdEvaluacion(int v)   { _idEvaluacion = v; }
void InstanciaEvaluacion::setIdInscripcion(int v)  { _idInscripcion = v; }
void InstanciaEvaluacion::setTipo(const std::string& v) {
    std::strncpy(_tipo, v.c_str(), sizeof(_tipo) - 1);
    _tipo[sizeof(_tipo) - 1] = '\0';
}

int InstanciaEvaluacion::getIdEvaluacion()  const { return _idEvaluacion; }
int InstanciaEvaluacion::getIdInscripcion() const { return _idInscripcion; }
std::string InstanciaEvaluacion::getTipo()  const { return std::string(_tipo); }

std::string InstanciaEvaluacion::toString() const {
    std::ostringstream os;
    os << "InstanciaEvaluacion{"
       << "idEvaluacion="   << _idEvaluacion
       << ", idInscripcion="<< _idInscripcion
       << ", tipo=\""       << _tipo << "\""
       << ", base="         << EvaluacionBase::toString()
       << "}";
    return os.str();
}
