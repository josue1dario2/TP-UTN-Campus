#include <iostream>
#include <sstream>
#include "EvaluacionBase.h"

using namespace std;

EvaluacionBase::EvaluacionBase()
{
    _fecha = Fecha();
    _nota = 0;
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
    if (nota >= 0 && nota <= 10)
        _nota = nota;
    else
        _nota = 0;
}

Fecha EvaluacionBase::getFecha() const { return _fecha; }
int EvaluacionBase::getNota() const { return _nota; }

void EvaluacionBase::cargar()
{
    cout << "Cargar fecha de la evaluación:" << endl;
    _fecha.cargar();

    int n;
    cout << "Ingrese nota (0-10): ";
    cin >> n;
    setNota(n);
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
