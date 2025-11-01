#include "Examen.h"
#include <iostream>
using std::cin; using std::cout; using std::endl;

Examen::Examen()
    : _idExamen(0), _idComision(0), _legajoAlumno(0),
      _tipoExamen(0), _nota(-1), _corregido(false), _eliminado(false) {}

Examen::Examen(int idExamen, int idComision, int legajoAlumno,
               int tipoExamen, Fecha fecha, bool eliminado)
    : _idExamen(idExamen), _idComision(idComision), _legajoAlumno(legajoAlumno),
      _tipoExamen(tipoExamen), _fecha(fecha), _nota(-1),
      _corregido(false), _eliminado(eliminado) {}

int  Examen::getIdExamen() const { return _idExamen; }
void Examen::setIdExamen(int v){ _idExamen = v; }

int  Examen::getIdComision() const { return _idComision; }
void Examen::setIdComision(int v){ _idComision = v; }

int  Examen::getLegajoAlumno() const { return _legajoAlumno; }
void Examen::setLegajoAlumno(int v){ _legajoAlumno = v; }

int  Examen::getTipoExamen() const { return _tipoExamen; }
void Examen::setTipoExamen(int v){ _tipoExamen = v; }

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

    cout << "\nSeleccione el tipo de examen:\n";
    cout << "---------------------------------\n";
    cout << "1 - Parcial 1\n";
    cout << "2 - Parcial 2\n";
    cout << "3 - Parcial 3\n";
    cout << "4 - Recuperatorio 1\n";
    cout << "5 - Recuperatorio 2\n";
    cout << "6 - Recuperatorio 3\n";
    cout << "7 - Final\n";
    cout << "---------------------------------\n";
    cout << "Ingrese una opción (1-7): ";
    cin >> _tipoExamen;

    cout << "\nFecha del examen:\n";
    _fecha.cargar();

    _nota = -1;
    _corregido = false;
    _eliminado = false;
}

void Examen::inscribir() {
    cout << "=== Inscripción a Examen ===\n";
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
    cout << "\n=== Datos del Examen ===\n";
    cout << "ID Examen: " << _idExamen << endl;
    cout << "ID Comision: " << _idComision << endl;
    cout << "Legajo Alumno: " << _legajoAlumno << endl;

    cout << "TipoExamen: " << _tipoExamen << " (" << getDescripcionTipoExamen() << ")\n";

    cout << "Fecha: ";
    _fecha.mostrar();
    cout << endl;

    cout << "Nota: ";
    if (_nota == -1) cout << "Sin corregir\n";
    else cout << _nota << endl;

    cout << "Corregido: " << (_corregido ? "Sí" : "No") << endl;
    cout << "Eliminado: " << (_eliminado ? "Sí" : "No") << endl;
}

const char* Examen::getDescripcionTipoExamen() const {
    if (_tipoExamen >= 1 && _tipoExamen <= 3) return "Parcial";
    if (_tipoExamen >= 4 && _tipoExamen <= 6) return "Recuperatorio";
    if (_tipoExamen == 7) return "Final";
    return "Desconocido";
}
