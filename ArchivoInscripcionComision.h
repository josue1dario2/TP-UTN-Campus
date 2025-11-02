#pragma once
#include "InscripcionComision.h"
#include <cstdio>
#include <cstring>

class ArchivoInscripcionComision {
private:
    char _nombre[30];
    int _tamanioRegistro;

public:
    ArchivoInscripcionComision(const char *nombre = "InscripcionesComision.dat");
    int agregarRegistro(InscripcionComision reg);
    bool listarRegistros();
    int contarRegistros();
    InscripcionComision leerRegistro(int pos);
    bool bajaLogica(int pos);
};
