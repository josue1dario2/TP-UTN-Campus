#include "ArchivoMateria.h"
#include <iostream>
#include <cstring>
using namespace std;

ArchivoMateria::ArchivoMateria(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Materia);
}

bool ArchivoMateria::abrirArchivo(FILE *&p, const char *modo) {
    p = fopen(_nombre, modo);
    if (p == nullptr) {
        //cout << "[ERROR] No se pudo abrir archivo: " << _nombre << endl;
        return false;
    }
    return true;
}

int ArchivoMateria::agregarRegistro(Materia reg) {
    FILE *p;
    if (!abrirArchivo(p, "ab")) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoMateria::listarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return false;

    int total = contarRegistros();
    Materia obj;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);


        if (!obj.getEliminado()) {
            obj.mostrar();
            cout << endl;
        }

    }

    fclose(p);
    return true;
}

int ArchivoMateria::buscarRegistro(const int idMateria) {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int total = contarRegistros();
    Materia obj;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&obj, _tamanioRegistro, 1, p);

        if (!obj.getEliminado() && obj.getIdMateria() == idMateria) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2; // no encontrado
}

int ArchivoMateria::buscarRegistro(const int idCarrera, const std::string& nombreMateria,const bool cargar) {
    Materia obj;
    FILE *p;
    if (!abrirArchivo(p, "rb")) return -1;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
            if (nombreMateria == std::string(obj.getNombre())&& (obj.getIdCarrera()==idCarrera)&& (cargar==true)) {
                fclose(p);
                return i;
            }
        }


    fclose(p);
    return -2;
}



Materia ArchivoMateria::leerRegistro(int pos) {
    Materia obj;

    if (pos < 0 || pos >= contarRegistros())
        return obj;

    FILE *p;
    if (!abrirArchivo(p, "rb")) return obj;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&obj, _tamanioRegistro, 1, p);

    fclose(p);
    return obj;
}

bool ArchivoMateria::modificarRegistro(Materia reg, int pos) {
    if (pos < 0 || pos >= contarRegistros())
        return false;

    FILE *p;
    if (!abrirArchivo(p, "rb+")) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);

    fclose(p);
    return escribio;
}

int ArchivoMateria::contarRegistros() {
    FILE *p;
    if (!abrirArchivo(p, "rb")) return 0;

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
