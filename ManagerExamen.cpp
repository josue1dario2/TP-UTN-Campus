#include "ManagerExamen.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

ManagerExamen::ManagerExamen() : _archivoExamen("Examenes.dat") {}

// ----------------------------------------------------------
// ALTAS
// ----------------------------------------------------------
void ManagerExamen::cargarParcial(int legajoAlumno, int idComision, int nota) {
    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idComision, legajoAlumno, "Parcial", hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nParcial registrado correctamente.\n";
    else
        cout << "\nError al registrar el parcial.\n";
}

void ManagerExamen::cargarRecuperatorio(int legajoAlumno, int idComision, int nota) {
    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idComision, legajoAlumno, "Recuperatorio", hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nRecuperatorio registrado correctamente.\n";
    else
        cout << "\nError al registrar el recuperatorio.\n";
}

void ManagerExamen::cargarFinal(int legajoAlumno, int idComision, int nota) {
    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idComision, legajoAlumno, "Final", hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nFinal registrado correctamente.\n";
    else
        cout << "\nError al registrar el final.\n";
}

// ----------------------------------------------------------
// CONSULTAS
// ----------------------------------------------------------
bool ManagerExamen::puedeRendirFinal(int legajoAlumno, int idComision) {
    int total = _archivoExamen.contarRegistros();
    int aprobados = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idComision &&
            strcmp(ex.getTipo(), "Parcial") == 0 &&
            ex.getNota() >= 4) {

            aprobados++;
        }
    }

    return aprobados >= 2;
}

bool ManagerExamen::estaPromocionado(int legajoAlumno, int idComision) {
    int total = _archivoExamen.contarRegistros();
    int suma = 0, cantidad = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idComision) {

            if ((strcmp(ex.getTipo(), "Parcial") == 0 ||
                 strcmp(ex.getTipo(), "Recuperatorio") == 0)) {

                suma += ex.getNota();
                cantidad++;
            }
        }
    }

    if (cantidad == 0) return false;

    float promedio = (float)suma / cantidad;
    return promedio >= 7;
}

bool ManagerExamen::estaRegular(int legajoAlumno, int idComision) {
    return puedeRendirFinal(legajoAlumno, idComision) &&
           !estaPromocionado(legajoAlumno, idComision);
}

bool ManagerExamen::estaLibre(int legajoAlumno, int idComision) {
    return !puedeRendirFinal(legajoAlumno, idComision);
}

// ----------------------------------------------------------
// REPORTES
// ----------------------------------------------------------
void ManagerExamen::mostrarTodos() {
    int total = _archivoExamen.contarRegistros();
    if (total == 0) {
        cout << "No hay exámenes registrados.\n";
        return;
    }

    cout << "\n\t=== LISTADO GENERAL DE EXÁMENES ===\n";

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (!ex.getEliminado()) {
            ex.mostrar();
            cout << "\n";
        }
    }
}

void ManagerExamen::mostrarHistorial(int legajoAlumno) {
    int total = _archivoExamen.contarRegistros();
    bool encontrado = false;

    cout << "\n\t=== HISTORIAL DE EXÁMENES ===\n";

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno && !ex.getEliminado()) {
            ex.mostrar();
            cout << "\n";
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No hay exámenes registrados.\n";
}

void ManagerExamen::recalcularCondicion(int legajoAlumno, int idComision) {
    cout << "\nRecalculando condición académica...\n";

    if (estaPromocionado(legajoAlumno, idComision))
        cout << "Condición: PROMOCIONADO\n";
    else if (estaRegular(legajoAlumno, idComision))
        cout << "Condición: REGULAR\n";
    else
        cout << "Condición: LIBRE\n";
}
