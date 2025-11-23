#include "ArchivoComision.h"
#include <iostream>
using namespace std;

ArchivoComision::ArchivoComision(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Comision);
}

bool ArchivoComision::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        cout << "[ERROR] No se pudo abrir el archivo: " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoComision::agregarRegistro(Comision reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoComision::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    Comision reg;
    bool hay = false;

    while (fread(&reg, _tamanioRegistro, 1, p) == 1) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "------------------------\n";
            hay = true;
        }
    }

    if (!hay) cout << "No hay comisiones activas.\n";

    fclose(p);
    return true;
}

int ArchivoComision::buscarRegistro(int idComision) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int cant = contarRegistros();
    Comision reg;

    for (int i = 0; i < cant; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado() && reg.getIdComision() == idComision) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Comision ArchivoComision::leerRegistro(int pos) {
    Comision reg;

    if (pos < 0 || pos >= contarRegistros()) return reg;

    FILE *p;
    if (!abrirArchivo(p, "rb")) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return reg;
}

bool ArchivoComision::modificarRegistro(Comision reg, int pos) {
    if (pos < 0) return false;

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return escribio;
}

int ArchivoComision::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / _tamanioRegistro;

    fclose(p);
    return cant;
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
