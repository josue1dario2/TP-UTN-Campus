#include "ManagerExamen.h"
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

// ----------------------------------------------------------
// CONSTRUCTOR
// ----------------------------------------------------------
ManagerExamen::ManagerExamen() : _archivoExamen("Examenes.dat") {}


// ----------------------------------------------------------
// MÉTODOS AUXILIARES DE BÚSQUEDA Y VALIDACIÓN
// ----------------------------------------------------------

// Verifica si el alumno ya usó un recuperatorio para un parcial específico
bool ManagerExamen::_yaUsoRecuperatorio(int legajoAlumno, int idComision, int numeroParcial) {
    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {
        Examen reg = _archivoExamen.leerRegistro(i);
        if (reg.getLegajoAlumno() == legajoAlumno &&
            reg.getIdComision() == idComision &&
            strcmp(reg.getTipo(), "Recuperatorio") == 0 &&
            reg.getNumero() == numeroParcial &&
            !reg.getEliminado()) {
            return true;
        }
    }
    return false;
}

// Verifica si ya existe un examen de cierto tipo
bool ManagerExamen::_existeExamen(int legajoAlumno, int idComision, const char* tipo, int numero) {
    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {
        Examen reg = _archivoExamen.leerRegistro(i);
        if (reg.getLegajoAlumno() == legajoAlumno &&
            reg.getIdComision() == idComision &&
            strcmp(reg.getTipo(), tipo) == 0 &&
            reg.getNumero() == numero &&
            !reg.getEliminado()) {
            return true;
        }
    }
    return false;
}


// ----------------------------------------------------------
// ALTAS DE EXÁMENES
// ----------------------------------------------------------

void ManagerExamen::cargarParcial(int legajoAlumno, int idComision, int numeroParcial, int nota) {
    if (numeroParcial < 1 || numeroParcial > 3) {
        cout << "Número de parcial inválido.\n";
        return;
    }

    if (_existeExamen(legajoAlumno, idComision, "Parcial", numeroParcial)) {
        cout << "El alumno ya tiene registrado ese parcial.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();
    Examen ex(0, idComision, legajoAlumno, "Parcial", numeroParcial, hoy, false);
    ex.corregir(nota);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "Parcial registrado correctamente.\n";
    else
        cout << "Error al registrar el parcial.\n";
}

void ManagerExamen::cargarRecuperatorio(int legajoAlumno, int idComision, int numeroParcial, int nota) {
    if (numeroParcial < 1 || numeroParcial > 3) {
        cout << "Número de parcial inválido.\n";
        return;
    }

    if (_yaUsoRecuperatorio(legajoAlumno, idComision, numeroParcial)) {
        cout << "El alumno ya usó un recuperatorio para este parcial.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();
    Examen ex(0, idComision, legajoAlumno, "Recuperatorio", numeroParcial, hoy, false);
    ex.corregir(nota);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "Recuperatorio registrado correctamente.\n";
    else
        cout << "Error al registrar el recuperatorio.\n";
}

void ManagerExamen::cargarFinal(int legajoAlumno, int idComision, int nota) {
    if (_existeExamen(legajoAlumno, idComision, "Final", 0)) {
        cout << "El alumno ya tiene un examen final registrado.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();
    Examen ex(0, idComision, legajoAlumno, "Final", 0, hoy, false);
    ex.corregir(nota);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "Final registrado correctamente.\n";
    else
        cout << "Error al registrar el final.\n";
}


// ----------------------------------------------------------
// CONSULTAS ACADÉMICAS
// ----------------------------------------------------------

bool ManagerExamen::puedeRendirFinal(int legajoAlumno, int idComision) {
    int total = _archivoExamen.contarRegistros();
    int aprobados = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdComision() == idComision &&
            strcmp(ex.getTipo(), "Parcial") == 0 &&
            ex.getNota() >= 4) {
            aprobados++;
        }
    }
    return aprobados >= 2; // necesita al menos 2 parciales aprobados
}

bool ManagerExamen::estaPromocionado(int legajoAlumno, int idComision) {
    int total = _archivoExamen.contarRegistros();
    int suma = 0, cantidad = 0;
    bool usoRecuperatorio = false;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno && ex.getIdComision() == idComision) {
            if ((strcmp(ex.getTipo(), "Parcial") == 0 || strcmp(ex.getTipo(), "Recuperatorio") == 0) && ex.getNota() >= 0) {
                suma += ex.getNota();
                cantidad++;
                if (strcmp(ex.getTipo(), "Recuperatorio") == 0)
                    usoRecuperatorio = true;
            }
        }
    }

    if (cantidad == 0) return false;
    float promedio = static_cast<float>(suma) / cantidad;
    return promedio >= 7 && !usoRecuperatorio;
}

bool ManagerExamen::estaRegular(int legajoAlumno, int idComision) {
    return puedeRendirFinal(legajoAlumno, idComision) && !estaPromocionado(legajoAlumno, idComision);
}

bool ManagerExamen::estaLibre(int legajoAlumno, int idComision) {
    return !puedeRendirFinal(legajoAlumno, idComision);
}


// ----------------------------------------------------------
// REPORTES
// ----------------------------------------------------------

void ManagerExamen::mostrarHistorial(int legajoAlumno) {
    int total = _archivoExamen.contarRegistros();
    bool encontrado = false;

    cout << "\n\t=== HISTORIAL DE EXÁMENES ===\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno && !ex.getEliminado()) {
            mostrarRegistro(ex);
            encontrado = true;
        }
    }

    mostrarPie();

    if (!encontrado)
        cout << "\tNo hay exámenes registrados para este alumno.\n";
}


void ManagerExamen::recalcularCondicion(int legajoAlumno, int idComision) {
    cout << "\nRecalculando condición académica del alumno " << legajoAlumno << "...\n";

    if (estaPromocionado(legajoAlumno, idComision))
        cout << "Condición: PROMOCIONADO\n";
    else if (estaRegular(legajoAlumno, idComision))
        cout << "Condición: REGULAR\n";
    else
        cout << "Condición: LIBRE\n";
}


// ----------------------------------------------------------
// PRESENTACIÓN TABULAR DE EXÁMENES
// ----------------------------------------------------------

void ManagerExamen::mostrarEncabezado() {
    cout << "\t+-----------+-----------+-------------+---------------+--------+-----------+-----------+\n";
    cout << "\t| Legajo    | Comisión  | Tipo        | Nº Parcial    | Nota   | Fecha     | Eliminado |\n";
    cout << "\t+-----------+-----------+-------------+---------------+--------+-----------+-----------+\n";
}

void ManagerExamen::mostrarRegistro(const Examen& e) {
    cout << "\t| " << setw(9) << right << e.getLegajoAlumno()
         << " | " << setw(9) << right << e.getIdComision()
         << " | " << setw(11) << left  << e.getTipo()
         << " | " << setw(13) << right << e.getNumero()
         << " | " << setw(6)  << right << (e.getCorregido() ? to_string(e.getNota()) : "-")
         << " | ";
    e.getFecha().mostrar();
    cout << " | " << setw(9) << right << (e.getEliminado() ? "Sí" : "No") << " |\n";
}

void ManagerExamen::mostrarPie() {
    cout << "\t+-----------+-----------+-------------+---------------+--------+-----------+-----------+\n";
}
