#include "Correlativa.h"
#include <iostream>

using std::cin; using std::cout; using std::string;

Correlativa::Correlativa()
    : _idCarrera(0), _idMateriaObjetivo(0), _idMateriaRequisito(0),
      _tipo(0), _eliminado(false) {}

Correlativa::Correlativa(int idCarrera, int idMateriaObjetivo, int idMateriaRequisito,
                         int tipo, bool eliminado)
    : _idCarrera(idCarrera), _idMateriaObjetivo(idMateriaObjetivo),
      _idMateriaRequisito(idMateriaRequisito), _tipo(tipo), _eliminado(eliminado) {}

int  Correlativa::getIdCarrera() const { return _idCarrera; }
void Correlativa::setIdCarrera(int v) { _idCarrera = v; }

int  Correlativa::getIdMateriaObjetivo() const { return _idMateriaObjetivo; }
void Correlativa::setIdMateriaObjetivo(int v) { _idMateriaObjetivo = v; }

int  Correlativa::getIdMateriaRequisito() const { return _idMateriaRequisito; }
void Correlativa::setIdMateriaRequisito(int v) { _idMateriaRequisito = v; }

int  Correlativa::getTipo() const { return _tipo; }
void Correlativa::setTipo(int v) { _tipo = v; }

bool Correlativa::getEliminado() const { return _eliminado; }
void Correlativa::setEliminado(bool v) { _eliminado = v; }

std::string Correlativa::toString() const {
    string tipoStr = (_tipo == 1 ? "Regularizada" :
                      _tipo == 2 ? "Aprobada" : "Otro");
    return "Carrera ID: " + std::to_string(_idCarrera) +
           "\nMateria Objetivo ID: " + std::to_string(_idMateriaObjetivo) +
           "\nMateria Requisito ID: " + std::to_string(_idMateriaRequisito) +
           "\nTipo: " + tipoStr +
           "\nEliminado: " + string(_eliminado ? "Sí" : "No");
}

void Correlativa::cargar(){
    cout << "ID Carrera: ";            cin >> _idCarrera;           cin.ignore(10000, '\n');
    cout << "ID Materia Objetivo: ";   cin >> _idMateriaObjetivo;   cin.ignore(10000, '\n');
    cout << "ID Materia Requisito: ";  cin >> _idMateriaRequisito;  cin.ignore(10000, '\n');
    cout << "Tipo (1=Regularizada, 2=Aprobada): ";
    cin >> _tipo;                      cin.ignore(10000, '\n');
    int e = 0; cout << "Eliminado (0/1): ";
    cin >> e;                          cin.ignore(10000, '\n');
    _eliminado = (e != 0);
}

void Correlativa::mostrar() const{
    cout << toString() << "\n";
}
