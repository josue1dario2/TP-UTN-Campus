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
    Docente obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -2;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (obj.getLegajo() == legajo) {
            fclose(p);
            return i; // posición del registro encontrado
        }
    }

    fclose(p);
    return -2; // no encontrado
}

int ArchivoDocente::buscarRegistroPorDni(int dni) {
    Docente obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -2;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (obj.getDni() == dni) {
            fclose(p);
            return i; // posición del registro encontrado
        }
    }

    fclose(p);
    return -2; // no encontrado
}




Docente ArchivoDocente::leerRegistro(int pos) {
    Docente obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * _tamanioRegistro, 0);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoDocente::modificarRegistro(Docente reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, 0);
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
