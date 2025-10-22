#include "Alumno.h"
#include <string>

Alumno::Alumno()
    : Persona(), _legajo(0), _fechaIngreso() {
}

Alumno::Alumno(int legajo, int dni, const char* nombre, const char* apellido,
               const char* telefono, const char* email, Direccion direccion,
               Fecha fechaIngreso, bool eliminado)
    : Persona(dni, nombre, apellido, telefono, email, direccion, eliminado),
      _legajo(legajo), _fechaIngreso(fechaIngreso) {
}

int Alumno::getLegajo() const {
    return _legajo;
}

void Alumno::setLegajo(int legajo) {
    _legajo = legajo;
}

Fecha Alumno::getFechaIngreso() const {
    return _fechaIngreso;
}

void Alumno::setFechaIngreso(Fecha fechaIngreso) {
    _fechaIngreso = fechaIngreso;
}

std::string Alumno::toString() const {
    return Persona::toString() +
           "\nLegajo: " + std::to_string(_legajo) +
           "\nFecha de ingreso: " + _fechaIngreso.toString();
}
