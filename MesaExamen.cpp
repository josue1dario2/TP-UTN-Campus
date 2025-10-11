#include "MesaExamen.h"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

MesaExamen::MesaExamen() : OfertaAcademica() {
    _idMesa = 0;
    _fecha  = Fecha();      // 01/01/1900 por tu ctor default o el que uses
    _turno  = 1;            // FEBRERO por defecto
}

MesaExamen::MesaExamen(int idMesa, const Fecha& fecha, int turno)
: OfertaAcademica()
{
    setIdMesa(idMesa);
    setFecha(fecha);
    setTurno(turno);
}

void MesaExamen::setIdMesa(int v) {
    _idMesa = (v >= 0 ? v : 0);
}

void MesaExamen::setFecha(const Fecha& f) {
    _fecha = f;
}

void MesaExamen::setTurno(int t) {
    if (t < 1) t = 1;
    if (t > 3) t = 3;
    _turno = t;
}

int   MesaExamen::getIdMesa()  const { return _idMesa; }
Fecha MesaExamen::getFecha()   const { return _fecha; }
int   MesaExamen::getTurno()   const { return _turno; }

const char* MesaExamen::turnoTexto() const {
    switch (_turno) {
        case 1: return "FEBRERO";
        case 2: return "JULIO";
        case 3: return "DICIEMBRE";
        default: return "-";
    }
}

void MesaExamen::cargar() {
    cout << "=== Cargar Mesa de Examen ===\n";

    cout << "ID Mesa: ";
    cin >> _idMesa;
    while (_idMesa < 0) {
        cout << "Invalido. Reingrese (>=0): ";
        cin >> _idMesa;
    }

    cout << "Fecha de mesa:\n";
    _fecha.cargar();

    cout << "Turno:\n";
    cout << "  1) FEBRERO\n";
    cout << "  2) JULIO\n";
    cout << "  3) DICIEMBRE\n";
    cout << "Elegir opcion (1-3): ";
    cin >> _turno;
    while (_turno < 1 || _turno > 3) {
        cout << "Opcion invalida. Reingrese (1-3): ";
        cin >> _turno;
    }
}

void MesaExamen::mostrar() const {
    cout << toString() << endl;
}

std::string MesaExamen::toString() const {
    stringstream ss;
    ss << "Mesa #" << _idMesa
       << " | Fecha: " << _fecha.toString()
       << " | Turno: " << turnoTexto();
    return ss.str();
}
