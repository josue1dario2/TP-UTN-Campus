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

void Docente::cargar() {
    cout << "=== Cargar Docente ===\n";

    Persona::cargar();

    cout << "Legajo: ";
    cin >> _legajo;
    cin.ignore(10000, '\n');

    cout << "Rol (Ej: Profesor, JTP, Ayudante): ";
    cin.getline(_rol, sizeof(_rol));

    setEliminado(false);
}

void Docente::mostrar() const {
    cout << "=== Datos del Docente ===\n";

    Persona::mostrar();

    cout << "Legajo: " << _legajo << "\n";
    cout << "Rol: " << _rol << "\n";
    cout << "\n";
}
