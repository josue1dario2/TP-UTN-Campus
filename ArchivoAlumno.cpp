#include "ArchivoAlumno.h"
#include <cstring>
#include <iostream>
using namespace std;

ArchivoAlumno::ArchivoAlumno(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Alumno);
}

bool ArchivoAlumno::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        // Si es solo lectura y el archivo no existe aún, lo consideramos vacío sin error
        if (strcmp(modo, "rb") == 0) return false;
        if (strcmp(modo, "rb+") == 0) {
            cout << "ERROR: no se pudo abrir el archivo " << _nombre << endl;
        } else if (strcmp(modo, "ab") == 0) {
            // ab debería crear el archivo; si falla es un error real
            cout << "ERROR: no se pudo crear/abrir el archivo " << _nombre << endl;
        }
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

bool ArchivoAlumno::actualizarRegistro(int pos, const Alumno& reg) {
    return modificarRegistro(reg, pos);
}

bool ArchivoAlumno::listarRegistros(bool incluirBorrados) {
    Alumno obj;
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    while (fread(&obj, _tamanioRegistro, 1, p) == 1) {

        // Si NO quiero incluir borrados Y el registro está eliminado → lo salto
        if (!incluirBorrados && obj.getEliminado()) continue;

        obj.mostrar();
        cout << endl;
    }

    fclose(p);
    return true;
}

int ArchivoAlumno::buscarRegistroPorDni(int dni) {
    Alumno obj;
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -2; // archivo inexistente -> no encontrado
    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (!obj.getEliminado() && obj.getDni() == dni) {
            fclose(p);
            return i;
        }
    }
    fclose(p);
    return -2;
}

int ArchivoAlumno::buscarRegistro(int legajo) {
    Alumno obj;
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -2; // archivo inexistente -> no encontrado
    int cant = contarRegistros();
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
    FILE *p;
    if (!abrirArchivo(p, "rb")) return obj;

    fseek(p, pos * _tamanioRegistro, 0);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoAlumno::modificarRegistro(Alumno reg, int pos) {

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, 0);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return ok;
}

int ArchivoAlumno::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0; // si no existe todavía, cantidad = 0
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
