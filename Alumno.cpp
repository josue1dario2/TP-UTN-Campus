#include <iostream>
#include "Alumno.h"

using namespace std;

Alumno::Alumno() : Persona()
{
    _idAlumno = 0;
    _legajo = 0;
    _fechaIngreso = Fecha();
    _esBecado = false;
    _eliminado = false;
}

Alumno::Alumno(int idAlumno, int legajo, Fecha fechaIngreso, bool esBecado, bool eliminado)
    : Persona()
{
    _idAlumno = idAlumno;
    _legajo = legajo;
    _fechaIngreso = fechaIngreso;
    _esBecado = esBecado;
    _eliminado = eliminado;
}

void Alumno::setIdAlumno(int idAlumno) { _idAlumno = idAlumno; }
void Alumno::setLegajo(int legajo) { _legajo = legajo; }
void Alumno::setFechaIngreso(const Fecha &fechaIngreso) { _fechaIngreso = fechaIngreso; }
void Alumno::setEsBecado(bool esBecado) { _esBecado = esBecado; }
void Alumno::setEliminado(bool eliminado) { _eliminado = eliminado; }

int Alumno::getIdAlumno() const { return _idAlumno; }
int Alumno::getLegajo() const { return _legajo; }
Fecha Alumno::getFechaIngreso() const { return _fechaIngreso; }
bool Alumno::getEsBecado() const { return _esBecado; }
bool Alumno::getEliminado() const { return _eliminado; }

void Alumno::mostrar() const
{
    cout << "ID Alumno: " << _idAlumno << endl;
    cout << "Legajo: " << _legajo << endl;
    cout << "Fecha de Ingreso: ";
    _fechaIngreso.mostrar();
    cout << "Es Becado: " << (_esBecado ? "Si" : "No") << endl;
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << endl;
}
