#include "ArchivoPersona.h"

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
        reg.mostrar();
        std::cout << "----------------------" << std::endl;
    }

    fclose(p);
    return true;
}

int ArchivoPersona::buscarRegistro(int dni) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    Persona reg;
    int pos = 0;

    while (fread(&reg, _tamanioRegistro, 1, p) == 1) {
        if (reg.getDni() == dni) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1; // No encontrado
}

Persona ArchivoPersona::leerRegistro(int pos) {
    Persona reg;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ArchivoPersona::modificarRegistro(Persona reg, int pos) {
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
