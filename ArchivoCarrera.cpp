#include "ArchivoCarrera.h"
#include <iostream>
using namespace std;

ArchivoCarrera::ArchivoCarrera(const char *n) {
    strcpy(_nombre, n);
    _tamanioRegistro = sizeof(Carrera);
}

int ArchivoCarrera::agregarRegistro(Carrera reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCarrera::listarRegistros() {
    Carrera obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    while (fread(&obj, _tamanioRegistro, 1, p) == 1) {
        if (!obj.getEliminado()) {
            obj.mostrar();

        }

    }
    cout << endl;

    fclose(p);
    return true;
}

int ArchivoCarrera::buscarRegistro(int idCarrera) {
    Carrera obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int cant = contarRegistros();
    for (int i = 0; i < cant; i++) {
        fread(&obj, _tamanioRegistro, 1, p);
        if (!obj.getEliminado() && obj.getIdCarrera() == idCarrera) {
            fclose(p);
            return i; // posición del registro encontrado
        }
    }

    fclose(p);
    return -2; // no encontrado
}

Carrera ArchivoCarrera::leerRegistro(int pos) {
    Carrera obj;
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * _tamanioRegistro, 0);
    fread(&obj, _tamanioRegistro, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoCarrera::modificarRegistro(Carrera reg, int pos) {
    FILE *pCarrera;
    pCarrera=fopen(_nombre,"rb+");
    if(pCarrera==nullptr){
        return -1;
    }

    fseek(pCarrera, pos * sizeof reg, 0);
    bool escribio = fwrite(&reg, sizeof reg, 1, pCarrera);
    fclose(pCarrera);
    return escribio;

    /*



    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, 0);
    bool ok = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return ok;
    */
}

int ArchivoCarrera::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

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
int ArchivoCarrera::getNuevoID(){
    if(contarRegistros() == 0){
        return 1;
    }

    return leerRegistro(contarRegistros() - 1).getIdCarrera()+1;


}

int ArchivoCarrera::buscarPosicion(int idCarrera){
    FILE *pCarrera;
    int pos=0;
    Carrera _carrera;
    pCarrera=fopen(_nombre, "rb"); ///"rb" sirve solo para leer
    if(pCarrera==nullptr) return -1;

    while(fread(&_carrera, sizeof _carrera, 1, pCarrera)==1){
        if(_carrera.getIdCarrera()==idCarrera){
            fclose(pCarrera);
            return pos;
        }
        pos++;
    }

    fclose(pCarrera);
    return -2;
}

