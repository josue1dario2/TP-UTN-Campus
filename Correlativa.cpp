#include "Correlativa.h"
#include "Validacion.h"
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

    _idMateriaObjetivo = Validacion::validarEnteroEnRango("\n\tID Materia Objetivo: ",1,10000);
    _idMateriaRequisito = Validacion::validarEnteroEnRango("\n\tID Materia Requisito: ",1,10000);

    _eliminado = false;

}

void Correlativa::mostrar() const {
    cout << "\t=== Datos de la Correlativa ===\n";
    cout << "\tMateria Objetivo: " << _idMateriaObjetivo << "\n";
    cout << "\tMateria Requisito: " << _idMateriaRequisito << "\n";
    cout << "\tEliminado: " << (_eliminado ? "Si" : "No") << "\n\n";
}
