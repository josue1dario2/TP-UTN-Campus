#include "Comision.h"
#include <iostream>
#include <cstring>
using namespace std;

Comision::Comision() {
    _idComision = 0;
    _idMateria = 0;
    _legajoDocente = 0;
    _anio = 0;
    strcpy(_turno, "Sin definir");
    _eliminado = false;
}

Comision::Comision(int idComision, int idMateria, int legajoDocente, int anio, const char* turno, bool eliminado) {
    _idComision = idComision;
    _idMateria = idMateria;
    _legajoDocente = legajoDocente;
    _anio = anio;
    strcpy(_turno, turno);
    _eliminado = eliminado;
}

// Getters
int Comision::getIdComision() const { return _idComision; }
int Comision::getIdMateria() const { return _idMateria; }
int Comision::getLegajoDocente() const { return _legajoDocente; }
int Comision::getAnio() const { return _anio; }
const char* Comision::getTurno() const { return _turno; }
bool Comision::getEliminado() const { return _eliminado; }

// Setters
void Comision::setIdComision(int v) { _idComision = v; }
void Comision::setIdMateria(int v) { _idMateria = v; }
void Comision::setLegajoDocente(int v) { _legajoDocente = v; }
void Comision::setAnio(int v) { _anio = v; }
void Comision::setTurno(const char* t) { strcpy(_turno, t); }
void Comision::setEliminado(bool e) { _eliminado = e; }

// Métodos
void Comision::cargar() {
    cout << "\n=== Cargar nueva comisión ===\n";
    cout << "ID Comision: ";
    cin >> _idComision;
    cout << "ID Materia: ";
    cin >> _idMateria;
    cout << "Legajo Docente: ";
    cin >> _legajoDocente;
    cout << "Año: ";
    cin >> _anio;
    cout << "Turno: ";
    cin.ignore();
    cin.getline(_turno, 20);
    _eliminado = false;
}

void Comision::mostrar() const {
    cout << "Comisión ID: " << _idComision
         << " | Materia ID: " << _idMateria
         << " | Docente Legajo: " << _legajoDocente
         << " | Año: " << _anio
         << " | Turno: " << _turno << endl;
}
