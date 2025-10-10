#include "EvaluacionBase.h"
#include <sstream>
#include <iostream>

EvaluacionBase::EvaluacionBase() : _fecha(), _nota(0) {}

EvaluacionBase::EvaluacionBase(const Fecha& fecha, int nota)
    : _fecha(fecha), _nota(nota) {}

void EvaluacionBase::setFecha(const Fecha& fecha) { _fecha = fecha; }
void EvaluacionBase::setNota(int nota) { _nota = nota; }

Fecha EvaluacionBase::getFecha() const { return _fecha; }
int   EvaluacionBase::getNota()  const { return _nota; }

void EvaluacionBase::cargar() {
}

void EvaluacionBase::mostrar() const {
    std::cout << toString() << std::endl;
}

std::string EvaluacionBase::toString() const {
    std::ostringstream os;
    os << "EvaluacionBase{fecha=" << _fecha.toString()
       << ", nota=" << _nota << "}";
    return os.str();
}
