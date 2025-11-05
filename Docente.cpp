#include "Docente.h"
#include <cstring>
#include <string>

Docente::Docente()
    : Persona(), _legajo(0) {
}

Docente::Docente(int legajo, int dni, const char* nombre, const char* apellido,
                 const char* telefono, const char* email, Direccion direccion, bool eliminado)
    : Persona(dni, nombre, apellido, telefono, email, direccion, eliminado),
      _legajo(legajo) {
}

int Docente::getLegajo() const {
    return _legajo;
}

void Docente::setLegajo(int legajo) {
    _legajo = legajo;
}

void Docente::cargar() {
    cout << "=== Cargar Docente ===\n";

    Persona::cargar();

    cout << "Legajo: ";
    cin >> _legajo;
    cin.ignore(10000, '\n');

    setEliminado(false);
}

void Docente::mostrar() const {
    cout << "=== Datos del Docente ===\n";

    Persona::mostrar();

    cout << "Legajo: " << _legajo << "\n";
    cout << "\n";
}
