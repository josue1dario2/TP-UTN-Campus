#include "ArchivoDocente.h"
#include <iostream>
using namespace std;

ArchivoDocente::ArchivoDocente(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Docente);
}

int ArchivoDocente::agregarRegistro(Docente reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoDocente::listarRegistros() {
    Docente obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    while (fread(&obj, _tamanioRegistro, 1, p) == 1) {
        if (!obj.getEliminado()) {
            obj.mostrar();
            cout << endl;
        }
    }

    fclose(p);
    return true;
}

int ArchivoDocente::buscarRegistro(int legajo) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int total = contarRegistros();
    Docente obj;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);

        if (!obj.getEliminado() && obj.getLegajo() == legajo) {
            fclose(p);
            return i; // posición encontrada
        }
    }

    fclose(p);
    return -2; // no encontrado
}

Docente ArchivoDocente::leerRegistro(int pos) {
    Docente obj;
    if (pos < 0 || pos >= contarRegistros()) return obj;

    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&obj, _tamanioRegistro, 1, p);

    fclose(p);
    return obj;
}

bool ArchivoDocente::modificarRegistro(Docente reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoDocente::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / _tamanioRegistro;

    fclose(p);
    return cant;
}

bool ArchivoDocente::bajaLogica(int pos) {
    Docente reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoDocente::activarRegistro(int pos) {
    Docente reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
