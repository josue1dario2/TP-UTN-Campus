#pragma once
#include "Carrera.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoCarrera {
private:
    char _nombre[30];
    int _tamanioRegistro;
    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoCarrera(const char *nombre = "Carreras.dat");

    int agregarRegistro(Carrera reg);
    bool listarRegistros();
    bool existeCarrera(int idCarrera);
    int buscarRegistro(int idCarrera);
    Carrera leerRegistro(int pos);
    bool modificarRegistro(Carrera reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
    int getNuevoID();
    int buscarPosicion(int idCarrera);
};
