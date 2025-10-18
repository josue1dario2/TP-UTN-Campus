#include <iostream>
#include <cstring> // Para usar strcpy
#include <string>

#include "Materia.h"

using namespace std;

Materia::Materia() {
    setIdMateria(0);
    setIdCarrera(0);
    setCodigo("");
    setNombre("");
    setCuatrimestreSugerido(0);
    setEliminado(false);
}

Materia::Materia(int idMateria, int idCarrera, const char* codigo, const char* nombre, int cuatrimestreSugerido,const char* estado, bool eliminado = false) {
    setIdMateria(idMateria);
    setIdCarrera(idCarrera);
    setCodigo(codigo);
    setNombre(nombre);
    setCuatrimestreSugerido(cuatrimestreSugerido);
    setEstado(estado);
    setEliminado(eliminado);
    }

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

void Materia::setEstado(const char* estado) {
    strncpy(_estado, estado, sizeof(_estado));
    _estado[sizeof(_estado) - 1] = '\0'; // Para asegurar que termine en null
}

void Materia::setEliminado(bool eliminado) {
    _eliminado = eliminado;
    }

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

const char* Materia::getEstado() const {
    return _estado;
}

bool Materia::getEliminado() const {
    return _eliminado;
    }

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

    setIdMateria(idMateria);
    setIdCarrera(idCarrera);
    setCodigo(codigo);
    setNombre(nombre);
    setCuatrimestreSugerido(cuatrimestreSugerido);
    setEliminado(false);
    }

void Materia::mostrar() const {
        cout << toString() << endl;
}

string Materia::toString() const {
    string s= "\n | ID de Materia: " + to_string(_IdMateria)+"\n";
    s+= " | ID de Carrera: " + to_string(_idCarrera)+"\n";
    s+= " | Código: " + string(_codigo)+"\n";
    s+= " | Nombre: " + string(_nombre)+"\n";
    s+= " | Cuatrimestre sugerido: " + to_string(_cuatrimestreSugerido)+"\n";
    s+= " | Eliminado: " + string((_eliminado ? "Sí" : "No"))+"\n";

    return s;
    }


