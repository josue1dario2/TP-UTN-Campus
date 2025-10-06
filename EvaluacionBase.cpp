#include "EvaluacionBase.h"
#include <iostream>
#include <sstream>
using namespace std;

EvaluacionBase::EvaluacionBase()
{
    _fecha = Fecha();
    _nota = 1;
}

EvaluacionBase::EvaluacionBase(const Fecha &fecha, int nota)
{
    setFecha(fecha);
    setNota(nota);
}

void EvaluacionBase::setFecha(const Fecha &fecha)
{
    _fecha = fecha;
}

void EvaluacionBase::setNota(int nota)
{
    if (nota >= 1 && nota <= 10)
        _nota = nota;
    else
        _nota = 1;
}

Fecha EvaluacionBase::getFecha() const { return _fecha; }
int EvaluacionBase::getNota() const { return _nota; }

void EvaluacionBase::cargar()
{
    cout << "Cargar fecha de evaluacion:" << endl;
    _fecha.cargar();

    cout << "Ingrese nota (0-10): ";
    cin >> _nota;
    while (_nota < 1 || _nota > 10)
    {
        cout << "Nota invalida. Reingrese (1-10): ";
        cin >> _nota;
    }
}

void EvaluacionBase::mostrar() const
{
    cout << toString() << endl;
}

string EvaluacionBase::toString() const
{
    stringstream ss;
    ss << "Fecha: " << _fecha.toString()
       << " | Nota: " << _nota;
    return ss.str();
}
