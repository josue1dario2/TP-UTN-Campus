#include "Fecha.h"
#include <iostream>
#include <sstream>
using namespace std;

bool Fecha::esBisiesto(int anio) const
{
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasDelMes(int mes, int anio) const
{
    switch (mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    default:
        return 0;
    }
}

Fecha::Fecha()
{
    _dia = 1;
    _mes = 1;
    _anio = 2000;
}

Fecha::Fecha(int dia, int mes, int anio)
{
    setAnio(anio);
    setMes(mes);
    setDia(dia);
}

void Fecha::setDia(int dia)
{
    int maxDias = diasDelMes(_mes, _anio);
    if (dia >= 1 && dia <= maxDias)
        _dia = dia;
    else
        _dia = 1;
}

void Fecha::setMes(int mes)
{
    if (mes >= 1 && mes <= 12)
        _mes = mes;
    else
        _mes = 1;
}

void Fecha::setAnio(int anio)
{
    if (anio >= 1900 && anio <= 2100)
        _anio = anio;
    else
        _anio = 2000;
}

int Fecha::getDia() const { return _dia; }
int Fecha::getMes() const { return _mes; }
int Fecha::getAnio() const { return _anio; }

void Fecha::cargar()
{
    cout << "\tIngrese anio (1900-2100): ";
    cin >> _anio;
    while (_anio < 1900 || _anio > 2100)
    {
        cout << "\tAnio invalido. Reingrese (1900-2100): ";
        cin >> _anio;
    }

    cout << "\tIngrese mes (1-12): ";
    cin >> _mes;
    while (_mes < 1 || _mes > 12)
    {
        cout << "\tMes invalido. Reingrese (1-12): ";
        cin >> _mes;
    }

    cout << "\tIngrese dia (1-" << diasDelMes(_mes, _anio) << "): ";
    cin >> _dia;
    while (_dia < 1 || _dia > diasDelMes(_mes, _anio))
    {
        cout << "\tDia invalido. Reingrese (1-" << diasDelMes(_mes, _anio) << "): ";
        cin >> _dia;
    }
}

void Fecha::mostrar() const {
    cout << (_dia < 10 ? "0" : "") << _dia << "/"
         << (_mes < 10 ? "0" : "") << _mes << "/"
         << _anio << endl;
}

bool Fecha::operator==(const Fecha &otra) const {
    return _anio == otra._anio &&
           _mes == otra._mes &&
           _dia == otra._dia;
}

bool Fecha::operator!=(const Fecha &otra) const {
    return !(*this == otra);
}

bool Fecha::operator<(const Fecha &otra) const {
    if (_anio != otra._anio) return _anio < otra._anio;
    if (_mes != otra._mes) return _mes < otra._mes;
    return _dia < otra._dia;
}

bool Fecha::operator<=(const Fecha &otra) const {
    return (*this < otra) || (*this == otra);
}

bool Fecha::operator>(const Fecha &otra) const {
    return !(*this <= otra);
}

bool Fecha::operator>=(const Fecha &otra) const {
    return !(*this < otra);
}


