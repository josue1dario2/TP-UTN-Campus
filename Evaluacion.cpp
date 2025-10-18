#include <iostream>
#include <cstring>
#include <sstream>
#include "Evaluacion.h"

using namespace std;

Evaluacion::Evaluacion() {
    _idEvaluacion = 0;
    _idMateria    = 0;
    _tipo[0]      = '\0';
    _fecha        = Fecha();
    _eliminado    = false;
}

Evaluacion::Evaluacion(int idEvaluacion, int idMateria, const char* tipo, const Fecha& fecha, bool eliminado = false) {
    _idEvaluacion = idEvaluacion;
    _idMateria    = idMateria;
    if (tipo) {
        strncpy(_tipo, tipo, sizeof(_tipo) - 1);
        _tipo[sizeof(_tipo) - 1] = '\0';
    } else {
        _tipo[0] = '\0';
    }
    _fecha     = fecha;
    _eliminado = eliminado;
}

void Evaluacion::setIdEvaluacion(int idEvaluacion) { _idEvaluacion = idEvaluacion; }
void Evaluacion::setIdMateria(int idMateria)       { _idMateria = idMateria; }
void Evaluacion::setTipo(const char* tipo) {
    if (tipo) {
        strncpy(_tipo, tipo, sizeof(_tipo) - 1);
        _tipo[sizeof(_tipo) - 1] = '\0';
    } else {
        _tipo[0] = '\0';
    }
}
void Evaluacion::setFecha(const Fecha& fecha) { _fecha = fecha; }
void Evaluacion::setEliminado(bool eliminado) { _eliminado = eliminado; }

int Evaluacion::getIdEvaluacion() const { return _idEvaluacion; }
int Evaluacion::getIdMateria() const    { return _idMateria; }
const char* Evaluacion::tipo() const    { return _tipo; }
Fecha Evaluacion::getFecha() const      { return _fecha; }
bool Evaluacion::getEliminado() const   { return _eliminado; }

void Evaluacion::cargar() {
    cout << "ID de Evaluacion: ";
    cin >> _idEvaluacion;

    cout << "ID de Materia: ";
    cin >> _idMateria;

    cout << "Tipo (ej: Parcial/Recup/TP/Final): ";
    cin >> _tipo;

    cout << "Cargar fecha:\n";
    _fecha.cargar();

    _eliminado = false;
}

void Evaluacion::mostrar() const {
    cout << "IdEval: "    << _idEvaluacion << '\n';
    cout << "IdMateria: " << _idMateria    << '\n';
    cout << "Tipo: "      << (_tipo[0] ? _tipo : "(sin tipo)") << '\n';
    cout << "Fecha: "     << _fecha.toString() << '\n';
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << '\n';
}

string Evaluacion::toString() const {
    ostringstream os;
    os << "Evaluacion{"
       << "idEvaluacion=" << _idEvaluacion
       << ", idMateria="  << _idMateria
       << ", tipo="       << (_tipo[0] ? _tipo : "(sin tipo)")
       << ", fecha="      << _fecha.toString()
       << ", eliminado="  << (_eliminado ? "true" : "false")
       << "}";
    return os.str();
}
