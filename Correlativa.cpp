#include "Correlativa.h"
#include <iostream>

using std::cin; using std::cout; using std::string;

Correlativa::Correlativa()
    : _idMateriaObjetivo(0), _idMateriaRequisito(0),_eliminado(false) {}

Correlativa::Correlativa(int idMateriaObjetivo, int idMateriaRequisito, bool eliminado)
    : _idMateriaObjetivo(idMateriaObjetivo),
      _idMateriaRequisito(idMateriaRequisito), _eliminado(eliminado) {}

int  Correlativa::getIdMateriaObjetivo() const { return _idMateriaObjetivo; }
void Correlativa::setIdMateriaObjetivo(int v) { _idMateriaObjetivo = v; }

int  Correlativa::getIdMateriaRequisito() const { return _idMateriaRequisito; }
void Correlativa::setIdMateriaRequisito(int v) { _idMateriaRequisito = v; }

bool Correlativa::getEliminado() const { return _eliminado; }
void Correlativa::setEliminado(bool v) { _eliminado = v; }

void Correlativa::cargar() {
    cout << "=== Cargar Correlativa ===\n";

    cout << "ID Materia Objetivo: ";
    cin >> _idMateriaObjetivo;

    cout << "ID Materia Requisito: ";
    cin >> _idMateriaRequisito;

    _eliminado = false;
}

void Correlativa::mostrar() const {
    cout << "=== Datos de la Correlativa ===\n";
    cout << "Materia Objetivo: " << _idMateriaObjetivo << "\n";
    cout << "Materia Requisito: " << _idMateriaRequisito << "\n";
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << "\n\n";
}