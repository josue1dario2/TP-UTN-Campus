#include "ArchivoMateria.h"
#include <iostream>
using namespace std;

ArchivoMateria::ArchivoMateria(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Materia);
}

int ArchivoMateria::agregarRegistro(Materia reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoMateria::listarRegistros() {
    Materia obj;
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
int ArchivoMateria::buscarPosicion(int idMateria)
{
    FILE *pMateria;
    int pos=0;
    Materia _materia;
    pMateria=fopen(_nombre, "rb"); ///"rb" sirve solo para leer
    if(pMateria==nullptr) return -1;

    while(fread(&_materia, sizeof _materia, 1, pMateria)==1){
        if(_materia.getIdMateria()==idMateria){
            fclose(pMateria);
            return pos;
        }
        pos++;
    }

    fclose(pMateria);
    return -2;

}

int ArchivoMateria::buscarRegistro(const int idMateria) {
    Materia obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (obj.getIdMateria() == idMateria) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

int ArchivoMateria::buscarRegistro(const int idCarrera, const std::string& nombreMateria,const bool cargar) {
    Materia obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

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



/*
bool ArchivoMateria::existeNombreMateria(std::string nombre){
    ArchivoMateria _archivoMatiera;
    int cantidregistros = contarRegistros();
    for (int i=0)
}*/

Materia ArchivoMateria::leerRegistro(int pos) {
    Materia obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * _tamanioRegistro, 0);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoMateria::modificarRegistro(Materia reg, int pos) {
    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, 0);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoMateria::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

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
