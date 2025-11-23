#include "ArchivoExamen.h"
#include <iostream>
using namespace std;

ArchivoExamen::ArchivoExamen(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Examen);
}

int ArchivoExamen::agregarRegistro(Examen reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoExamen::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Examen reg;
    bool hay = false;

    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "------------------------" << endl;
            hay = true;
        }
    }

    if (!hay) cout << "No hay exámenes activos.\n";

    fclose(p);
    return true;
}

int ArchivoExamen::buscarRegistro(int id) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int total = contarRegistros();
    Examen reg;

    for (int i = 0; i < total; i++) {

        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado() && reg.getIdExamen() == id) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Examen ArchivoExamen::leerRegistro(int pos) {
    Examen reg;
    if (pos < 0 || pos >= contarRegistros()) return reg;

    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return reg;
}

bool ArchivoExamen::modificarRegistro(Examen reg, int pos) {
    if (pos < 0 || pos >= contarRegistros()) return false;

    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return escribio;
}

int ArchivoExamen::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);

    return bytes / _tamanioRegistro;
}

bool ArchivoExamen::bajaLogica(int pos) {
    Examen reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoExamen::activarRegistro(int pos) {
    Examen reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}

bool ArchivoExamen::inscribirExamen(Examen& examen) {
    examen.inscribir();
    return agregarRegistro(examen) == 1;
}

bool ArchivoExamen::corregirExamen(int idExamen, int nota) {
    if (nota < 0 || nota > 10) return false;

    int pos = buscarRegistro(idExamen);
    if (pos < 0) return false;

    Examen reg = leerRegistro(pos);
    reg.corregir(nota);

    return modificarRegistro(reg, pos);
}
