#pragma once
#include "InscripcionComision.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoInscripcionComision {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoInscripcionComision(const char *nombre = "InscripcionesComision.dat");

    int agregarRegistro(InscripcionComision reg);
    bool listarRegistros();
    int contarRegistros();
    InscripcionComision leerRegistro(int pos);
    int buscarRegistro(int legajo, int idComision);
    bool modificarRegistro(const InscripcionComision &reg, int pos);
};
