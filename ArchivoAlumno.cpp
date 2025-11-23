#include "ArchivoAlumno.h"
#include <iostream>
using namespace std;

ArchivoAlumno::ArchivoAlumno(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Alumno);
}

bool ArchivoAlumno::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        cout << "ERROR: no se pudo abrir el archivo " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoAlumno::agregarRegistro(Alumno reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}

bool ArchivoAlumno::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    Alumno obj;
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
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int cant = contarRegistros();
    Alumno obj;

    for (int i = 0; i < cant; i++) {
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

int ArchivoAlumno::buscarPosicion(int legajo) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int cant = contarRegistros();
    Alumno obj;

    for (int i = 0; i < cant; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);

        if (obj.getLegajo() == legajo) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Alumno ArchivoAlumno::leerRegistro(int pos) {
    Alumno obj;

    if (pos < 0 || pos >= contarRegistros()) return obj;

    FILE *p;
    if (!abrirArchivo(p, "rb")) return obj;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&obj, _tamanioRegistro, 1, p);

    fclose(p);
    return obj;
}

bool ArchivoAlumno::modificarRegistro(Alumno reg, int pos) {
    if (pos < 0) return false;

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return ok;
}

int ArchivoAlumno::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

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
