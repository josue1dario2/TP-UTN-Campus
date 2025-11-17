#include "ExamenManager.h"
#include <iostream>
#include <cstring>
using namespace std;

ExamenManager::ExamenManager() : _archivoExamen("Examenes.dat") {}

// Verifica si el alumno ya usó un recuperatorio para un parcial específico
bool ExamenManager::_yaUsoRecuperatorio(int legajoAlumno, int idComision, int numeroParcial) {
    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {
        Examen reg = _archivoExamen.leerRegistro(i);
        if (reg.getLegajoAlumno() == legajoAlumno && reg.getIdComision() == idComision) {
            if (strcmp(reg.getTipo(), "Recuperatorio") == 0 && reg.getNumero() == numeroParcial && !reg.getEliminado()) {
                return true;
            }
        }
    }
    return false;
}

// Verifica si ya existe un examen de cierto tipo
bool ExamenManager::_existeExamen(int legajoAlumno, int idComision, const char* tipo, int numero) {
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

void ExamenManager::cargarParcial(int legajoAlumno, int idComision, int numeroParcial, int nota) {
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

void ExamenManager::cargarRecuperatorio(int legajoAlumno, int idComision, int numeroParcial, int nota) {
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

void ExamenManager::cargarFinal(int legajoAlumno, int idComision, int nota) {
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

bool ExamenManager::puedeRendirFinal(int legajoAlumno, int idComision) {
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

bool ExamenManager::estaPromocionado(int legajoAlumno, int idComision) {
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

bool ExamenManager::estaRegular(int legajoAlumno, int idComision) {
    return puedeRendirFinal(legajoAlumno, idComision) && !estaPromocionado(legajoAlumno, idComision);
}

bool ExamenManager::estaLibre(int legajoAlumno, int idComision) {
    return !puedeRendirFinal(legajoAlumno, idComision);
}

void ExamenManager::mostrarHistorial(int legajoAlumno) {
    int total = _archivoExamen.contarRegistros();
    bool encontrado = false;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno && !ex.getEliminado()) {
            ex.mostrar();
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No hay exámenes registrados para este alumno.\n";
}

void ExamenManager::recalcularCondicion(int legajoAlumno, int idComision) {
    cout << "\nRecalculando condición académica del alumno " << legajoAlumno << "...\n";

    if (estaPromocionado(legajoAlumno, idComision))
        cout << "Condición: PROMOCIONADO\n";
    else if (estaRegular(legajoAlumno, idComision))
        cout << "Condición: REGULAR\n";
    else
        cout << "Condición: LIBRE\n";
}
