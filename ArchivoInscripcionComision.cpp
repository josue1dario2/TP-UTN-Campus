#include "ArchivoInscripcionComision.h"
#include <iostream>
#include <cstring>
using namespace std;

ArchivoInscripcionComision::ArchivoInscripcionComision(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(InscripcionComision);
}

bool ArchivoInscripcionComision::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        //cout << "[ERROR] No se pudo abrir archivo: " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoInscripcionComision::agregarRegistro(InscripcionComision reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return 0;

    int ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

bool ArchivoInscripcionComision::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    InscripcionComision reg;
    int num = 0;
    int total = contarRegistros();

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (reg.getEstado() != 2) {  // 0=Activo, 1=Pendiente, 2=Cancelado
            cout << ++num << ") ";
            reg.mostrar();
        }
    }

    fclose(p);
    return true;
}

int ArchivoInscripcionComision::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / _tamanioRegistro;

    fclose(p);
    return cantidad;
}

InscripcionComision ArchivoInscripcionComision::leerRegistro(int pos) {
    InscripcionComision reg;

    if (pos < 0 || pos >= contarRegistros())
        return reg;

    FILE *p;
    if (!abrirArchivo(p, "rb")) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return reg;
}

bool ArchivoInscripcionComision::modificarRegistro(const InscripcionComision &reg, int pos) {
    if (pos < 0 || pos >= contarRegistros())
        return false;

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoInscripcionComision::buscarRegistro(int legajo, int idComision) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int total = contarRegistros();
    InscripcionComision reg;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (reg.getEstado() != 2 &&
            reg.getLegajoAlumno() == legajo &&
            reg.getIdComision() == idComision) {

            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2; // no encontrado
}
