#include "ArchivoDocente.h"
#include <iostream>
#include <cstring>
using namespace std;

ArchivoDocente::ArchivoDocente(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Docente);
}

bool ArchivoDocente::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        //cout << "[ERROR] No se pudo abrir archivo: " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoDocente::agregarRegistro(Docente reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}

bool ArchivoDocente::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    Docente obj;
    bool hay = false;

    while (fread(&obj, _tamanioRegistro, 1, p)) {
        if (!obj.getEliminado()) {
            obj.mostrar();
            cout << "----------------------\n";
            hay = true;
        }
    }

    if (!hay)
        cout << "No hay docentes activos.\n";

    fclose(p);
    return true;
}

int ArchivoDocente::buscarRegistro(int legajo) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int total = contarRegistros();
    Docente obj;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);

        if (!obj.getEliminado() && obj.getLegajo() == legajo) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Docente ArchivoDocente::leerRegistro(int pos) {
    Docente obj;

    if (pos < 0 || pos >= contarRegistros())
        return obj;

    FILE *p;
    if (!abrirArchivo(p, "rb")) return obj;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&obj, _tamanioRegistro, 1, p);

    fclose(p);
    return obj;
}

bool ArchivoDocente::modificarRegistro(Docente reg, int pos) {
    if (pos < 0 || pos >= contarRegistros())
        return false;

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoDocente::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

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
