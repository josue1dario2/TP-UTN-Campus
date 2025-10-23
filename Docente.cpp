#include "Docente.h"
#include <cstring>
#include <string>

Docente::Docente()
    : Persona(), _legajo(0) {
    strcpy(_rol, "");
}

Docente::Docente(int legajo, int dni, const char* nombre, const char* apellido,
                 const char* telefono, const char* email, Direccion direccion,
                 const char* rol, bool eliminado)
    : Persona(dni, nombre, apellido, telefono, email, direccion, eliminado),
      _legajo(legajo) {
    setRol(rol);
}

int Docente::getLegajo() const {
    return _legajo;
}

void Docente::setLegajo(int legajo) {
    _legajo = legajo;
}

const char* Docente::getRol() const {
    return _rol;
}

void Docente::setRol(const char* rol) {
    strncpy(_rol, rol, sizeof(_rol));
    _rol[sizeof(_rol) - 1] = '\0';
}

std::string Docente::toString() const {
    return Persona::toString() +
           "\nLegajo: " + std::to_string(_legajo) +
           "\nRol: " + std::string(_rol);
}
