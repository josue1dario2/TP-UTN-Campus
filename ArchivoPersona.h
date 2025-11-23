#pragma once
#include "Persona.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoPersona {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoPersona(const char *nombre = "Personas.dat");

    int agregarRegistro(Persona reg);
    bool listarRegistros();
    int buscarRegistro(int dni);
    Persona leerRegistro(int pos);
    bool modificarRegistro(Persona reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
