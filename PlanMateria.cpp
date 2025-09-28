#include "PlanMateria.h"
#include <iostream>
#include <string>

PlanMateria::PlanMateria()
{
    _idPlanMateria = 0;
    _plan = 2014;
    _idMateria = 0;
    _anio = 1;
    _dictado = 1;
    _activo = false;
}

PlanMateria::PlanMateria(int idPlanMateria, int plan, int idMateria, int anio, int dictado, bool activo)
{
    set_idPlanMateria(idPlanMateria);
    set_plan(plan);
    set_idMateria(idMateria);
    set_anio(anio);
    set_dictado(dictado);
    set_activo(activo);
}

int PlanMateria::get_idPlanMateria() const
{
    return _idPlanMateria;
}

int PlanMateria::get_plan() const
{
    return _plan;
}

int PlanMateria::get_idMateria() const
{
    return _idMateria;
}

int PlanMateria::get_anio() const
{
    return _anio;
}

int PlanMateria::get_dictado() const
{
    return _dictado;
}

bool PlanMateria::get_activo() const
{
    return _activo;
}

void PlanMateria::set_idPlanMateria(int idPlanMateria)
{
    if (idPlanMateria >= 0)
    {
        _idPlanMateria = idPlanMateria;
    }
    else
    {
        _idPlanMateria = 0;
    }
}

void PlanMateria::set_plan(int plan)
{
    if (plan >= 2014)
    {
        _plan = plan;
    }
    else
    {
        _plan = 2014;
    }
}

void PlanMateria::set_idMateria(int idMateria)
{
    if (idMateria > 0)
    {
        _idMateria = idMateria;
    }
    else
    {
        _idMateria = 0;
    }
}

void PlanMateria::set_anio(int anio)
{
    // La carrera dura 2 años
    if (anio >= 1 && anio <= 2)
    {
        _anio = anio;
    }
    else
    {
        _anio = 1;
    }
}

void PlanMateria::set_dictado(int dictado)
{
    // Hay 4 cuatrimestres en total (2 por año)
    if (dictado >= 1 && dictado <= 4)
    {
        _dictado = dictado;
    }
    else
    {
        _dictado = 1;
    }
}

void PlanMateria::set_activo(bool activo)
{
    _activo = activo;
}

void PlanMateria::cargar()
{
    int idPlanMateria, plan, idMateria, anio, dictado;
    bool activo;
    int tempActivo;

    std::cout << "Ingrese ID Plan Materia: ";
    std::cin >> idPlanMateria;
    set_idPlanMateria(idPlanMateria);

    std::cout << "Ingrese Plan (minimo 2014): ";
    std::cin >> plan;
    set_plan(plan);

    std::cout << "Ingrese ID Materia: ";
    std::cin >> idMateria;
    set_idMateria(idMateria);

    std::cout << "Ingrese anio de cursada (1 o 2): ";
    std::cin >> anio;
    set_anio(anio);

    std::cout << "Ingrese cuatrimestre (1, 2, 3 o 4): ";
    std::cin >> dictado;
    set_dictado(dictado);

    std::cout << "Esta activo? (1 para SI, 0 para NO): ";
    std::cin >> tempActivo;
    activo = (tempActivo == 1);
    set_activo(activo);
}

void PlanMateria::mostrar() const
{
    std::cout << "ID Plan Materia: " << _idPlanMateria << std::endl;
    std::cout << "Plan: " << _plan << std::endl;
    std::cout << "ID Materia: " << _idMateria << std::endl;
    std::cout << "Anio de cursada: " << _anio << std::endl;

    std::string dictadoStr;
    switch (_dictado)
    {
    case 1:
        dictadoStr = "1er Cuatrimestre";
        break;
    case 2:
        dictadoStr = "2do Cuatrimestre";
        break;
    case 3:
        dictadoStr = "3er Cuatrimestre";
        break;
    case 4:
        dictadoStr = "4to Cuatrimestre";
        break;
    default:
        dictadoStr = "Desconocido";
        break;
    }
    std::cout << "Cuatrimestre: " << dictadoStr << std::endl;

    std::cout << "Activo: " << (_activo ? "SI" : "NO") << std::endl;
}

std::string PlanMateria::toString() const
{
    return "ID Plan Materia: " + std::to_string(_idPlanMateria) +
           ", Plan: " + std::to_string(_plan) +
           ", ID Materia: " + std::to_string(_idMateria) +
           ", Anio: " + std::to_string(_anio) +
           ", Cuatrimestre: " + std::to_string(_dictado) +
           ", Activo: " + (_activo ? "SI" : "NO");
}
