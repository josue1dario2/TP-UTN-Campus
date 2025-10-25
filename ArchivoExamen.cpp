#include "ArchivoExamen.h"
#include <iostream>
using namespace std;

ArchivoExamen::ArchivoExamen(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Examen);
}

int ArchivoExamen::agregarRegistro(Examen reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoExamen::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Examen reg;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "------------------------" << endl;
        }
    }
    fclose(p);
    return true;
}

int ArchivoExamen::buscarRegistro(int id) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    Examen reg;
    int pos = 0;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (reg.getIdExamen() == id) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

Examen ArchivoExamen::leerRegistro(int pos) {
    Examen reg;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ArchivoExamen::modificarRegistro(Examen reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoExamen::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / _tamanioRegistro;
}

bool ArchivoExamen::bajaLogica(int pos) {
    Examen reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoExamen::activarRegistro(int pos) {
    Examen reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}

bool ArchivoExamen::inscribirExamen(Examen examen) {
    examen.inscribir();
    return agregarRegistro(examen) == 1;
}

bool ArchivoExamen::corregirExamen(int idExamen, int nota) {
    int pos = buscarRegistro(idExamen);
    if (pos == -1) return false;

    Examen reg = leerRegistro(pos);
    reg.corregir(nota);
    return modificarRegistro(reg, pos);
}