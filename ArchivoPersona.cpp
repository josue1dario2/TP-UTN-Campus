#include "ArchivoPersona.h"
#include <iostream>
#include <cstring>
using namespace std;

ArchivoPersona::ArchivoPersona(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Persona);
}

bool ArchivoPersona::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        cout << "[ERROR] No se pudo abrir archivo: " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoPersona::agregarRegistro(Persona reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return -1;

    int escrito = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escrito;
}

bool ArchivoPersona::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    int total = contarRegistros();
    Persona reg;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "----------------------" << endl;
        }
    }

    fclose(p);
    return true;
}

int ArchivoPersona::buscarRegistro(int dni) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int total = contarRegistros();
    Persona reg;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado() && reg.getDni() == dni) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Persona ArchivoPersona::leerRegistro(int pos) {
    Persona reg;

    if (pos < 0 || pos >= contarRegistros())
        return reg;

    FILE *p;
    if (!abrirArchivo(p, "rb")) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return reg;
}

bool ArchivoPersona::modificarRegistro(Persona reg, int pos) {
    if (pos < 0 || pos >= contarRegistros())
        return false;

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoPersona::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / _tamanioRegistro;

    fclose(p);
    return cantidad;
}

bool ArchivoPersona::bajaLogica(int pos) {
    Persona reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoPersona::activarRegistro(int pos) {
    Persona reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
