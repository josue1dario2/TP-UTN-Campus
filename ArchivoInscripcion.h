#pragma once
#include "Inscripcion.h"
#include <cstdio>
#include <cstring>

class ArchivoInscripcion {
private:
    char _nombre[30];
    int _tamanioRegistro;
public:
    ArchivoInscripcion(const char *nombre = "Inscripciones.dat");

    int agregarRegistro(Inscripcion reg);
    bool listarRegistros();
    int buscarRegistro(int id);
    Inscripcion leerRegistro(int pos);
    bool modificarRegistro(Inscripcion reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
