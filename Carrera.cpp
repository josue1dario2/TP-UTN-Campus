#include <iostream>
#include <cstring>
#include <string>

#include "Carrera.h"

using namespace std;

// --- Constructor por defecto ---
Carrera::Carrera() {
    _idCarrera = 0;
    strcpy(_nombre, "");   // inicializa con cadena vac�a
    _duracionCuatrimestres = 0;
    _eliminado = false;
}

// --- Constructor con parámetros ---
Carrera::Carrera(int idcarrera, const char* nombre, int duracionCuatrimestres, bool eliminado) {
    set_idCarrera(idcarrera);
    set_nombre(nombre);
    set_duracionCuatrimestres(duracionCuatrimestres);
    set_eliminado(eliminado);

}

// --- Getters ---
int Carrera::get_idCarrera() const { return _idCarrera; }
const char* Carrera::get_nombre() const { return _nombre; }
int Carrera::get_duracionCuatrimestres() const { return _duracionCuatrimestres; }
bool Carrera::get_eliminado() const { return _eliminado; }

// --- Setters ---
void Carrera::set_idCarrera(int idCarrera) { _idCarrera = idCarrera; }
void Carrera::set_nombre(const char* nombre) {
        strncpy(_nombre, nombre, sizeof(_nombre)-1);
        _nombre[sizeof(_nombre)-1] = '\0';
    }
void Carrera::set_duracionCuatrimestres(int duracionCuatrimestres) { _duracionCuatrimestres = duracionCuatrimestres; }
void Carrera::set_eliminado(bool eliminado) { _eliminado = eliminado; }

// --- M�todo cargar (pide datos al usuario) ---
void Carrera::cargar() {
    cout << "Ingrese ID de la carrera: ";
    cin >> _idCarrera;
    cin.ignore(); // limpiar buffer
    cout << "Ingrese _nombre de la carrera: ";
    cin.getline(_nombre, 50);
    cout << "Ingrese duracion en cuatrimestres: ";
    cin >> _duracionCuatrimestres;
    cout << "¿_eliminado? (0 = No, 1 = Si): ";
    cin >> _eliminado;
}

// --- M�todo mostrar ---
void Carrera::mostrar() const {
        cout << toString() << endl;
}

// --- toString ---
string Carrera::toString() const {
    string s = "ID: " + to_string(_idCarrera);
    s += " | Nombre: " + string(_nombre);
    s += " | Duración: " + to_string(_duracionCuatrimestres) + " cuatrimestres";
    s += " | Eliminado: " + string(_eliminado ? "Sí" : "No");
    return s;
}

/*
int _idCarrera;
char _nombre[50];
int _duracionCuatrimestres;
bool _eliminado;

*/



