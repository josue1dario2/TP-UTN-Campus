#include "ExamenManager.h"
using namespace std;

ExamenManager::ExamenManager() : _archivoExamen("Examenes.dat") {}

// Verifica si el alumno ya usó un recuperatorio para un parcial específico
bool ExamenManager::_yaUsoRecuperatorio(int legajoAlumno, int idComision, int numeroParcial) {
    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {
        Examen reg = _archivoExamen.leerRegistro(i);
        if (reg.getLegajoAlumno() == legajoAlumno && reg.getIdComision() == idComision) {
            // Recuperatorios: tipoExamen = 4,5,6 → corresponden a parciales 1,2,3
            if (reg.getTipoExamen() >= 4 && reg.getTipoExamen() <= 6) {
                int parcialAsociado = reg.getTipoExamen() - 3;
                if (parcialAsociado == numeroParcial && !reg.getEliminado())
                    return true;
            }
        }
    }
    return false;
}

// Verifica si ya existe un examen de cierto tipo
bool ExamenManager::_existeExamen(int legajoAlumno, int idComision, int tipoExamen) {
    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {
        Examen reg = _archivoExamen.leerRegistro(i);
        if (reg.getLegajoAlumno() == legajoAlumno &&
            reg.getIdComision() == idComision &&
            reg.getTipoExamen() == tipoExamen &&
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

    int tipoExamen = numeroParcial; // 1, 2 o 3
    if (_existeExamen(legajoAlumno, idComision, tipoExamen)) {
        cout << "El alumno ya tiene registrado ese parcial.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar(); // O asignar fecha actual si la tenés implementada
    Examen ex(0, idComision, legajoAlumno, tipoExamen, hoy);
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

    int tipoExamen = numeroParcial + 3; // 4, 5 o 6
    Fecha hoy;
    hoy.cargar();
    Examen ex(0, idComision, legajoAlumno, tipoExamen, hoy);
    ex.corregir(nota);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "Recuperatorio registrado correctamente.\n";
    else
        cout << "Error al registrar el recuperatorio.\n";
}

void ExamenManager::cargarFinal(int legajoAlumno, int idComision, int nota) {
    int tipoExamen = 7; // Final
    if (_existeExamen(legajoAlumno, idComision, tipoExamen)) {
        cout << "El alumno ya tiene un examen final registrado.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();
    Examen ex(0, idComision, legajoAlumno, tipoExamen, hoy);
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
            ex.getTipoExamen() >= 1 && ex.getTipoExamen() <= 6 &&
            ex.getNota() >= 4) {
            aprobados++;
        }
    }
    return aprobados >= 2; // Por ejemplo: necesita 2 parciales aprobados
}

bool ExamenManager::estaPromocionado(int legajoAlumno, int idComision) {
    int total = _archivoExamen.contarRegistros();
    int suma = 0, cantidad = 0;
    bool usoRecuperatorio = false;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno && ex.getIdComision() == idComision) {
            if (ex.getTipoExamen() >= 1 && ex.getTipoExamen() <= 6 && ex.getNota() >= 0) {
                suma += ex.getNota();
                cantidad++;
                if (ex.getTipoExamen() >= 4 && ex.getTipoExamen() <= 6)
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
