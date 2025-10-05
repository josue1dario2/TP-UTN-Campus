#include <iostream>
#include <cstring>

#include "Comision.h"

using namespace std;


// Constructor por defecto
Comision::Comision() {
        setIdComision(0);
        setIdCursada(0);
        setCodigo("");
        setTurno(0);
        setModalidad(0);
        setAula("");
        setCupo(0);
    }
Comision::Comision(int idComision, int idCursada, const char* codigo, int turno, int modalidad, const char* aula, int cupo) {
        setIdComision(idComision);
        setIdCursada(idCursada);
        setCodigo(codigo);
        setTurno(turno);
        setModalidad(modalidad);
        setAula(aula);
        setCupo(cupo);
    }

    // Setters
void Comision::setIdComision(int idComision) { _idComision = idComision; }
void Comision::setIdCursada(int idCursada) { _idCursada = idCursada; }
void Comision::setCodigo(const char* codigo) { strncpy(_codigo, codigo, 19); _codigo[19] = '\0'; }
void Comision::setTurno(int turno) { _turno = turno; }
void Comision::setModalidad(int modalidad) { _modalidad = modalidad; }
void Comision::setAula(const char* aula) { strncpy(_aula, aula, 19); _aula[19] = '\0'; }
void Comision::setCupo(int cupo) { _cupo = cupo; }

// Getters
int Comision::getIdComision() const { return _idComision; }
int Comision::getIdCursada() const { return _idCursada; }
const char* Comision::getCodigo() const { return _codigo; }
int Comision::getTurno() const { return _turno; }
int Comision::getModalidad() const { return _modalidad; }
const char* Comision::getAula() const { return _aula; }
int Comision::getCupo() const { return _cupo; }



    // Método para cargar datos
void Comision::cargar() {

        cout << "Ingrese ID numérico de Comision: ";
        cin >> _idComision;
        cout << "Ingrese ID numérico de Cursada: ";
        cin >> _idCursada;
        cin.ignore();
        cout << "Ingrese codigo alfanumérico: ";
        cin.getline(_codigo, 20);
        cout << "Ingrese turno (número): ";
        cin >> _turno;
        cout << "Ingrese modalidad (número): ";
        cin >> _modalidad;
        cin.ignore();
        cout << "Ingrese aula (alfanumérica): ";
        cin.getline(_aula, 20);
        cout << "Ingrese cupo (número): ";
        cin >> _cupo;
    }

    // Método para mostrar datos
void Comision::mostrar() const {
    cout << toString() << endl;
}

string Comision::toString() const {

    string s=" | ID de la comisión: " + to_string(_idComision)+"\n";
    s+= " | ID de la Cursada: " + to_string(_idCursada)+"\n";
    s+= " | Codigo: " + string(_codigo) +"\n";
    s+= " | Turno: " + to_string(_turno) +"\n";
    s+= " | Modalidad: " + to_string(_modalidad) +"\n";
    s+= " | Aula: " + string(_aula) +"\n";
    s+= " | Cupo: " + to_string(_cupo) +"\n";
    return s;
}

