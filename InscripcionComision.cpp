#include "InscripcionComision.h"
#include <iostream>
using namespace std;

InscripcionComision::InscripcionComision() {
    _legajoAlumno = 0;
    _idComision = 0;
    _estado = 0;   // 0 = Activa
}

InscripcionComision::InscripcionComision(int legajo, int idComision) {
    _legajoAlumno = legajo;
    _idComision = idComision;
    _estado = 0;   // 0 = Activa
}

void InscripcionComision::setLegajoAlumno(int legajo) {
    _legajoAlumno = legajo;
}

void InscripcionComision::setIdComision(int idComision) {
    _idComision = idComision;
}

void InscripcionComision::setFecha(Fecha f) {
    _fecha = f;
}

void InscripcionComision::setEstado(int estado) {
    _estado = estado;
}

int InscripcionComision::getLegajoAlumno() const {
    return _legajoAlumno;
}

int InscripcionComision::getIdComision() const {
    return _idComision;
}

Fecha InscripcionComision::getFecha() const {
    return _fecha;
}

int InscripcionComision::getEstado() const {
    return _estado;
}

void InscripcionComision::cargar() {
    cout << "\n=== Inscripción a Comisión ===\n";
    cout << "Legajo del alumno: ";
    cin >> _legajoAlumno;
    cout << "ID de la comisión: ";
    cin >> _idComision;

    cout << "Fecha de inscripción:\n";
    _fecha.cargar();
    _estado = 0;  // Siempre inicia como activa
}

void InscripcionComision::mostrar() const {
    cout << "Legajo: " << _legajoAlumno
         << " | Comisión: " << _idComision
         << " | Fecha: ";

    _fecha.mostrar();

    cout << " | Estado: ";

    if (_estado == 0) cout << "Activa";
    else if (_estado == 1) cout << "Pendiente de baja";
    else cout << "Baja";

    cout << endl << endl;
}
