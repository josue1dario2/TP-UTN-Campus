#include "ManagerMateria.h"
#include <iostream>
#include <limits>
using namespace std;

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

    for (int i = 0; i < cantidad; i++) {
        Materia reg = _archivo.leerRegistro(i);

        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "-------------------------------\n";
        }
    }
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
