#include "ManagerExamen.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// ----------------------------------------------------------
// CONSTRUCTOR
// ----------------------------------------------------------
ManagerExamen::ManagerExamen() : _archivoExamen("Examenes.dat") {}


// ----------------------------------------------------------
// ALTAS DE EXÁMENES
// ----------------------------------------------------------

void ManagerExamen::cargarParcial(int legajoAlumno, int idMateria, int nota) {
    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idMateria, legajoAlumno, "Parcial", hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nParcial registrado correctamente.\n";
    else
        cout << "\nError al registrar el parcial.\n";
}

void ManagerExamen::cargarRecuperatorio(int legajoAlumno, int idMateria, int nota) {
    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idMateria, legajoAlumno, "Recuperatorio", hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nRecuperatorio registrado correctamente.\n";
    else
        cout << "\nError al registrar el recuperatorio.\n";
}

void ManagerExamen::cargarFinal(int legajoAlumno, int idMateria, int nota) {
    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idMateria, legajoAlumno, "Final", hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nFinal registrado correctamente.\n";
    else
        cout << "\nError al registrar el final.\n";
}


// ----------------------------------------------------------
// CONSULTAS ACADÉMICAS
// ----------------------------------------------------------

bool ManagerExamen::puedeRendirFinal(int legajoAlumno, int idMateria) {
    int total = _archivoExamen.contarRegistros();
    int aprobados = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Parcial") == 0 &&
            ex.getNota() >= 4) {
            aprobados++;
        }
    }

    return aprobados >= 2;
}

bool ManagerExamen::estaPromocionado(int legajoAlumno, int idMateria) {
    int total = _archivoExamen.contarRegistros();
    int suma = 0, cantidad = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno && ex.getIdMateria() == idMateria) {
            if ((strcmp(ex.getTipo(), "Parcial") == 0 || strcmp(ex.getTipo(), "Recuperatorio") == 0) && ex.getNota() >= 0) {
                suma += ex.getNota();
                cantidad++;
            }
        }
    }

    if (cantidad == 0) return false;
    float promedio = static_cast<float>(suma) / cantidad;
    return promedio >= 7;
}

bool ManagerExamen::estaRegular(int legajoAlumno, int idMateria) {
    return puedeRendirFinal(legajoAlumno, idMateria) && !estaPromocionado(legajoAlumno, idMateria);
}

bool ManagerExamen::estaLibre(int legajoAlumno, int idMateria) {
    return !puedeRendirFinal(legajoAlumno, idMateria);
}


// ----------------------------------------------------------
// REPORTES
// ----------------------------------------------------------

void ManagerExamen::mostrarHistorial(int legajoAlumno) {
    int total = _archivoExamen.contarRegistros();
    bool encontrado = false;

    cout << "\n\t=== HISTORIAL DE EXÁMENES ===\n";
    cout << "\t+-----------+-----------+--------------+--------+-----------+\n";
    cout << "\t| Legajo    | Materia   | Tipo         | Nota   | Fecha     |\n";
    cout << "\t+-----------+-----------+--------------+--------+-----------+\n";

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno && !ex.getEliminado()) {
            cout << "\t| " << setw(9) << right << ex.getLegajoAlumno()
                 << " | " << setw(9) << right << ex.getIdMateria()
                 << " | " << setw(12) << left << ex.getTipo()
                 << " | " << setw(6) << right << (ex.getCorregido() ? to_string(ex.getNota()) : "-")
                 << " | ";
            ex.getFecha().mostrar();
            cout << " |\n";
            encontrado = true;
        }
    }

    cout << "\t+-----------+-----------+--------------+--------+-----------+\n";

    if (!encontrado)
        cout << "\tNo hay exámenes registrados para este alumno.\n";
}

void ManagerExamen::recalcularCondicion(int legajoAlumno, int idMateria) {
    cout << "\nRecalculando condición académica del alumno " << legajoAlumno << "...\n";

    if (estaPromocionado(legajoAlumno, idMateria))
        cout << "Condición: PROMOCIONADO\n";
    else if (estaRegular(legajoAlumno, idMateria))
        cout << "Condición: REGULAR\n";
    else
        cout << "Condición: LIBRE\n";
}

