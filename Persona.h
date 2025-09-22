#pragma once
#include <string>
// #include "Direccion.h" // Comentado porque aún no está disponible

class Persona {
public:
    Persona();
    Persona(int dni, const char* nombre, const char* apellido, const char* telefono, const char* email);

    int getDni() const;
    void setDni(int dni);

    const char* getNombre() const;
    void setNombre(const char* nombre);

    const char* getApellido() const;
    void setApellido(const char* apellido);

    const char* getTelefono() const;
    void setTelefono(const char* telefono);

    const char* getEmail() const;
    void setEmail(const char* email);

    // Direccion getDireccion() const;
    // void setDireccion(Direccion direccion);

    std::string toString() const;

private:
    int _dni;
    char _nombre[50];
    char _apellido[50];
    char _telefono[50];
    char _email[50];
    // Direccion _direccion;
};