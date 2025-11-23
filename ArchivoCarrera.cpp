#include "ArchivoCarrera.h"
#include <iostream>
using namespace std;

ArchivoCarrera::ArchivoCarrera(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Carrera);
}

bool ArchivoCarrera::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        cout << "ERROR: No se pudo abrir el archivo " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoCarrera::agregarRegistro(Carrera reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCarrera::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    Carrera obj;
    while (fread(&obj, _tamanioRegistro, 1, p) == 1) {
        if (!obj.getEliminado()) {
            obj.mostrar();
            cout << endl;
        }
    }

    fclose(p);
    return true;
}

int ArchivoCarrera::buscarRegistro(int idCarrera) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int cant = contarRegistros();
    Carrera obj;

    for (int i = 0; i < cant; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);

        if (!obj.getEliminado() && obj.getIdCarrera() == idCarrera) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

int ArchivoCarrera::buscarPosicion(int idCarrera) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int cant = contarRegistros();
    Carrera obj;

    for (int i = 0; i < cant; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);

        if (obj.getIdCarrera() == idCarrera) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Carrera ArchivoCarrera::leerRegistro(int pos) {
    Carrera obj;
    FILE *p;
    if (!abrirArchivo(p, "rb")) return obj;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);

    return obj;
}

bool ArchivoCarrera::modificarRegistro(Carrera reg, int pos) {
    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);

    return ok;
}

int ArchivoCarrera::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / _tamanioRegistro;
    fclose(p);

    return cant;
}

bool ArchivoCarrera::bajaLogica(int pos) {
    Carrera reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoCarrera::activarRegistro(int pos) {
    Carrera reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}

int ArchivoCarrera::getNuevoID() {
    int cant = contarRegistros();
    int maxID = 0;

    for (int i = 0; i < cant; i++) {
        Carrera c = leerRegistro(i);
        if (!c.getEliminado() && c.getIdCarrera() > maxID) {
            maxID = c.getIdCarrera();
        }
    }

    return maxID + 1;
}
