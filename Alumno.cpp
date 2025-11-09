#include "Alumno.h"
#include <iostream>
using namespace std;

Alumno::Alumno()
    : Persona(), _legajo(0), _fechaIngreso() {}

Alumno::Alumno(int legajo, int dni, const char* nombre, const char* apellido,
               const char* telefono, const char* email, Direccion direccion,
               Fecha fechaNacimiento, Fecha fechaIngreso, bool eliminado)
    : Persona(dni, nombre, apellido, telefono, email, direccion, fechaNacimiento, eliminado),
      _legajo(legajo), _fechaIngreso(fechaIngreso) {}

int Alumno::getLegajo() const { return _legajo; }
void Alumno::setLegajo(int legajo) { _legajo = legajo; }

Fecha Alumno::getFechaIngreso() const { return _fechaIngreso; }
void Alumno::setFechaIngreso(Fecha fechaIngreso) { _fechaIngreso = fechaIngreso; }

void Alumno::cargar() {
    cout << "\n=== Cargar Alumno ===\n";
    Persona::cargar();

    cout << "Legajo: ";
    cin >> _legajo;
    cin.ignore();

    cout << "Fecha de ingreso:\n";
    _fechaIngreso.cargar();

    setEliminado(false);
}

void Alumno::mostrar() const {
    cout << "\n=== Datos del Alumno ===\n";
    Persona::mostrar();
    cout << "Legajo: " << _legajo << "\n";
    cout << "Fecha de ingreso: ";
    _fechaIngreso.mostrar();
    cout << "---------------------------\n";
}
