#include "Alumno.h"
#include "Validacion.h"
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
cout << "\n\t=== Cargar Alumno ===\n";
    Persona::cargar();
    _legajo = Validacion::validarEnteroEnRango("\n\tNum. de legajo: ", 10000, 99999);

    cout << "\tFecha de ingreso:\n";
    _fechaIngreso.cargar();

    setEliminado(false);
}

void Alumno::mostrar() const {
    cout << "\n\t=== Datos del Alumno ===\n";
    Persona::mostrar();
    cout << "\tLegajo: " << _legajo << "\n";
    cout << "\tFecha de ingreso: ";
    _fechaIngreso.mostrar();
    cout << "\n\t---------------------------\n";
}
