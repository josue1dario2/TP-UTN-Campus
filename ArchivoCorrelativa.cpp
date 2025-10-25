#include "ArchivoCorrelativa.h"
#include <iostream>
using namespace std;

ArchivoCorrelativa::ArchivoCorrelativa(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Correlativa);
}

int ArchivoCorrelativa::agregarRegistro(Correlativa reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCorrelativa::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Correlativa reg;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "------------------------" << endl;
        }
    }
    fclose(p);
    return true;
}

int ArchivoCorrelativa::buscarRegistro(int id) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    Correlativa reg;
    int pos = 0;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (reg.getIdCorrelativa() == id) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

Correlativa ArchivoCorrelativa::leerRegistro(int pos) {
    Correlativa reg;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ArchivoCorrelativa::modificarRegistro(Correlativa reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCorrelativa::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / _tamanioRegistro;
}

bool ArchivoCorrelativa::bajaLogica(int pos) {
    Correlativa reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoCorrelativa::activarRegistro(int pos) {
    Correlativa reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
