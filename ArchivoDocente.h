#pragma once
#include "Docente.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoDocente {
private:
    char _nombre[30];
    int _tamanioRegistro;

public:
    ArchivoDocente(const char *nombre = "Docentes.dat");

    int agregarRegistro(Docente reg);
    bool listarRegistros();
    int buscarRegistro(int legajo);
    Docente leerRegistro(int pos);
    bool modificarRegistro(Docente reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
