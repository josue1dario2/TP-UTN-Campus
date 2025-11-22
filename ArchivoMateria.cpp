#include "ArchivoMateria.h"
#include <iostream>
using namespace std;

ArchivoMateria::ArchivoMateria(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Materia);
}

int ArchivoMateria::agregarRegistro(Materia reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoMateria::listarRegistros() {
    Materia obj;
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

int ArchivoMateria::buscarRegistro(int idMateria) {
    Materia obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (obj.getIdMateria() == idMateria) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}


Materia ArchivoMateria::leerRegistro(int pos) {
    Materia obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * _tamanioRegistro, 0);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoMateria::modificarRegistro(Materia reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, 0);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoMateria::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / _tamanioRegistro;
    fclose(p);
    return cant;
}

bool ArchivoMateria::bajaLogica(int pos) {
    Materia reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoMateria::activarRegistro(int pos) {
    Materia reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
