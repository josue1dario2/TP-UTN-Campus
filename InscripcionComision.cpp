#include "InscripcionComision.h"
#include <iostream>
using namespace std;

InscripcionComision::InscripcionComision() {
    _legajoAlumno = 0;
    _idComision = 0;
    _eliminado = false;
}

InscripcionComision::InscripcionComision(int legajo, int idComision) {
    _legajoAlumno = legajo;
    _idComision = idComision;
    _eliminado = false;
}

void InscripcionComision::setLegajoAlumno(int legajo) { _legajoAlumno = legajo; }
void InscripcionComision::setIdComision(int idComision) { _idComision = idComision; }
void InscripcionComision::setFecha(Fecha f) { _fecha = f; }
void InscripcionComision::setEliminado(bool e) { _eliminado = e; }

int InscripcionComision::getLegajoAlumno() const { return _legajoAlumno; }
int InscripcionComision::getIdComision() const { return _idComision; }
Fecha InscripcionComision::getFecha() const { return _fecha; }
bool InscripcionComision::getEliminado() const { return _eliminado; }

void InscripcionComision::cargar() {
    cout << "\n=== Inscripción a Comisión ===\n";
    cout << "Legajo del alumno: ";
    cin >> _legajoAlumno;
    cout << "ID de la comisión: ";
    cin >> _idComision;
    cout << "Fecha de inscripción:\n";
    _fecha.cargar();
    _eliminado = false;
}

void InscripcionComision::mostrar() const {
    cout << "Legajo: " << _legajoAlumno
         << " | Comisión: " << _idComision
         << " | Fecha: ";
    _fecha.mostrar();
    cout << " | Estado: " << (_eliminado ? "Inactiva" : "Activa") << endl;
    cout << endl;
}
