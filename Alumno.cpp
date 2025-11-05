#include "Alumno.h"
#include <string>

Alumno::Alumno()
    : Persona(), _legajo(0), _fechaNacimiento() {
}

Alumno::Alumno(int legajo, int dni, const char* nombre, const char* apellido,
               const char* telefono, const char* email, Direccion direccion,
               Fecha fechaNacimiento, bool eliminado)
    : Persona(dni, nombre, apellido, telefono, email, direccion, eliminado),
      _legajo(legajo), _fechaNacimiento(fechaNacimiento) {
}

int Alumno::getLegajo() const {
    return _legajo;
}

void Alumno::setLegajo(int legajo) {
    _legajo = legajo;
}

Fecha Alumno::getFechaNacimiento() const {
    return _fechaNacimiento;
}

void Alumno::setFechaNacimiento(Fecha fechaNacimiento) {
    _fechaNacimiento = fechaNacimiento;
}

void Alumno::cargar() {
    cout << "=== Cargar Alumno ===\n";

    Persona::cargar();

    cout << "Legajo: ";
    cin >> _legajo;

    cout << "Fecha de nacimiento:\n";
    _fechaNacimiento.cargar();

    setEliminado(false);
}

void Alumno::mostrar() const {
    cout << "=== Datos del Alumno ===\n";

    Persona::mostrar();

    cout << "Legajo: " << _legajo << "\n";
    cout << "Fecha de nacimiento: ";
    _fechaNacimiento.mostrar();
    cout << "\n";
}
