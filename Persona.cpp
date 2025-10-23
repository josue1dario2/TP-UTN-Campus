#include "Persona.h"
#include "Direccion.h" 
#include <cstring>

Persona::Persona()
    : _dni(0), _direccion(), _eliminado(false) {
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    strcpy(_email, "");
}

Persona::Persona(int dni, const char* nombre, const char* apellido,
                 const char* telefono, const char* email,
                 Direccion direccion, bool eliminado)
    : _dni(dni), _direccion(direccion), _eliminado(eliminado) {
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEmail(email);
}


int Persona::getDni() const {
    return _dni;
}

void Persona::setDni(int dni) {
    _dni = dni;
}

const char* Persona::getNombre() const {
    return _nombre;
}

void Persona::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, sizeof(_nombre));
    _nombre[sizeof(_nombre) - 1] = '\0';
}

const char* Persona::getApellido() const {
    return _apellido;
}

void Persona::setApellido(const char* apellido) {
    strncpy(_apellido, apellido, sizeof(_apellido));
    _apellido[sizeof(_apellido) - 1] = '\0';
}

const char* Persona::getTelefono() const {
    return _telefono;
}

void Persona::setTelefono(const char* telefono) {
    strncpy(_telefono, telefono, sizeof(_telefono));
    _telefono[sizeof(_telefono) - 1] = '\0';
}

const char* Persona::getEmail() const {
    return _email;
}

void Persona::setEmail(const char* email) {
    strncpy(_email, email, sizeof(_email));
    _email[sizeof(_email) - 1] = '\0';
}

Direccion Persona::getDireccion() const {
    return _direccion;
}

void Persona::setDireccion(Direccion direccion) {
    _direccion = direccion;
}
bool Persona::getEliminado() const {
    return _eliminado;
}

void Persona::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

void Persona::cargar(){
    cout << "DNI: ";
    cin >> _dni;

    cout << "Nombre: ";
    cin >> _nombre;

    cout << "Apellido: ";
    cin >> _apellido;

    cout << "Telefono: ";
    cin >> _telefono;

    cout << "Email: ";
    cin >> _email;

    cout << "Direccion:\n";
    _direccion.cargar();

    _eliminado = false;
}

void Persona::mostrar() const{
    cout << "DNI: "      << _dni      << "\n"
         << "Nombre: "   << _nombre   << "\n"
         << "Apellido: " << _apellido << "\n"
         << "Telefono: " << _telefono << "\n"
         << "Email: "    << _email    << "\n"
         << "Direccion: " << _direccion.mostrar() << "\n"
         << "Eliminado: " << (_eliminado ? "Si" : "No") << "\n";
}