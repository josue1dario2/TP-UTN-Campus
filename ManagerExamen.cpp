#include "ManagerExamen.h"
#include "ArchivoComision.h"
#include "ManagerAlumno.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

ManagerExamen::ManagerExamen() : _archivoExamen("Examenes.dat") {}


// ======================================================================
// ALTAS
// ======================================================================
void ManagerExamen::cargarParcial(int legajoAlumno, int idComision, int nota) {

    // Obtener materia desde la comisión
    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    // Número de parcial (1 o 2)
    int numeroParcial = 1;

    // Contar parciales existentes
    int total = _archivoExamen.contarRegistros();
    int parcialesExistentes = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Parcial") == 0)
        {
            parcialesExistentes++;
        }
    }

    if (parcialesExistentes >= 2) {
        cout << "\nERROR: Ya tiene los 2 parciales cargados.\n";
        return;
    }

    numeroParcial = parcialesExistentes + 1;

    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idMateria, legajoAlumno, "Parcial", numeroParcial, hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nParcial registrado correctamente.\n";
    else
        cout << "\nError al registrar el parcial.\n";
}



void ManagerExamen::cargarRecuperatorio(int legajoAlumno, int idComision, int nota) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    // Recuperatorio va sobre un parcial existente → recupera el último parcial desaprobado
    int parcialARecu = -1;

    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Parcial") == 0 &&
            ex.getNota() < 4)
        {
            parcialARecu = ex.getNumeroParcial();
        }
    }

    if (parcialARecu == -1) {
        cout << "\nERROR: No tiene parciales desaprobados.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idMateria, legajoAlumno, "Recuperatorio", parcialARecu, hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nRecuperatorio registrado correctamente.\n";
    else
        cout << "\nError al registrar el recuperatorio.\n";
}




void ManagerExamen::cargarFinal(int legajoAlumno, int idComision, int nota) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    Fecha hoy;
    hoy.cargar();

    Examen ex(0, idMateria, legajoAlumno, "Final", 0, hoy, false);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.agregarRegistro(ex))
        cout << "\nFinal registrado correctamente.\n";
    else
        cout << "\nError al registrar el final.\n";
}


// ======================================================================
// VALIDACIONES
// ======================================================================
bool ManagerExamen::puedeRendirFinal(int legajoAlumno, int idComision) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);

    if (pos < 0) {
        cout << "\nERROR: La comisión no existe.\n";
        return false;
    }

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    // ---- 1) CORRELATIVAS ----
    ManagerAlumno ma;
    if (!ma.cumpleCorrelativas(legajoAlumno, idMateria)) {
        cout << "\nERROR: El alumno no cumple correlativas.\n";
        return false;
    }

    // ---- 2) REGULARIDAD REAL (Usando parciales + recuperatorios) ----
    float prom = promedioConReglas(legajoAlumno, idMateria);

    if (prom < 4) {
        cout << "\nERROR: No es regular (promedio: " << prom << ").\n";
        return false;
    }

    // ---- 3) YA APROBÓ FINAL ----
    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            ex.getNota() >= 4)
        {
            cout << "\nERROR: Ya tiene final aprobado.\n";
            return false;
        }
    }

    return true;
}




bool ManagerExamen::estaPromocionado(int legajoAlumno, int idComision) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) return false;

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    int total = _archivoExamen.contarRegistros();

    // Notas finales por parcial (1 o 2)
    int notaP1 = -1;
    int notaP2 = -1;

    int recuP1 = -1;
    int recuP2 = -1;

    // Buscar parciales y recuperatorios
    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria)
            continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) notaP1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) notaP2 = ex.getNota();
        }

        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) recuP1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) recuP2 = ex.getNota();
        }
    }

    // REGLA: Si usó recuperatorio, NO puede promocionar (solo regularizar)
    if (recuP1 != -1 || recuP2 != -1) {
        return false;
    }

    // Necesita los dos parciales aprobados (sin recuperatorios)
    if (notaP1 < 0 || notaP2 < 0) return false;

    float prom = (notaP1 + notaP2) / 2.0f;

    return prom >= 7;
}



bool ManagerExamen::estaRegular(int legajoAlumno, int idComision) {

    // Si promociona, no puede ser regular
    if (estaPromocionado(legajoAlumno, idComision))
        return false;

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) return false;

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    int total = _archivoExamen.contarRegistros();

    // Notas por parcial
    int notaP1 = -1, notaP2 = -1;
    int recuP1 = -1, recuP2 = -1;

    // Buscar parciales / recuperatorios
    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria)
            continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) notaP1 = ex.getNota();
            else if (ex.getNumeroParcial() == 2) notaP2 = ex.getNota();
        }

        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) recuP1 = ex.getNota();
            else if (ex.getNumeroParcial() == 2) recuP2 = ex.getNota();
        }
    }

    // Aplicar recuperatorios válidos
    if (recuP1 != -1) notaP1 = recuP1;
    if (recuP2 != -1) notaP2 = recuP2;

    // Para regularidad necesita haber rendido los dos parciales
    if (notaP1 < 0 || notaP2 < 0)
        return false;

    float promedio = (notaP1 + notaP2) / 2.0f;

    return promedio >= 4.0f;
}


bool ManagerExamen::estaLibre(int legajoAlumno, int idComision) {
    return !estaPromocionado(legajoAlumno, idComision) &&
           !estaRegular(legajoAlumno, idComision);
}

// ======================================================================
// REPORTES
// ======================================================================
void ManagerExamen::mostrarTodos() {
    int total = _archivoExamen.contarRegistros();

    cout << "\n=== LISTADO DE EXÁMENES ===\n";

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

    cout << "\n=== HISTORIAL DE EXÁMENES ===\n";

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno) {
            ex.mostrar();
            cout << "\n";
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No hay exámenes registrados.\n";
}

void ManagerExamen::recalcularCondicion(int legajoAlumno, int idComision) {
    cout << "\nRecalculando condición...\n";

    if (estaPromocionado(legajoAlumno, idComision))
        cout << "PROMOCIONADO\n";
    else if (estaRegular(legajoAlumno, idComision))
        cout << "REGULAR\n";
    else
        cout << "LIBRE\n";
}
float ManagerExamen::promedioConReglas(int legajo, int idMateria) {
    int p1 = -1, p2 = -1;
    int r1 = -1, r2 = -1;

    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdMateria() == idMateria)
        {
            if (strcmp(ex.getTipo(), "Parcial") == 0) {
                if (ex.getNumeroParcial() == 1) p1 = ex.getNota();
                if (ex.getNumeroParcial() == 2) p2 = ex.getNota();
            }

            if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
                if (ex.getNumeroParcial() == 1) r1 = ex.getNota();
                if (ex.getNumeroParcial() == 2) r2 = ex.getNota();
            }
        }
    }

    // Regla → recuperatorio reemplaza parcial
    int n1 = (r1 != -1 ? r1 : p1);
    int n2 = (r2 != -1 ? r2 : p2);

    float suma = 0;
    int cant = 0;

    if (n1 != -1) { suma += n1; cant++; }
    if (n2 != -1) { suma += n2; cant++; }

    if (cant == 0) return 0;

    return suma / cant;
}
