#pragma once
#include "Comision.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoComision {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoComision(const char *nombre = "Comisiones.dat");

    int agregarRegistro(Comision reg);
    bool listarRegistros();
    int buscarRegistro(int idComision);
    Comision leerRegistro(int pos);
    bool modificarRegistro(Comision reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
