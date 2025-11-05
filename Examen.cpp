#include "Examen.h"
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;

Examen::Examen()
    : _idExamen(0), _idMateria(0), _legajoAlumno(0),
      _nota(-1), _corregido(false), _eliminado(false) {
    std::strcpy(_tipo, "");
}

Examen::Examen(int idExamen, int idMateria, int legajoAlumno,
               const char* tipo, Fecha fecha, bool eliminado)
    : _idExamen(idExamen), _idMateria(idMateria), _legajoAlumno(legajoAlumno),
      _fecha(fecha), _nota(-1), _corregido(false), _eliminado(eliminado) {
    setTipo(tipo);
}

int  Examen::getIdExamen() const { return _idExamen; }
void Examen::setIdExamen(int v){ _idExamen = v; }

int  Examen::getIdMateria() const { return _idMateria; }
void Examen::setIdMateria(int v){ _idMateria = v; }

int  Examen::getLegajoAlumno() const { return _legajoAlumno; }
void Examen::setLegajoAlumno(int v){ _legajoAlumno = v; }

const char* Examen::getTipo() const { return _tipo; }
void Examen::setTipo(const char* v){
    std::strncpy(_tipo, v, sizeof(_tipo));
    _tipo[sizeof(_tipo) - 1] = '\0';
}

Fecha Examen::getFecha() const { return _fecha; }
void  Examen::setFecha(Fecha f){ _fecha = f; }

int  Examen::getNota() const { return _nota; }
void Examen::setNota(int v){ _nota = v; }

bool Examen::getCorregido() const { return _corregido; }
void Examen::setCorregido(bool v){ _corregido = v; }

bool Examen::getEliminado() const { return _eliminado; }
void Examen::setEliminado(bool v){ _eliminado = v; }

void Examen::cargar() {
    cout << "=== Cargar Examen ===\n";
    cout << "ID Examen: ";
    cin >> _idExamen;

    cout << "ID Materia: ";
    cin >> _idMateria;

    cout << "Legajo del Alumno: ";
    cin >> _legajoAlumno;

    cout << "\nSeleccione el tipo de examen:\n";
    cout << "1) Parcial 1\n";
    cout << "2) Parcial 2\n";
    cout << "3) Parcial 3\n";
    cout << "4) Recuperatorio 1\n";
    cout << "5) Recuperatorio 2\n";
    cout << "6) Recuperatorio 3\n";
    cout << "7) Final 1\n";
    cout << "8) Final 2\n";
    cout << "Opción: ";

    int opcion;
    cin >> opcion;
    cin.ignore(10000, '\n');

    switch (opcion) {
        case 1: strcpy(_tipo, "Parcial1"); break;
        case 2: strcpy(_tipo, "Parcial2"); break;
        case 3: strcpy(_tipo, "Parcial3"); break;
        case 4: strcpy(_tipo, "Recuperatorio1"); break;
        case 5: strcpy(_tipo, "Recuperatorio2"); break;
        case 6: strcpy(_tipo, "Recuperatorio3"); break;
        case 7: strcpy(_tipo, "Final1"); break;
        case 8: strcpy(_tipo, "Final2"); break;
        default: strcpy(_tipo, "Desconocido"); break;
    }

    cout << "\nFecha del examen:\n";
    _fecha.cargar();

    _nota = -1;
    _corregido = false;
    _eliminado = false;

    cout << "\nExamen cargado correctamente.\n";
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
    cout << "=== Datos del Examen ===\n";
    cout << "ID Examen: " << _idExamen << "\n";
    cout << "ID Materia: " << _idMateria << "\n";
    cout << "Legajo Alumno: " << _legajoAlumno << "\n";
    cout << "Tipo: " << _tipo << "\n";
    cout << "Fecha: ";
    _fecha.mostrar();
    cout << "Nota: " << (_nota == -1 ? "Sin corregir" : std::to_string(_nota)) << "\n";
    cout << "Corregido: " << (_corregido ? "Sí" : "No") << "\n";
    cout << "Eliminado: " << (_eliminado ? "Sí" : "No") << "\n\n";
}
