#include "Correlativa.h"

Correlativa::Correlativa()
    : _idCorrelativa(0),
      _plan(0),
      _idPlanMateriaObjetivo(0),
      _idPlanMateriaReq(0),
      _tipoCorrelativa(0) {
}


Correlativa::Correlativa(int idCorrelativa, int plan, int idObjetivo, int idReq, int tipo)
    : _idCorrelativa(idCorrelativa),
      _plan(plan),
      _idPlanMateriaObjetivo(idObjetivo),
      _idPlanMateriaReq(idReq),
      _tipoCorrelativa(tipo) {
}


// Setters
void Correlativa::setIdCorrelativa(int id) {
    _idCorrelativa = id;
}

void Correlativa::setPlan(int plan) {
    _plan = plan;
}

void Correlativa::setIdPlanMateriaObjetivo(int idObjetivo) {
    _idPlanMateriaObjetivo = idObjetivo;
}

void Correlativa::setIdPlanMateriaReq(int idReq) {
    _idPlanMateriaReq = idReq;
}

void Correlativa::setTipoCorrelativa(int tipo) {
    _tipoCorrelativa = tipo;
}


// Getters
int Correlativa::getIdCorrelativa() const {
    return _idCorrelativa;
}

int Correlativa::getPlan() const {
    return _plan;
}

int Correlativa::getIdPlanMateriaObjetivo() const {
    return _idPlanMateriaObjetivo;
}

int Correlativa::getIdPlanMateriaReq() const {
    return _idPlanMateriaReq;
}

int Correlativa::getTipoCorrelativa() const {
    return _tipoCorrelativa;
}


void Correlativa::mostrar() const {
    std::cout << "ID Correlativa: " << _idCorrelativa << std::endl;
    std::cout << "Plan: " << _plan << std::endl;
    std::cout << "ID Materia Objetivo: " << _idPlanMateriaObjetivo << std::endl;
    std::cout << "ID Materia Requisito: " << _idPlanMateriaReq << std::endl;
    std::cout << "Tipo de Correlativa: " << _tipoCorrelativa << std::endl;
}


void Correlativa::cargar() {
    std::cout << "Ingrese ID Correlativa: ";
    std::cin >> _idCorrelativa;

    std::cout << "Ingrese Plan: ";
    std::cin >> _plan;

    std::cout << "Ingrese ID Materia Objetivo: ";
    std::cin >> _idPlanMateriaObjetivo;

    std::cout << "Ingrese ID Materia Requisito: ";
    std::cin >> _idPlanMateriaReq;

    std::cout << "Ingrese Tipo de Correlativa: ";
    std::cin >> _tipoCorrelativa;
}