#pragma once
#include "Examen.h"
#include <cstdio>
#include <cstring>

class ArchivoExamen {
private:
    char _nombre[30];
    int _tamanioRegistro;
public:
    ArchivoExamen(const char *nombre = "Examenes.dat");

    int agregarRegistro(Examen reg);
    bool listarRegistros();
    int buscarRegistro(int id);
    Examen leerRegistro(int pos);
    bool modificarRegistro(Examen reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
    bool inscribirExamen(Examen& examen);
    bool corregirExamen(int idExamen, int nota);
};
