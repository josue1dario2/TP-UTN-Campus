#pragma once
#include "Correlativa.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class ArchivoCorrelativa {
private:
    char _nombre[30];
    int _tamanioRegistro;

    bool abrirArchivo(FILE *&p, const char *modo);

public:
    ArchivoCorrelativa(const char *nombre = "Correlativas.dat");

    int agregarRegistro(Correlativa reg);
    bool listarRegistros();

    void listarDeMateria(int idMateriaObjetivo);
    int buscarPosDeMateria(int idMateriaObjetivo, int idRequisito);

    int buscarPorMateriaObjetivo(int idMateriaObjetivo);
    int buscarPorMateriaRequisito(int idMateriaRequisito);

    Correlativa leerRegistro(int pos);
    bool modificarRegistro(Correlativa reg, int pos);

    int contarRegistros();
    bool bajaLogica(int pos);
    bool activarRegistro(int pos);
};
