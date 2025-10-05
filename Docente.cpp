#include <iostream>
#include <cstring>
#include <string>

#include "Docente.h"

Docente::Docente() : Persona()
{
    _idDocente = 0;
    _legajo = 0;
    strcpy(_rol, "");
    _eliminado = false;
}

Docente::Docente(int idDocente, int legajo, const char *rol, bool eliminado, const char *nombre, const char *apellido, int dni)
    : Persona(nombre, apellido, dni)
{
    _idDocente = idDocente;
    _legajo = legajo;
    strcpy(_rol, rol);
    _eliminado = eliminado;
}

void Docente::setIdDocente(int idDocente)
{
    _idDocente = idDocente;
}

void Docente::setLegajo(int legajo)
{
    _legajo = legajo;
}

void Docente::setRol(const char *rol)
{
    strcpy(_rol, rol);
}

void Docente::setEliminado(bool eliminado)
{
    _eliminado = eliminado;
}

int Docente::getIdDocente() const
{
    return _idDocente;
}

int Docente::getLegajo() const
{
    return _legajo;
}

const char *Docente::getRol() const
{
    return _rol;
}

bool Docente::getEliminado() const
{
    return _eliminado;
}

void Docente::cargar()
{
    Persona::cargar();

    std::cout << "Ingrese el legajo: ";
    std::cin >> _legajo;
    std::cout << "Ingrese el rol: ";
    std::cin.ignore();
    std::cin.getline(_rol, 20);

    _eliminado = false;
}

void Docente::mostrar() const
{
    Persona::mostrar();

    std::cout << "Legajo: " << _legajo << std::endl;
    std::cout << "Rol: " << _rol << std::endl;
}

std::string Docente::toString() const
{
    std::string str = Persona::toString();

    str += ", Legajo: " + std::to_string(_legajo);
    str += ", Rol: " + std::string(_rol);
    return str;
}