#pragma once
#include "Alumno.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoAlumno {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoAlumno(const char *nombre = "Alumnos.dat");

    int agregarRegistro(Alumno reg);
    bool listarRegistros();
    int buscarRegistro(int legajo);
    Alumno leerRegistro(int pos);
    bool modificarRegistro(Alumno reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
