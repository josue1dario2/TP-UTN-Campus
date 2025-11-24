#include "Examen.h"
#include <iostream>
#include <iomanip>
using namespace std;

Examen::Examen() {
    _idExamen = 0;
    _idMateria = 0;
    _legajoAlumno = 0;
    strcpy(_tipo, "");
    _numeroParcial = 0;
    _nota = -1;
    _corregido = false;
    _eliminado = false;
}

Examen::Examen(int idExamen,
               int idMateria,
               int legajoAlumno,
               const char* tipo,
               int numeroParcial,
               Fecha fecha,
               bool eliminado)
{
    _idExamen = idExamen;
    _idMateria = idMateria;
    _legajoAlumno = legajoAlumno;
    strcpy(_tipo, tipo);
    _numeroParcial = numeroParcial;
    _fecha = fecha;
    _nota = -1;
    _corregido = false;
    _eliminado = eliminado;
}

// ---------------------------------------------------------
// GETTERS / SETTERS
// ---------------------------------------------------------
int Examen::getIdExamen() const { return _idExamen; }
void Examen::setIdExamen(int v) { _idExamen = v; }

int Examen::getIdMateria() const { return _idMateria; }
void Examen::setIdMateria(int v) { _idMateria = v; }

int Examen::getLegajoAlumno() const { return _legajoAlumno; }
void Examen::setLegajoAlumno(int v) { _legajoAlumno = v; }

const char* Examen::getTipo() const { return _tipo; }
void Examen::setTipo(const char* v) { strcpy(_tipo, v); }

int Examen::getNumeroParcial() const { return _numeroParcial; }
void Examen::setNumeroParcial(int n) { _numeroParcial = n; }

Fecha Examen::getFecha() const { return _fecha; }
void Examen::setFecha(Fecha f) { _fecha = f; }

int Examen::getNota() const { return _nota; }
void Examen::setNota(int v) { _nota = v; }

bool Examen::getCorregido() const { return _corregido; }
void Examen::setCorregido(bool v) { _corregido = v; }

bool Examen::getEliminado() const { return _eliminado; }
void Examen::setEliminado(bool v) { _eliminado = v; }

// ---------------------------------------------------------
// MÉTODOS
// ---------------------------------------------------------
void Examen::inscribir() {
    _corregido = false;
    _nota = -1;
}

void Examen::corregir(int nota) {
    _nota = nota;
    _corregido = true;
}

void Examen::cargar() {
    cout << "ID materia: ";
    cin >> _idMateria;

    cout << "Legajo alumno: ";
    cin >> _legajoAlumno;

    cout << "Tipo (Parcial/Recuperatorio/Final): ";
    cin >> _tipo;

    if (strcmp(_tipo, "Parcial") == 0 || strcmp(_tipo, "Recuperatorio") == 0) {
        cout << "Número de parcial (1 o 2): ";
        cin >> _numeroParcial;
    } else {
        _numeroParcial = 0; // Final => siempre 0
    }

    _fecha.cargar();

    cout << "Nota: ";
    cin >> _nota;

    _corregido = true;
}

void Examen::mostrar() const {
    cout << "ID Examen: " << _idExamen << endl;
    cout << "ID Materia: " << _idMateria << endl;
    cout << "Legajo Alumno: " << _legajoAlumno << endl;
    cout << "Tipo: " << _tipo;

    if (strcmp(_tipo, "Final") != 0) {
        cout << " (" << _numeroParcial << ")";
    }

    cout << endl;

    cout << "Fecha: ";
    _fecha.mostrar();
    cout << endl;

    if (_corregido) {
        cout << "Nota: " << _nota << endl;
    } else {
        cout << "Nota: Sin corregir" << endl;
    }

    cout << "Estado: " << (_eliminado ? "Eliminado" : "Activo") << endl;
}
