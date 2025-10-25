#include "ArchivoInscripcion.h"
#include <iostream>
using namespace std;

ArchivoInscripcion::ArchivoInscripcion(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Inscripcion);
}

int ArchivoInscripcion::agregarRegistro(Inscripcion reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoInscripcion::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Inscripcion reg;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "------------------------" << endl;
        }
    }
    fclose(p);
    return true;
}

int ArchivoInscripcion::buscarRegistro(int id) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    Inscripcion reg;
    int pos = 0;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (reg.getIdInscripcion() == id) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

Inscripcion ArchivoInscripcion::leerRegistro(int pos) {
    Inscripcion reg;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ArchivoInscripcion::modificarRegistro(Inscripcion reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoInscripcion::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / _tamanioRegistro;
}

bool ArchivoInscripcion::bajaLogica(int pos) {
    Inscripcion reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoInscripcion::activarRegistro(int pos) {
    Inscripcion reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
