#include "ArchivoPersona.h"
#include <iostream>
using namespace std;

ArchivoPersona::ArchivoPersona(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Persona);
}

int ArchivoPersona::agregarRegistro(Persona reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escrito = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escrito;
}

bool ArchivoPersona::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Persona reg;
    while (fread(&reg, _tamanioRegistro, 1, p) == 1) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "----------------------" << endl;
        }
    }

    fclose(p);
    return true;
}

int ArchivoPersona::buscarRegistro(int dni) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    Persona reg;
    int cant = contarRegistros();

    for (int i = 0; i < cant; i++) {

        // ✔ Corrección IMPORTANTE: usar fseek para posiciones exactas
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado() && reg.getDni() == dni) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2; // no encontrado
}

Persona ArchivoPersona::leerRegistro(int pos) {
    Persona reg;

    // ✔ Validación de límites
    if (pos < 0 || pos >= contarRegistros())
        return reg;

    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return reg;
}

bool ArchivoPersona::modificarRegistro(Persona reg, int pos) {

    // ✔ Validación de límites
    if (pos < 0 || pos >= contarRegistros())
        return false;

    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoPersona::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

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
