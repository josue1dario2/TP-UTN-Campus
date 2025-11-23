#pragma once
#include "Examen.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoExamen {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoExamen(const char *nombre = "Examenes.dat");

    int agregarRegistro(Examen reg);
    bool listarRegistros();
    int buscarRegistro(int idExamen);
    Examen leerRegistro(int pos);
    bool modificarRegistro(Examen reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);

    // Funciones de negocio
    bool inscribirExamen(Examen &examen);
    bool corregirExamen(int idExamen, int nota);
};
