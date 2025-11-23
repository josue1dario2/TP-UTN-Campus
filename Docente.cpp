#include "Docente.h"
#include "Validacion.h"
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
    cout << "\n\t=== Cargar Docente ===\n";
    if(cin.peek() == '\n') cin.ignore();
    _legajo = Validacion::validarEnteroEnRango("\n\tNum. de legajo: ", 10000, 99999);
	Persona::cargar();

    
    //cin.ignore();

    cout << "\n\tFecha de ingreso:\n";
    _fechaIngreso.cargar();

    setEliminado(false);
}

void Docente::mostrar() const {
    cout << "\n\t=== Datos del Docente ===\n";
    Persona::mostrar();
    cout << "\tLegajo: " << _legajo;
    cout << "\n\tFecha de ingreso: ";
    _fechaIngreso.mostrar();
    cout << "\t---------------------------\n";
}
