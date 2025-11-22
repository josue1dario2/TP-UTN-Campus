#include "ArchivoInscripcionComision.h"
#include <iostream>
using namespace std;

ArchivoInscripcionComision::ArchivoInscripcionComision(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(InscripcionComision);
}

int ArchivoInscripcionComision::agregarRegistro(InscripcionComision reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return 0;

    int ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);

    return ok;
}

bool ArchivoInscripcionComision::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    InscripcionComision reg;
    int i = 0;

    while (fread(&reg, _tamanioRegistro, 1, p)) {
        // Mostrar solo ACTIVO (0) y PENDIENTE (1)
        if (reg.getEstado() != 2) {
            cout << ++i << ") ";
            reg.mostrar();
        }
    }

    fclose(p);
    return true;
}

int ArchivoInscripcionComision::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / _tamanioRegistro;

    fclose(p);
    return cantidad;
}

InscripcionComision ArchivoInscripcionComision::leerRegistro(int pos) {
    InscripcionComision reg;

    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return reg;
}

bool ArchivoInscripcionComision::modificarRegistro(const InscripcionComision &reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoInscripcionComision::buscarRegistro(int legajo, int idComision) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    InscripcionComision reg;
    int pos = 0;

    while (fread(&reg, _tamanioRegistro, 1, p)) {

        if (reg.getEstado() != 2 &&
            reg.getLegajoAlumno() == legajo &&
            reg.getIdComision() == idComision)
        {
            fclose(p);
            return pos;
        }

        pos++;
    }

    fclose(p);
    return -2; // no encontrado
}
