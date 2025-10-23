#pragma once
#include <string>
#include <cstring>
#include "Direccion.h"

class Persona {
public:
    Persona() {
        _dni = 0;
        _eliminado = false;
        strcpy(_nombre, "");
        strcpy(_apellido, "");
        strcpy(_telefono, "");
        strcpy(_email, "");
        _direccion = Direccion();
    }

    Persona(int dni, const char* nombre, const char* apellido,
            const char* telefono, const char* email,
            Direccion direccion, bool eliminado = false) {
        _dni = dni;
        strcpy(_nombre, nombre);
        strcpy(_apellido, apellido);
        strcpy(_telefono, telefono);
        strcpy(_email, email);
        _direccion = direccion;
        _eliminado = eliminado;
    }

    int getDni() const { return _dni; }
    void setDni(int dni) { _dni = dni; }

    const char* getNombre() const { return _nombre; }
    void setNombre(const char* nombre) { strcpy(_nombre, nombre); }

    const char* getApellido() const { return _apellido; }
    void setApellido(const char* apellido) { strcpy(_apellido, apellido); }

    const char* getTelefono() const { return _telefono; }
    void setTelefono(const char* telefono) { strcpy(_telefono, telefono); }

    const char* getEmail() const { return _email; }
    void setEmail(const char* email) { strcpy(_email, email); }

    Direccion getDireccion() const { return _direccion; }
    void setDireccion(Direccion direccion) { _direccion = direccion; }

    bool getEliminado() const { return _eliminado; }
    void setEliminado(bool eliminado) { _eliminado = eliminado; }

    void cargar();
    void mostrar() const;

private:
    int _dni;
    char _nombre[50];
    char _apellido[50];
    char _telefono[50];
    char _email[50];
    Direccion _direccion;
    bool _eliminado;
};
