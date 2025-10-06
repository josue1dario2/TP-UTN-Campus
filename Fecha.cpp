#include <iostream>
#include <sstream>
#include "Fecha.h"
#include "Validacion.h"

using namespace std;

Fecha::Fecha()
{
    _dia = 1;
    _mes = 1;
    _anio = 2000;
}

Fecha::Fecha(int dia, int mes, int anio)
{
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

void Fecha::setDia(int dia)
{
    if (dia >= 1 && dia <= 31)
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
    if (anio > 0) {
        _anio = anio;
    }else
        _anio = 2000;
}

int Fecha::getDia() const { return _dia; }
int Fecha::getMes() const { return _mes; }
int Fecha::getAnio() const { return _anio; }

void Fecha::cargar()
{
    int d=0, m=0, a=0;
    bool fechaValida=false;

    while (!fechaValida) {
        d = Validacion::validarEntero("Ingrese el dia: ");
        m = Validacion::validarEntero("Ingrese mes: ");
        a = Validacion::validarEntero("Ingrese anio: ");

        fechaValida=Validacion::esFechaValidaManual(d, m, a);
        if (!fechaValida) {
            cout << "La fecha ingresada es incorrecta. Por favor, intente nuevamente." << endl;
        }
    }

    setDia(d);
    setMes(m);
    setAnio(a);
}

void Fecha::mostrar() const
{
    cout << toString() << endl;
}

string Fecha::toString() const
{
    stringstream ss;
    ss << (_dia < 10 ? "0" : "") << _dia << "/"
       << (_mes < 10 ? "0" : "") << _mes << "/"
       << _anio;
    return ss.str();
}
