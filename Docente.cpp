#include "Docente.h"
#include <iostream>
using namespace std;

Docente::Docente()
    : Persona(), _legajo(0), _fechaIngreso() {}

Docente::Docente(int legajo, int dni, const char* nombre, const char* apellido,
                 const char* telefono, const char* email,
                 Direccion direccion, Fecha fechaNacimiento,
                 Fecha fechaIngreso, bool eliminado)
    : Persona(dni, nombre, apellido, telefono, email, direccion, fechaNacimiento, eliminado),
      _legajo(legajo), _fechaIngreso(fechaIngreso) {}

int Docente::getLegajo() const { return _legajo; }
void Docente::setLegajo(int legajo) { _legajo = legajo; }

Fecha Docente::getFechaIngreso() const { return _fechaIngreso; }
void Docente::setFechaIngreso(Fecha fechaIngreso) { _fechaIngreso = fechaIngreso; }

void Docente::cargar() {
    cout << "\n=== Cargar Docente ===\n";
    Persona::cargar();

    cout << "Legajo: ";
    cin >> _legajo;
    cin.ignore();

    cout << "Fecha de ingreso:\n";
    _fechaIngreso.cargar();

    setEliminado(false);
}

void Docente::mostrar() const {
    cout << "\n=== Datos del Docente ===\n";
    Persona::mostrar();
    cout << "Legajo: " << _legajo << "\n";
    cout << "Fecha de ingreso: ";
    _fechaIngreso.mostrar();
    cout << "---------------------------\n";
}
