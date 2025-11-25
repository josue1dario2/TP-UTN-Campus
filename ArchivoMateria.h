#pragma once
#include "Materia.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoMateria {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoMateria(const char *nombre = "Materias.dat");

    int agregarRegistro(Materia reg);
    bool listarRegistros();

    //int buscarRegistro(int idMateria);
    int buscarRegistro(const int idMateria);
    int buscarRegistro(const int idCarrera, const std::string& nombreMateria, const bool cargar=false);


    Materia leerRegistro(int pos);
    bool modificarRegistro(Materia reg, int pos);
    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
