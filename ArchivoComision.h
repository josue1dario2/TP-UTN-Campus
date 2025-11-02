#pragma once
#include "Comision.h"
#include <cstdio>
#include <cstring>

class ArchivoComision {
private:
    char _nombre[30];
    int _tamanioRegistro;
public:
    ArchivoComision(const char *nombre = "Comisiones.dat");

    int agregarRegistro(const Comision& reg);
    bool listarRegistros();
    int buscarRegistro(int id);
    Comision leerRegistro(int pos);
    bool modificarRegistro(const Comision& reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
