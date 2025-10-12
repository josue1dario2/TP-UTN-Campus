#include "MesaExamen.h"
#include "Validacion.h"
#include <limits>
#include <iostream>
using namespace std;

// Constructores
MesaExamen::MesaExamen() : OfertaAcademica() {
    setIdMesa(0);
    setFecha(Fecha());
    setTurno(0);
}

MesaExamen::MesaExamen(int idMesa, int idPlanMateria, int modalidad, const char* aula, bool activa, const Fecha& fecha, int turno)
    : OfertaAcademica(idPlanMateria, modalidad, aula, activa) {
    setIdMesa(idMesa);
    setFecha(fecha);
    setTurno(turno);
}

// Setters
void MesaExamen::setIdMesa(int idMesa) { _idMesa = idMesa; }
void MesaExamen::setFecha(const Fecha& fecha) { _fecha = fecha; }
void MesaExamen::setTurno(int turno) { _turno = turno; }

// Getters
int MesaExamen::getIdMesa() const { return _idMesa; }
Fecha MesaExamen::getFecha() const { return _fecha; }
int MesaExamen::getTurno() const { return _turno; }

// Métodos
void MesaExamen::cargar() {
    OfertaAcademica::cargar();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    _idMesa = Validacion::validarEntero("Ingrese ID de la Mesa de Examen: ");
    cout << "Ingrese fecha de la mesa de examen:\n";
    _fecha.cargar();
    _turno = Validacion::validarEntero("Ingrese turno (numero): ");
}

void MesaExamen::mostrar() const {
    cout << toString() << endl;
}

std::string MesaExamen::toString() const {
    std::string s = OfertaAcademica::toString();
    s += " | ID Mesa: " + std::to_string(_idMesa) + "\n";
    s += " | Fecha: " + _fecha.toString() + "\n";
    s += " | Turno: " + std::to_string(_turno) + "\n";
    return s;
}

