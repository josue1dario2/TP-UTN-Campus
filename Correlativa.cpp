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

void Correlativa::cargar() {
    cout << "=== Cargar Correlativa ===\n";

    cout << "ID Carrera: ";
    cin >> _idCarrera;

    cout << "ID Materia Objetivo: ";
    cin >> _idMateriaObjetivo;

    cout << "ID Materia Requisito: ";
    cin >> _idMateriaRequisito;

    cout << "Tipo de correlativa (1=Regularizada, 2=Aprobada): ";
    cin >> _tipo;

    _eliminado = false;
}

void Correlativa::mostrar() const {
    cout << "=== Datos de la Correlativa ===\n";
    cout << "ID Carrera: " << _idCarrera << "\n";
    cout << "Materia Objetivo: " << _idMateriaObjetivo << "\n";
    cout << "Materia Requisito: " << _idMateriaRequisito << "\n";
    cout << "Tipo: " << (_tipo == 1 ? "Regularizada" :
                        _tipo == 2 ? "Aprobada" : "Desconocido") << "\n";
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << "\n\n";
}