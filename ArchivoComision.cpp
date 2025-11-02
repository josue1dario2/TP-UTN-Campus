#include "ArchivoComision.h"

ArchivoComision::ArchivoComision(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Comision);
}

int ArchivoComision::agregarRegistro(const Comision& reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int result = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return result;
}

bool ArchivoComision::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Comision reg;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (!reg.getEliminado()) {
            reg.mostrar();
        }
    }
    fclose(p);
    return true;
}

int ArchivoComision::buscarRegistro(int idComision) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    Comision reg;
    int pos = 0;
    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (reg.getIdComision() == idComision) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

Comision ArchivoComision::leerRegistro(int pos) {
    Comision reg;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ArchivoComision::modificarRegistro(const Comision& reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

int ArchivoComision::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / _tamanioRegistro;
}

bool ArchivoComision::bajaLogica(int pos) {
    Comision reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoComision::activarRegistro(int pos) {
    Comision reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
