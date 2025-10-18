// MesaExamen.cpp
#include "MesaExamen.h"
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

static const char* turnoToText(int t) {
    switch (t) {
        case 1: return "FEBRERO";
        case 2: return "JULIO";
        case 3: return "DICIEMBRE";
        default: return "DESCONOCIDO";
    }
}

MesaExamen::MesaExamen()
: _idMesa(0), _fecha(), _turno(0), _eliminado(false) {}

MesaExamen::MesaExamen(int idMesa, const Fecha& fecha, int turno, bool eliminado)
: _idMesa(idMesa), _fecha(fecha), _turno(turno), _eliminado(eliminado) {}

void MesaExamen::setIdMesa(int v)          { _idMesa = v; }
void MesaExamen::setFecha(const Fecha& f)  { _fecha = f; }
void MesaExamen::setTurno(int t)           { _turno = t; }
void MesaExamen::setEliminado(bool e)      { _eliminado = e; }

int   MesaExamen::getIdMesa() const        { return _idMesa; }
Fecha MesaExamen::getFecha() const         { return _fecha; }
int   MesaExamen::getTurno() const         { return _turno; }
bool  MesaExamen::getEliminado() const     { return _eliminado; }

const char* MesaExamen::turnoTexto() const {
    return turnoToText(_turno);
}

void MesaExamen::cargar() {
    cout << "ID de la mesa: ";
    cin >> _idMesa;

    cout << "Turno (1=FEBRERO, 2=JULIO, 3=DICIEMBRE): ";
    cin >> _turno;

    cout << "Fecha de la mesa:\n";
    _fecha.cargar();

    _eliminado = false;

}

void MesaExamen::mostrar() const {
    cout << "Mesa de Examen\n";
    cout << "  ID: " << _idMesa << "\n";
    cout << "  Turno: " << turnoTexto() << " (" << _turno << ")\n";
    cout << "  Fecha: "; _fecha.mostrar();
    cout << "  Estado: " << (_eliminado ? "Eliminada" : "Activa") << "\n";
}

std::string MesaExamen::toString() const {
    ostringstream os;
    os << " | ID: " << _idMesa << "\n"
       << " | Turno: " << turnoTexto() << " (" << _turno << ")\n"
       << " | Fecha: " << _fecha.toString() << "\n"
       << " | Estado: " << (_eliminado ? "Eliminada" : "Activa") << "\n";
    return os.str();
}
