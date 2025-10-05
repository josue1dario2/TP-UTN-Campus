#include <iostream>
#include <cstring> // Para usar strcpy
#include <string>

#include "Materia.h"

using namespace std;

// Constructor por defecto
Materia::Materia() {
    setIdMateria(0);
    setIdCarrera(0);
    setCodigo("");
    setNombre("");
    setCuatrimestreSugerido(0);
    setEliminado(false);
}

    // Constructor parametrizado
Materia::Materia(int idMateria, int idCarrera, const char* codigo, const char* nombre, int cuatrimestreSugerido, bool eliminado) {
    setIdMateria(idMateria);
    setIdCarrera(idCarrera);
    setCodigo(codigo);
    setNombre(nombre);
    setCuatrimestreSugerido(cuatrimestreSugerido);
    setEliminado(eliminado);
    }

    // Setters
void Materia::setIdMateria(int idMateria) {
    _IdMateria = idMateria;
    }

void Materia::setIdCarrera(int idCarrera) {
    _idCarrera = idCarrera;
    }

void Materia::setCodigo(const char* codigo) {
    strncpy(_codigo, codigo, sizeof(_codigo));
    _codigo[sizeof(_codigo) - 1] = '\0'; // Para asegurar que termine en null
    }

void Materia::setNombre(const char* nombre) {
        strncpy(_nombre, nombre, sizeof(_nombre));
        _nombre[sizeof(_nombre) - 1] = '\0';
    }

void Materia::setCuatrimestreSugerido(int cuatrimestreSugerido) {
    _cuatrimestreSugerido = cuatrimestreSugerido;
    }

void Materia::setEliminado(bool eliminado) {
    _eliminado = eliminado;
    }

    // Getters
int Materia::getIdMateria() const {
    return _IdMateria;
    }

    int Materia::getIdCarrera() const {
        return _idCarrera;
    }

const char* Materia::getCodigo() const {
    return _codigo;
    }

const char* Materia::getNombre() const {
    return _nombre;
    }

int Materia::getCuatrimestreSugerido() const {
    return _cuatrimestreSugerido;
    }

bool Materia::getEliminado() const {
    return _eliminado;
    }

    // Método para cargar datos por consola
void Materia::cargar() {
    int idMateria, idCarrera, cuatrimestreSugerido;
    char codigo[10], nombre[50];
    bool eliminado;

    cout << "ID de materia: ";
    cin >> idMateria;
    cin.ignore();

    cout << "ID de Carrera: ";
    cin >> idCarrera;
    cin.ignore();

    cout << "Código: ";
    cin.getline(codigo, sizeof(codigo));

    cout << "Nombre: ";
    cin.getline(nombre, sizeof(nombre));

    cout << "Cuatrimestre sugerido: ";
    cin >> cuatrimestreSugerido;

    cout << "¿Está _eliminado? (1 = Sí, 0 = No): ";
    cin >> eliminado;

    // Usar setters
    setIdMateria(idMateria);
    setIdCarrera(idCarrera);
    setCodigo(codigo);
    setNombre(nombre);
    setCuatrimestreSugerido(cuatrimestreSugerido);
    setEliminado(eliminado);
    }

void Materia::mostrar() const {
        cout << toString() << endl;
}

    // Método para mostrar datos por consola
string Materia::toString() const {
    string s= "\n | ID de Materia: " + to_string(_IdMateria)+"\n";
    s+= " | ID de Carrera: " + to_string(_idCarrera)+"\n";
    s+= " | Código: " + string(_codigo)+"\n";
    s+= " | Nombre: " + string(_nombre)+"\n";
    s+= " | Cuatrimestre sugerido: " + to_string(_cuatrimestreSugerido)+"\n";
    s+= " | Eliminado: " + string((_eliminado ? "Sí" : "No"))+"\n";

    return s;
    }


