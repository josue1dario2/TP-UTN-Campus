#include "Examen.h"
#include <iostream>
using std::cin; using std::cout;

Examen::Examen()
    : _idExamen(0), _idComision(0), _legajoAlumno(0),
      _numero(0), _nota(-1), _corregido(false), _eliminado(false) {
    std::strcpy(_tipo, "");
    // _fecha por defecto
}

Examen::Examen(int idExamen, int idComision, int legajoAlumno,
               const char* tipo, int numero, Fecha fecha, bool eliminado)
    : _idExamen(idExamen), _idComision(idComision), _legajoAlumno(legajoAlumno),
      _numero(numero), _fecha(fecha), _nota(-1), _corregido(false), _eliminado(eliminado) {
    setTipo(tipo);
}

int  Examen::getIdExamen() const { return _idExamen; }
void Examen::setIdExamen(int v){ _idExamen = v; }

int  Examen::getIdComision() const { return _idComision; }
void Examen::setIdComision(int v){ _idComision = v; }

int  Examen::getLegajoAlumno() const { return _legajoAlumno; }
void Examen::setLegajoAlumno(int v){ _legajoAlumno = v; }

const char* Examen::getTipo() const { return _tipo; }
void Examen::setTipo(const char* v){
    std::strncpy(_tipo, v, sizeof(_tipo));
    _tipo[sizeof(_tipo)-1] = '\0';
}

int  Examen::getNumero() const { return _numero; }
void Examen::setNumero(int v){ _numero = v; }

Fecha Examen::getFecha() const { return _fecha; }
void  Examen::setFecha(Fecha f){ _fecha = f; }

int  Examen::getNota() const { return _nota; }
void Examen::setNota(int v){ _nota = v; }

bool Examen::getCorregido() const { return _corregido; }
void Examen::setCorregido(bool v){ _corregido = v; }

bool Examen::getEliminado() const { return _eliminado; }
void Examen::setEliminado(bool v){ _eliminado = v; }

void Examen::cargar() {
    cout << "=== Crear nuevo Examen ===\n";
    cout << "ID Examen: ";
    cin >> _idExamen;

    cout << "ID Comision: ";
    cin >> _idComision;

    cout << "Tipo (Parcial/Final): ";
    cin >> _tipo;

    if (strcmp(_tipo, "Parcial") == 0 || strcmp(_tipo, "parcial") == 0) {
        cout << "Numero de parcial (1-3): ";
        cin >> _numero;
    } else {
        _numero = 0;
    }

    cout << "Fecha del examen:\n";
    _fecha.cargar();

    _nota = -1;
    _corregido = false;
    _eliminado = false;
}

void Examen::inscribir() {
    cout << "=== Inscripcion a Examen ===\n";
    cout << "Legajo del alumno: ";
    cin >> _legajoAlumno;
    _corregido = false;
    _nota = -1;
}

void Examen::corregir(int nota) {
    _nota = nota;
    _corregido = true;
}

void Examen::mostrar() const {
    cout << "=== Datos del Examen ===\n";
    cout << "ID Examen: " << _idExamen << "\n";
    cout << "ID Comision: " << _idComision << "\n";
    cout << "Legajo Alumno: " << _legajoAlumno << "\n";
    cout << "Tipo: " << _tipo << "\n";
    if (strcmp(_tipo, "Parcial") == 0 || strcmp(_tipo, "parcial") == 0)
        cout << "Numero: " << _numero << "\n";
    cout << "Fecha: ";
    _fecha.mostrar();
    cout << "Nota: ";
    if (_nota == -1)
        cout << "Sin corregir\n";
    else
        cout << _nota << "\n";
    cout << "Corregido: " << (_corregido ? "Sí" : "No") << "\n";
    cout << "Eliminado: " << (_eliminado ? "Sí" : "No") << "\n\n";
}
