#include "Direccion.h"
#include <cstring>
#include <sstream>

Direccion::Direccion()
{
    strcpy(_calle, "");
    strcpy(_provincia, "");
    strcpy(_ciudad, "");
    _numero = 0;
    _codigoPostal = 0;
}

Direccion::Direccion(const char *calle,
                     const char *provincia,
                     const char *ciudad,
                     int numero,
                     int codigoPostal)
{
    setCalle(calle);
    setProvincia(provincia);
    setCiudad(ciudad);
    setNumero(numero);
    setCodigoPostal(codigoPostal);
}

const char *Direccion::getCalle() const
{
    return _calle;
}

const char *Direccion::getProvincia() const
{
    return _provincia;
}

const char *Direccion::getCiudad() const
{
    return _ciudad;
}

int Direccion::getNumero() const
{
    return _numero;
}

int Direccion::getCodigoPostal() const
{
    return _codigoPostal;
}

void Direccion::setCalle(const char *calle)
{
    if (calle != nullptr && strlen(calle) < 50)
    {
        strcpy(_calle, calle);
    }
    else
    {
        strcpy(_calle, "Desconocida");
    }
}

void Direccion::setProvincia(const char *provincia)
{
    if (provincia != nullptr && strlen(provincia) < 50)
    {
        strcpy(_provincia, provincia);
    }
    else
    {
        strcpy(_provincia, "Desconocida");
    }
}

void Direccion::setCiudad(const char *ciudad)
{
    if (ciudad != nullptr && strlen(ciudad) < 50)
    {
        strcpy(_ciudad, ciudad);
    }
    else
    {
        strcpy(_ciudad, "Desconocida");
    }
}

void Direccion::setNumero(int numero)
{
    _numero = (numero > 0) ? numero : 0;
}

void Direccion::setCodigoPostal(int codigoPostal)
{
    _codigoPostal = (codigoPostal > 0) ? codigoPostal : 0;
}

void Direccion::cargar() {
    cout << "Calle: ";
    cin >> _calle;

    cout << "Numero: ";
    cin >> _numero;

    cout << "Ciudad: ";
    cin >> _ciudad;

    cout << "Provincia: ";
    cin >> _provincia;

    cout << "Codigo Postal: ";
    cin >> _codigoPostal;
}

void Direccion::mostrar() const {
    cout << "Calle: " << _calle << " " << _numero << "\n"
         << "Ciudad: " << _ciudad << "\n"
         << "Provincia: " << _provincia << "\n"
         << "Codigo Postal: " << _codigoPostal << "\n";
}