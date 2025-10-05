#include "Validacion.h"
#include "Cursada.h"
#include <iostream>
#include <cstring>
#include <limits>
#include "OfertaAcademica.h"
using namespace std;

Cursada::Cursada() : OfertaAcademica() {
    setIdCursada(0);
    setCicloLectivo("");

}

Cursada::Cursada(int idCursada, const char* cicloLectivo, int idPlanMateria, int modalidad, const char* aula, bool activa) : OfertaAcademica(idPlanMateria, modalidad, aula, activa) {
    setIdCursada(idCursada);
    setCicloLectivo(cicloLectivo);

}

// Setters
void Cursada::setIdCursada(int idCursada) {
    _idCursada = idCursada;
}

void Cursada::setCicloLectivo(const char* cicloLectivo) {
    strncpy(_cicloLectivo, cicloLectivo, sizeof(_cicloLectivo));
    _cicloLectivo[sizeof(_cicloLectivo) - 1] = '\0';
}

// Getters
int Cursada::getIdCursada() const {
    return _idCursada;
}

const char* Cursada::getCicloLectivo() const {
    return _cicloLectivo;
}

// Métodos
void Cursada::cargar() {
    size_t longMininaCadena=1, longMaximaCadena=20;

    string cadena,mensaje="Ingrese ID de Cursada: ";
    OfertaAcademica::cargar(); // Carga los datos base

    //limpia el búffer:
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    _idCursada=Validacion::validarEntero(mensaje);


    mensaje= "Ingrese Ciclo Lectivo: ";
    cadena= Validacion::pedirEntradaCadena(mensaje, longMininaCadena, longMaximaCadena);
    strncpy(_cicloLectivo, cadena.c_str(),sizeof(_cicloLectivo)-1);
    const char _cicloLectivo[sizeof(_cicloLectivo)-1]="\0";
}

void Cursada::mostrar() const {
    cout << toString() << endl;

}

string Cursada::toString() const {
    string base = OfertaAcademica::toString();
    base += " | ID Cursada: " + to_string(_idCursada)+"\n";
    base += " | Ciclo Lectivo: " + string(_cicloLectivo)+"\n";



    return base;
}

