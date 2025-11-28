#include "Persona.h"
#include <iostream>
#include <cstring>
using namespace std;

Persona::Persona()
    : _dni(0), _fechaNacimiento(), _direccion(), _eliminado(false) {
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    strcpy(_email, "");
}

Persona::Persona(int dni, const char* nombre, const char* apellido,
                 const char* telefono, const char* email,
                 Direccion direccion, Fecha fechaNacimiento, bool eliminado)
    : _dni(dni), _direccion(direccion),
      _fechaNacimiento(fechaNacimiento), _eliminado(eliminado) {
    strncpy(_nombre, nombre, sizeof(_nombre));
    _nombre[sizeof(_nombre) - 1] = '\0';
    strncpy(_apellido, apellido, sizeof(_apellido));
    _apellido[sizeof(_apellido) - 1] = '\0';
    strncpy(_telefono, telefono, sizeof(_telefono));
    _telefono[sizeof(_telefono) - 1] = '\0';
    strncpy(_email, email, sizeof(_email));
    _email[sizeof(_email) - 1] = '\0';
}

int Persona::getDni() const { return _dni; }
void Persona::setDni(int dni) { _dni = dni; }

const char* Persona::getNombre() const { return _nombre; }
void Persona::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, sizeof(_nombre));
    _nombre[sizeof(_nombre) - 1] = '\0';
}

const char* Persona::getApellido() const { return _apellido; }
void Persona::setApellido(const char* apellido) {
    strncpy(_apellido, apellido, sizeof(_apellido));
    _apellido[sizeof(_apellido) - 1] = '\0';
}

const char* Persona::getTelefono() const { return _telefono; }
void Persona::setTelefono(const char* telefono) {
    strncpy(_telefono, telefono, sizeof(_telefono));
    _telefono[sizeof(_telefono) - 1] = '\0';
}

const char* Persona::getEmail() const { return _email; }
void Persona::setEmail(const char* email) {
    strncpy(_email, email, sizeof(_email));
    _email[sizeof(_email) - 1] = '\0';
}

Direccion Persona::getDireccion() const { return _direccion; }
void Persona::setDireccion(Direccion direccion) { _direccion = direccion; }

Fecha Persona::getFechaNacimiento() const { return _fechaNacimiento; }
void Persona::setFechaNacimiento(Fecha f) { _fechaNacimiento = f; }

bool Persona::getEliminado() const { return _eliminado; }
void Persona::setEliminado(bool eliminado) { _eliminado = eliminado; }

void Persona::cargar() {
    cout << "=== Cargar Persona ===\n";
    cout << "DNI: ";
    cin >> _dni;
    cin.ignore();

    cout << "Nombre: ";
    cin.getline(_nombre, 50);

    cout << "Apellido: ";
    cin.getline(_apellido, 50);

    cout << "Teléfono: ";
    cin.getline(_telefono, 50);

    cout << "Email: ";
    cin.getline(_email, 50);

    cout << "\n--- Cargar dirección ---\n";
    _direccion.cargar();

    cout << "\n--- Fecha de nacimiento ---\n";
    _fechaNacimiento.cargar();

    _eliminado = false;
}

void Persona::mostrar() const {
    cout << "=== Datos de la Persona ===\n";
    cout << "DNI: " << _dni << "\n";
    cout << "Nombre: " << _nombre << "\n";
    cout << "Apellido: " << _apellido << "\n";
    cout << "Teléfono: " << _telefono << "\n";
    cout << "Email: " << _email << "\n";
    cout << "Dirección: ";
    _direccion.mostrar();
    cout << "Fecha de nacimiento: ";
    _fechaNacimiento.mostrar();
    cout << "\n";
}
