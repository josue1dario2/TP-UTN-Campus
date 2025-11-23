#pragma once
#include "Alumno.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoAlumno {
private:
    char _nombre[64];
    int _tamanioRegistro;

public:
    ArchivoAlumno(const char *nombre = "Alumnos.dat");

    int agregarRegistro(Alumno reg);
    bool listarRegistros(bool incluirBorrados= false);
    int buscarRegistro(int legajo);
    Alumno leerRegistro(int pos);
    bool modificarRegistro(Alumno reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);

    int buscarRegistroPorDni(int dni);
    bool actualizarRegistro(int pos, const Alumno& reg);
};
