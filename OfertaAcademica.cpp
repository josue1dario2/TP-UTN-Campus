

#include <iostream>
#include <cstring>
#include <limits>

#include "OfertaAcademica.h"
#include "Validacion.h"

using namespace std;


// Constructor por defecto
OfertaAcademica::OfertaAcademica() {
    setIdPlanMateria(0);
    setModalidad(0);
    setAula("");
    setActiva(0); // 1 = Sí, 0 = No
    }
OfertaAcademica::OfertaAcademica(int idPlanMateria, int modalidad, const char* aula, bool activa) {

    setIdPlanMateria(idPlanMateria);
    setModalidad(modalidad);
    setAula(aula);
    setActiva(activa);

    }

// Setters

void OfertaAcademica::setIdPlanMateria(int idPlanMateria) { _idPlanMateria = idPlanMateria; }
void OfertaAcademica::setModalidad(int modalidad) { _modalidad = modalidad; }
void OfertaAcademica::setAula(const char* aula) { strncpy(_aula, aula, sizeof(_aula)); _aula[sizeof(_aula)-1] = '\0'; }
void OfertaAcademica::setActiva(bool activa) { _activa = activa; }


// Getters

int OfertaAcademica::getIdPlanMateria() const { return _idPlanMateria; }
int OfertaAcademica::getModalidad() const { return _modalidad; }
const char* OfertaAcademica::getAula() const { return _aula; }
bool OfertaAcademica::getActiva() const { return _activa; }


// Método para cargar datos
void OfertaAcademica::cargar() {
    size_t longMininaCadena=1, longMaximaCadena=20;
    string mensaje,cadena;
    bool larga;

    mensaje="Ingrese num. ID del Plan de la Materia: ";
    _idPlanMateria = Validacion::validarEntero(mensaje);

    mensaje="Ingrese modalidad (numero): ";
    _modalidad= Validacion::validarEntero(mensaje);

    mensaje="Ingrese el aula 2-19 caracteres (letras y números):";

    cadena=Validacion::pedirEntradaCadena(mensaje,longMininaCadena, longMaximaCadena);
    strncpy(_aula, cadena.c_str(),sizeof(_aula)-1);
    const char _aula[sizeof(_aula)-1]="\0";



    _activa = Validacion::validarBool("¿Activa? (1=si, 0=no)");

    }


// Método para mostrar datos
void OfertaAcademica::mostrar() const {
    cout << toString() << endl;
}

string OfertaAcademica::toString() const {

    string s=" | ID del Plan de la materia: " + to_string(_idPlanMateria)+"\n";
    s+= " | Modalidad: " + to_string(_modalidad) +"\n";
    s+= " | Aula: " + string(_aula) +"\n";
    s+= " | Activa: " + string((_activa ? "Sí" : "No")) +"\n";
    return s;
}



