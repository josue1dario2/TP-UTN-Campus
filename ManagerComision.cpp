#include "ManagerComision.h"
#include <iostream>
#include <iomanip>
using namespace std;

ManagerComision::ManagerComision() : _archivo("Comisiones.dat") {}

// ----------------------------------------------------
// AUXILIARES DE PRESENTACIÓN
// ----------------------------------------------------
void ManagerComision::mostrarEncabezado() {
    cout << "\t+------------+------------+------------+------------+------------+------------+\n";
    cout << "\t| IDComision | IDMateria  | Turno      | Modalidad  | Año        | Eliminado  |\n";
    cout << "\t+------------+------------+------------+------------+------------+------------+\n";
}

void ManagerComision::mostrarRegistro(const Comision& c) {
    cout << "\t| " << setw(10) << right << c.getIdComision()
         << " | " << setw(10) << right << c.getIdMateria()
         << " | " << setw(10) << left  << c.getTurno()
         << " | " << setw(10) << left  << c.getModalidad()
         << " | " << setw(10) << right << c.getAnio()
         << " | " << setw(10) << right << (c.getEliminado() ? "Sí" : "No")
         << " |\n";
}

void ManagerComision::mostrarPie() {
    cout << "\t+------------+------------+------------+------------+------------+------------+\n";
}

// ----------------------------------------------------
// INGRESO DE DATOS
// ----------------------------------------------------
Comision ManagerComision::ingresarDatos(int idComision) {
    int idMateria = Validacion::validarEnteroEnRango("\tID Materia: ", 1, 9999);

    string turno;
    cout << "\tTurno (Mañana / Tarde / Noche): ";
    getline(cin >> ws, turno);

    string modalidad;
    cout << "\tModalidad (Presencial / Virtual / Híbrida): ";
    getline(cin >> ws, modalidad);

    int cuatrimestre = Validacion::validarEnteroEnRango("\tCuatrimestre (1-2): ", 1, 2);
    int anio = Validacion::validarEnteroEnRango("\tAño (2020-2030): ", 2020, 2030);
    int legajoDocente = Validacion::validarEnteroEnRango("\tLegajo Docente: ", 1, 99999);

    return Comision(idComision, idMateria, turno.c_str(), modalidad.c_str(),
                    cuatrimestre, anio, legajoDocente, false);
}

// ----------------------------------------------------
// CRUD
// ----------------------------------------------------

void ManagerComision::cargar() {
    cout << "\n\t=== Cargar Nueva Comisión ===\n";

    int nuevoID = _archivo.contarRegistros() + 1;
    Comision nueva = ingresarDatos(nuevoID);

    if (_archivo.agregarRegistro(nueva))
        cout << "\n\tComisión agregada correctamente.\n";
    else
        cout << "\n\tError al agregar la comisión.\n";
}

void ManagerComision::listar() {
    cout << "\n\t=== LISTADO DE COMISIONES ===\n";
    int total = _archivo.contarRegistros();
    if (total == 0) {
        cout << "\n\tNo hay comisiones registradas.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado()) {
            mostrarRegistro(c);
        }
    }
    mostrarPie();
}

void ManagerComision::modificar() {
    cout << "\n\t=== MODIFICAR COMISIÓN ===\n";
    int id = Validacion::validarEnteroEnRango("\tIngrese ID de comisión a modificar: ", 1, 99999);

    int pos = _archivo.buscarRegistro(id);
    if (pos < 0) {
        cout << "\tNo se encontró la comisión.\n";
        return;
    }

    Comision original = _archivo.leerRegistro(pos);
    cout << "\n\tDatos actuales:\n";
    original.mostrar();

    Comision modificada = ingresarDatos(original.getIdComision());

    cout << "\n\t¿Desea guardar los cambios? (s/n): ";
    char op;
    cin >> op;
    if (op == 's' || op == 'S') {
        if (_archivo.modificarRegistro(modificada, pos))
            cout << "\tComisión modificada correctamente.\n";
        else
            cout << "\tError al modificar la comisión.\n";
    } else {
        cout << "\tOperación cancelada.\n";
    }
}

void ManagerComision::borrar() {
    cout << "\n\t=== BAJA LÓGICA DE COMISIÓN ===\n";
    int id = Validacion::validarEnteroEnRango("\tIngrese ID de comisión: ", 1, 99999);

    int pos = _archivo.buscarRegistro(id);
    if (pos < 0) {
        cout << "\tNo se encontró la comisión.\n";
        return;
    }

    if (_archivo.bajaLogica(pos))
        cout << "\tComisión dada de baja correctamente.\n";
    else
        cout << "\tError al dar de baja la comisión.\n";
}

void ManagerComision::activar() {
    cout << "\n\t=== REACTIVAR COMISIÓN ===\n";
    int id = Validacion::validarEnteroEnRango("\tIngrese ID de comisión: ", 1, 99999);

    int pos = _archivo.buscarRegistro(id);
    if (pos < 0) {
        cout << "\tNo se encontró la comisión.\n";
        return;
    }

    if (_archivo.activarRegistro(pos))
        cout << "\tComisión reactivada correctamente.\n";
    else
        cout << "\tError al reactivar la comisión.\n";
}

// ----------------------------------------------------
// CONSULTAS
// ----------------------------------------------------
void ManagerComision::mostrarTodasLasComisiones() {
    listar();
}

void ManagerComision::mostrarComisionesPorMateria(int idMateria) {
    int total = _archivo.contarRegistros();
    bool encontrado = false;

    cout << "\n\t=== COMISIONES DE LA MATERIA " << idMateria << " ===\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateria() == idMateria) {
            mostrarRegistro(c);
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "\tNo hay comisiones registradas para esta materia.\n";

    mostrarPie();
}
