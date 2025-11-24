#include "ManagerMateria.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

string quitarAcentos(const char* texto) {
    string t = texto;
    string r;

    for (unsigned char c : t) {
        switch (c) {
            case 0xC3:
                continue;
            case 0xA1: r += "a"; break; // á
            case 0xA9: r += "e"; break; // é
            case 0xAD: r += "i"; break; // í
            case 0xB3: r += "o"; break; // ó
            case 0xBA: r += "u"; break; // ú
            case 0xB1: r += "n"; break; // ñ
            default: r += c; break;
        }
    }
    return r;
}

void ManagerMateria::alta() {
    Materia reg;

    cout << "=== ALTA DE MATERIA ===\n";

    int idCarrera;
    cout << "ID Carrera: ";
    cin >> idCarrera;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char nombre[50];
    cout << "Nombre: ";
    cin.getline(nombre, 50);

    int cuatrimestre;
    cout << "Cuatrimestre: ";
    cin >> cuatrimestre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char estado[20];
    cout << "Estado (Activa / Inactiva): ";
    cin.getline(estado, 20);

    reg.setIdMateria(generarIdNuevo());
    reg.setIdCarrera(idCarrera);
    reg.setNombre(nombre);
    reg.setCuatrimestre(cuatrimestre);
    reg.setEstado(estado);
    reg.setEliminado(false);

    if (_archivo.agregarRegistro(reg) == 1)
        cout << "Materia guardada con éxito.\n";
    else
        cout << "Error al guardar la materia.\n";
}

void ManagerMateria::baja() {
    int id;
    cout << "Ingrese el ID de la materia a eliminar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    if (_archivo.bajaLogica(pos))
        cout << "Materia dada de baja correctamente.\n";
    else
        cout << "No se pudo eliminar.\n";
}

void ManagerMateria::modificacion() {
    int id;
    cout << "Ingrese el ID de la materia a modificar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    Materia reg = _archivo.leerRegistro(pos);

    cout << "\n=== DATOS ACTUALES ===\n";
    reg.mostrar();

    cout << "\n=== INGRESE NUEVOS DATOS ===\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int nuevoIdCarrera;
    cout << "Nuevo ID de Carrera: ";
    cin >> nuevoIdCarrera;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char nombre[50];
    cout << "Nuevo nombre: ";
    cin.getline(nombre, 50);

    int cuatrimestre;
    cout << "Nuevo cuatrimestre: ";
    cin >> cuatrimestre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char estado[20];
    cout << "Nuevo estado: ";
    cin.getline(estado, 20);

    reg.setNombre(nombre);
    reg.setCuatrimestre(cuatrimestre);
    reg.setEstado(estado);
    reg.setIdCarrera(nuevoIdCarrera);

    if (_archivo.modificarRegistro(reg, pos))
        cout << "Registro modificado correctamente.\n";
    else
        cout << "Error al modificar.\n";
}

void ManagerMateria::listarTodas() {
    int cantidad = _archivo.contarRegistros();
    if (cantidad == 0) {
        cout << "No hay materias registradas.\n";
        return;
    }

    cout << "=== LISTADO DE MATERIAS ===\n";

    cout << left << setfill(' ');

    // ------- ENCABEZADO -------
    cout << setw(10) << "Carrera"
         << setw(5)  << "Id"
         << setw(38) << "Nombre"
         << setw(15) << "Cuatrimestre"
         << setw(10) << "Estado"
         << setw(10) << "Eliminado"
         << "\n";

    cout << string(88, '-') << "\n";

    // ------- FILAS -------
    for (int i = 0; i < cantidad; i++) {
        Materia reg = _archivo.leerRegistro(i);

        if (!reg.getEliminado()) {
            cout << setw(10) << reg.getIdCarrera()
                 << setw(5)  << reg.getIdMateria()
                 << setw(38) << quitarAcentos(reg.getNombre())
                 << setw(15) << reg.getCuatrimestre()
                 << setw(10) << reg.getEstado()
                 << setw(10) << (reg.getEliminado() ? "Si" : "No")
                 << "\n";
        }
    }

    cout << string(88, '-') << "\n";
}

int ManagerMateria::buscarPorId(int idMateria) {
    return _archivo.buscarRegistro(idMateria);
}

int ManagerMateria::generarIdNuevo() {
    int cant = _archivo.contarRegistros();
    int maxID = 0;

    for (int i = 0; i < cant; i++) {
        Materia reg = _archivo.leerRegistro(i);
        if (reg.getIdMateria() > maxID)
            maxID = reg.getIdMateria();
    }

    return maxID + 1;
}
