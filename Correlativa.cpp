#include "Correlativa.h"
using namespace std;

Correlativa::Correlativa() {
    _idCorrelativa      = 0;
    _idCarrera          = 0;
    _idMateriaObjetivo  = 0;
    _idMateriaRequisito = 0;
    _tipoCorrelativa    = 0;
    _eliminado          = false;
}

Correlativa::Correlativa(int idCorrelativa, int idCarrera, int idMateriaObjetivo,
                         int idMateriaRequisito, int tipoCorrelativa, bool eliminado = false) {
    _idCorrelativa      = idCorrelativa;
    _idCarrera          = idCarrera;
    _idMateriaObjetivo  = idMateriaObjetivo;
    _idMateriaRequisito = idMateriaRequisito;
    _tipoCorrelativa    = tipoCorrelativa;
    _eliminado          = eliminado;
}

void Correlativa::setIdCorrelativa(int idCorrelativa)        { _idCorrelativa = idCorrelativa; }
void Correlativa::setIdCarrera(int idCarrera)                 { _idCarrera = idCarrera; }
void Correlativa::setIdMateriaObjetivo(int idMateriaObjetivo) { _idMateriaObjetivo = idMateriaObjetivo; }
void Correlativa::setIdMateriaRequisito(int idMateriaRequisito) { _idMateriaRequisito = idMateriaRequisito; }
void Correlativa::setTipoCorrelativa(int tipoCorrelativa)     { _tipoCorrelativa = tipoCorrelativa; }
void Correlativa::setEliminado(bool eliminado)                { _eliminado = eliminado; }

int  Correlativa::getIdCorrelativa() const       { return _idCorrelativa; }
int  Correlativa::getIdCarrera() const           { return _idCarrera; }
int  Correlativa::getIdMateriaObjetivo() const   { return _idMateriaObjetivo; }
int  Correlativa::getIdMateriaRequisito() const  { return _idMateriaRequisito; }
int  Correlativa::getTipoCorrelativa() const     { return _tipoCorrelativa; }
bool Correlativa::getEliminado() const           { return _eliminado; }


void Correlativa::cargar() {
    cout << "ID Correlativa: ";
    cin  >> _idCorrelativa;

    cout << "ID Carrera: ";
    cin  >> _idCarrera;

    cout << "ID Materia Objetivo: ";
    cin  >> _idMateriaObjetivo;

    cout << "ID Materia Requisito: ";
    cin  >> _idMateriaRequisito;

    cout << "Tipo Correlativa (1=Regularizada, 2=Aprobada, etc.): ";
    cin  >> _tipoCorrelativa;

    _eliminado = false;
}

void Correlativa::mostrar() const {
    cout << "IdCorrelativa:      " << _idCorrelativa      << '\n';
    cout << "IdCarrera:          " << _idCarrera          << '\n';
    cout << "IdMateriaObjetivo:  " << _idMateriaObjetivo  << '\n';
    cout << "IdMateriaRequisito: " << _idMateriaRequisito << '\n';
    cout << "TipoCorrelativa:    " << _tipoCorrelativa    << '\n';
    cout << "Eliminado:          " << (_eliminado ? "Si" : "No") << '\n';
}
