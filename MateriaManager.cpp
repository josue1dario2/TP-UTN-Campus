#include "MateriaManager.h"
#include <iostream>
using namespace std;

void MateriaManager::alta() {
    Materia reg;
    reg.cargar();

    reg.setIdMateria(generarIdNuevo());
    reg.setEliminado(false);

    if (_archivo.agregarRegistro(reg) == 1) {
        cout << "Materia guardada con éxito.\n";
    } else {
        cout << "Error al guardar la materia.\n";
    }
}

void MateriaManager::baja() {
    int id;
    cout << "Ingrese el ID de la materia a eliminar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    if (_archivo.bajaLogica(pos)) {
        cout << "Materia dada de baja correctamente.\n";
    } else {
        cout << "No se pudo eliminar.\n";
    }
}

void MateriaManager::modificacion() {
    int id;
    cout << "Ingrese el ID de la materia a modificar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    Materia reg = _archivo.leerRegistro(pos);
    cout << "\nDatos actuales:\n";
    reg.mostrar();

    cout << "\nIngrese los nuevos datos:\n";
    reg.cargar();

    if (_archivo.modificarRegistro(reg, pos)) {
        cout << "Registro modificado correctamente.\n";
    } else {
        cout << "Error al modificar.\n";
    }
}

void MateriaManager::listarTodas() {
    int cantidad = _archivo.contarRegistros();
    if (cantidad == 0) {
        cout << "No hay materias registradas.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        Materia reg = _archivo.leerRegistro(i);
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "-------------------------------\n";
        }
    }
}

int MateriaManager::buscarPorId(int idMateria) {
    return _archivo.buscarRegistro(idMateria);
}

int MateriaManager::generarIdNuevo() {
    return _archivo.contarRegistros() + 1;
}