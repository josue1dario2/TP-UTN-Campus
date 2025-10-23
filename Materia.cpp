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
    cout << "=== Cargar Materia ===\n";
    cout << "ID Materia: ";
    cin >> _idMateria;

    cout << "ID Carrera: ";
    cin >> _idCarrera;
    cin.ignore(10000, '\n');

    cout << "Código: ";
    cin.getline(_codigo, sizeof(_codigo));

    cout << "Nombre: ";
    cin.getline(_nombre, sizeof(_nombre));

    cout << "Cuatrimestre sugerido: ";
    cin >> _cuatrimestreSugerido;
    cin.ignore(10000, '\n');

    cout << "Estado (Activa / Inactiva): ";
    cin.getline(_estado, sizeof(_estado));

    _eliminado = false;
}

void Materia::mostrar() const {
    cout << "=== Datos de la Materia ===\n";
    cout << "ID Materia: " << _idMateria << "\n";
    cout << "ID Carrera: " << _idCarrera << "\n";
    cout << "Código: " << _codigo << "\n";
    cout << "Nombre: " << _nombre << "\n";
    cout << "Cuatrimestre sugerido: " << _cuatrimestreSugerido << "\n";
    cout << "Estado: " << _estado << "\n";
    cout << "Eliminado: " << (_eliminado ? "Sí" : "No") << "\n\n";
}


