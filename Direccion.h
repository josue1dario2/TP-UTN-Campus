#pragma once
#include <iostream>
#include <string>
using namespace std;

class Direccion
{
public:
    Direccion();
    Direccion(const char *calle,
              const char *provincia,
              const char *ciudad,
              int numero,
              int codigoPostal);

    const char *getCalle() const;
    const char *getProvincia() const;
    const char *getCiudad() const;
    int getNumero() const;
    int getCodigoPostal() const;

    void setCalle(const char *calle);
    void setProvincia(const char *provincia);
    void setCiudad(const char *ciudad);
    void setNumero(int numero);
    void setCodigoPostal(int codigoPostal);

    void cargar(const char *calle,
                const char *provincia,
                const char *ciudad,
                int numero,
                int codigoPostal);

    string toString() const;
    void mostrar() const;

private:
    char _calle[50];
    char _provincia[50];
    char _ciudad[50];
    int _numero;
    int _codigoPostal;
};
