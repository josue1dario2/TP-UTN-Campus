#include "ArchivoAlumno.h"
#include <iostream>
using namespace std;

ArchivoAlumno::ArchivoAlumno(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Alumno);
}

int ArchivoAlumno::agregarRegistro(Alumno reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;
    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoAlumno::listarRegistros() {
    Alumno obj;
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

int ArchivoAlumno::buscarRegistro(int legajo) {
    Alumno obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (!obj.getEliminado() && obj.getLegajo() == legajo) {
            fclose(p);
            return i; // posición del registro encontrado
        }
    }

    fclose(p);
    return -2; // no encontrado
}

Alumno ArchivoAlumno::leerRegistro(int pos) {
    Alumno obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * _tamanioRegistro, 0);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoAlumno::modificarRegistro(Alumno reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, 0);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

int ArchivoAlumno::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / _tamanioRegistro;
    fclose(p);
    return cant;
}

bool ArchivoAlumno::bajaLogica(int pos) {
    Alumno reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoAlumno::activarRegistro(int pos) {
    Alumno reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
