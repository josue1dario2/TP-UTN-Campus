#include "ArchivoCorrelativa.h"
#include <iostream>
using namespace std;

ArchivoCorrelativa::ArchivoCorrelativa(const char *nombre) {
    strcpy(_nombre, nombre);
    _tamanioRegistro = sizeof(Correlativa);
}

int ArchivoCorrelativa::agregarRegistro(Correlativa reg) {
    FILE *p = fopen(_nombre, "ab");
    if (p == nullptr) return -1;

    int escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCorrelativa::listarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return false;

    Correlativa reg;
    bool hay = false;

    while (fread(&reg, _tamanioRegistro, 1, p)) {
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "------------------------" << endl;
            hay = true;
        }
    }

    if (!hay) cout << "No hay correlativas activas.\n";

    fclose(p);
    return true;
}


void ArchivoCorrelativa::listarDeMateria(int idMateriaObjetivo) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) {
        cout << "No se pudo abrir archivo.\n";
        return;
    }

    int total = contarRegistros();
    Correlativa reg;
    bool hay = false;

    cout << "Correlativas de la materia " << idMateriaObjetivo << ":\n";

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado() &&
            reg.getIdMateriaObjetivo() == idMateriaObjetivo) {

            cout << " - Requiere aprobar materia: "
                 << reg.getIdMateriaRequisito() << endl;
            hay = true;
        }
    }

    if (!hay) cout << " (Sin correlativas configuradas)\n";

    fclose(p);
}


int ArchivoCorrelativa::buscarPosDeMateria(int idMateriaObjetivo, int idRequisito) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int total = contarRegistros();
    Correlativa reg;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (!reg.getEliminado() &&
            reg.getIdMateriaObjetivo() == idMateriaObjetivo &&
            reg.getIdMateriaRequisito() == idRequisito) {

            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

int ArchivoCorrelativa::buscarPorMateriaObjetivo(int idMateriaObjetivo) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int total = contarRegistros();
    Correlativa reg;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (reg.getIdMateriaObjetivo() == idMateriaObjetivo) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

int ArchivoCorrelativa::buscarPorMateriaRequisito(int idMateriaRequisito) {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return -1;

    int total = contarRegistros();
    Correlativa reg;

    for (int i = 0; i < total; i++) {
        fseek(p, i * _tamanioRegistro, SEEK_SET);
        fread(&reg, _tamanioRegistro, 1, p);

        if (reg.getIdMateriaRequisito() == idMateriaRequisito) {
            fclose(p);
            return i;
        }
    }

    fclose(p);
    return -2;
}

Correlativa ArchivoCorrelativa::leerRegistro(int pos) {
    Correlativa reg;
    if (pos < 0 || pos >= contarRegistros()) return reg;

    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    fread(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ArchivoCorrelativa::modificarRegistro(Correlativa reg, int pos) {
    if (pos < 0 || pos >= contarRegistros()) return false;

    FILE *p = fopen(_nombre, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * _tamanioRegistro, SEEK_SET);
    bool escribio = fwrite(&reg, _tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCorrelativa::contarRegistros() {
    FILE *p = fopen(_nombre, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / _tamanioRegistro;
}

bool ArchivoCorrelativa::bajaLogica(int pos) {
    Correlativa reg = leerRegistro(pos);
    reg.setEliminado(true);
    return modificarRegistro(reg, pos);
}

bool ArchivoCorrelativa::activarRegistro(int pos) {
    Correlativa reg = leerRegistro(pos);
    reg.setEliminado(false);
    return modificarRegistro(reg, pos);
}
