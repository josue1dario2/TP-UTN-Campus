#include "ManagerExamen.h"
#include "ArchivoComision.h"
#include "ManagerAlumno.h"
#include "ManagerInscripcionComision.h"
#include "ArchivoMateria.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
using namespace std;

ManagerExamen::ManagerExamen() : _archivoExamen("Examenes.dat") {}


// ======================================================================
// ALTAS
// ======================================================================
void ManagerExamen::cargarParcial(int legajoAlumno, int idComision, int nota) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    ManagerInscripcionComision manInsc;
    if (!manInsc.estaInscripto(legajoAlumno, idComision)) {
        cout << "\nERROR: El alumno NO está inscrito en esta comisión.\n";
        return;
    }

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    int posPend = _archivoExamen.buscarPendiente(legajoAlumno, idMateria, "Parcial");
    if (posPend < 0) {
        cout << "\nERROR: No hay parcial pendiente para corregir.\n";
        return;
    }

    Examen ex = _archivoExamen.leerRegistro(posPend);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.modificarRegistro(ex,posPend))
        cout << "\nParcial corregido correctamente.\n";
    else
        cout << "\nError al corregir el parcial.\n";
}

void ManagerExamen::cargarRecuperatorio(int legajoAlumno, int idComision, int nota) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    ManagerInscripcionComision manInsc;
    if (!manInsc.estaInscripto(legajoAlumno, idComision)) {
        cout << "\nERROR: El alumno NO está inscrito en esta comisión.\n";
        return;
    }

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    int posPend = _archivoExamen.buscarPendiente(legajoAlumno, idMateria, "Recuperatorio");
    if (posPend < 0) {
        cout << "\nERROR: No hay recuperatorio pendiente para corregir.\n";
        return;
    }

    Examen ex = _archivoExamen.leerRegistro(posPend);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.modificarRegistro(ex,posPend))
        cout << "\nRecuperatorio corregido correctamente.\n";
    else
        cout << "\nError al corregir el recuperatorio.\n";
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

    int posPend = _archivoExamen.buscarPendiente(legajoAlumno, idMateria, "Final");
    if (posPend < 0) {
        cout << "\nERROR: No hay final pendiente para corregir.\n";
        return;
    }

    Examen ex = _archivoExamen.leerRegistro(posPend);
    ex.setNota(nota);
    ex.setCorregido(true);

    if (_archivoExamen.modificarRegistro(ex,posPend))
        cout << "\nFinal corregido correctamente.\n";
    else
        cout << "\nError al corregir el final.\n";
}


// ======================================================================
// VALIDACIONES
// ======================================================================
bool ManagerExamen::puedeRendirFinal(int legajoAlumno, int idComision) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);

    if (pos < 0) return false;

    ManagerInscripcionComision manInsc;
    if (!manInsc.estaInscripto(legajoAlumno, idComision))
        return false;

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    ManagerAlumno ma;
    if (!ma.cumpleCorrelativas(legajoAlumno, idMateria))
        return false;

    if (estaPromocionado(legajoAlumno, idComision))
        return false;

    int p1 = -1, p2 = -1;
    int r1 = -1, r2 = -1;

    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria) continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) p1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) p2 = ex.getNota();
        }

        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) r1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) r2 = ex.getNota();
        }
    }

    if (r1 != -1) p1 = r1;
    if (r2 != -1) p2 = r2;

    if (p1 < 4 || p2 < 4) return false;

    return true;
}



// ======================================================================
// ESTADO ACADÉMICO
// ======================================================================
bool ManagerExamen::estaPromocionado(int legajoAlumno, int idComision) {

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) return false;

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    int notaP1 = -1, notaP2 = -1;
    int rec1 = -1, rec2 = -1;

    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria) continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) notaP1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) notaP2 = ex.getNota();
        }
        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) rec1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) rec2 = ex.getNota();
        }
    }

    if (rec1 != -1 || rec2 != -1) return false;

    if (notaP1 < 0 || notaP2 < 0) return false;

    float prom = (notaP1 + notaP2) / 2.0f;
    return prom >= 7;
}

bool ManagerExamen::estaPromocionadoPorMateria(int legajoAlumno, int idMateria) {
    int notaP1 = -1, notaP2 = -1;
    int rec1 = -1, rec2 = -1;

    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria) continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) notaP1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) notaP2 = ex.getNota();
        }
        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) rec1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) rec2 = ex.getNota();
        }
    }

    // Si usó algún recuperatorio → NO promociona
    if (rec1 != -1 || rec2 != -1) return false;

    // Debe tener ambos parciales cargados
    if (notaP1 < 0 || notaP2 < 0) return false;

    // Promedio de parciales
    float promedio = (notaP1 + notaP2) / 2.0f;

    return promedio >= 7;
}

bool ManagerExamen::estaRegular(int legajoAlumno, int idComision) {

    if (estaPromocionado(legajoAlumno, idComision)) return false;

    ArchivoComision ac;
    int pos = ac.buscarRegistro(idComision);
    if (pos < 0) return false;

    Comision com = ac.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    int p1 = -1, p2 = -1;
    int r1 = -1, r2 = -1;

    int total = _archivoExamen.contarRegistros();
    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria) continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) p1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) p2 = ex.getNota();
        }

        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) r1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) r2 = ex.getNota();
        }
    }

    if (r1 != -1) p1 = r1;
    if (r2 != -1) p2 = r2;

    if (p1 < 0 || p2 < 0) return false;

    float prom = (p1 + p2) / 2.0f;
    return prom >= 4;
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


// ======================================================================
// RECUPERATORIOS
// ======================================================================
bool ManagerExamen::recuperatorioPendiente(int legajo, int idMateria, int nro) {

    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Recuperatorio") == 0 &&
            ex.getNumeroParcial() == nro &&
            !ex.getCorregido() &&
            !ex.getEliminado())
        {
            return true;
        }
    }
    return false;
}

bool ManagerExamen::recuperatorioYaRendido(int legajo, int idMateria, int nro) {

    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Recuperatorio") == 0 &&
            ex.getNumeroParcial() == nro &&
            ex.getCorregido() &&
            !ex.getEliminado())
        {
            return true;
        }
    }
    return false;
}


// ======================================================================
// INSCRIPCIÓN A RECUPERATORIO  (ÚNICA VERSIÓN CORRECTA)
// ======================================================================
void ManagerExamen::inscribirARecuperatorio(int legajoAlumno) {

    ArchivoInscripcionComision archIns;
    ArchivoComision archCom;
    ArchivoMateria archMat;

    int totalIns = archIns.contarRegistros();
    if (totalIns == 0) {
        cout << "\nNo estás inscripto en ninguna comisión.\n";
        return;
    }

    cout << "\n=== INSCRIPCIÓN A RECUPERATORIO ===\n\n";

    int *comisiones = new int[totalIns];
    int cant = 0;

    cout << "+--------+------------------------------------------+--------------+\n";
    cout << "| OPCION |                  MATERIA                 |   COMISION   |\n";
    cout << "+--------+------------------------------------------+--------------+\n";

    for (int i = 0; i < totalIns; i++) {

        InscripcionComision ic = archIns.leerRegistro(i);

        if (ic.getLegajoAlumno() != legajoAlumno || ic.getEstado() != 0)
            continue;

        int pos = archCom.buscarRegistro(ic.getIdComision());
        if (pos < 0) continue;

        Comision com = archCom.leerRegistro(pos);

        string nombreMateria = "N/A";
        int posMat = archMat.buscarRegistro(com.getIdMateria());
        if (posMat >= 0) {
            Materia m = archMat.leerRegistro(posMat);
            nombreMateria = m.getNombre();
        }

        comisiones[cant] = com.getIdComision();

        cout << "| " << setw(6) << left << cant + 1
             << " | " << setw(40) << left << nombreMateria
             << " | " << setw(12) << left << com.getIdComision()
             << " |\n";

        cant++;
    }

    cout << "+--------+------------------------------------------+--------------+\n";

    if (cant == 0) {
        cout << "\nNo hay comisiones donde estés inscripto.\n";
        delete[] comisiones;
        return;
    }

    int opcion;
    cout << "\nIngrese número de opción: ";
    cin >> opcion;

    if (opcion < 1 || opcion > cant) {
        cout << "\nOpción inválida.\n";
        delete[] comisiones;
        return;
    }

    int idComision = comisiones[opcion - 1];
    delete[] comisiones;

    int posC = archCom.buscarRegistro(idComision);
    if (posC < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    Comision com = archCom.leerRegistro(posC);
    int idMateria = com.getIdMateria();

    int totalEx = _archivoExamen.contarRegistros();

    int p1 = -1, p2 = -1;

    for (int i = 0; i < totalEx; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria) continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0 && ex.getCorregido()) {
            if (ex.getNumeroParcial() == 1) p1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) p2 = ex.getNota();
        }
    }

    int nroRec = -1;
    if (p1 >= 0 && p1 < 4) nroRec = 1;
    else if (p2 >= 0 && p2 < 4) nroRec = 2;
    else {
        cout << "\nNo tenés recuperatorios disponibles.\n";
        return;
    }

    if (recuperatorioYaRendido(legajoAlumno, idMateria, nroRec)) {
        cout << "\nYa rendiste el Recuperatorio " << nroRec << ".\n";
        return;
    }

    if (recuperatorioPendiente(legajoAlumno, idMateria, nroRec)) {
        cout << "\nYa tenés un recuperatorio pendiente.\n";
        return;
    }

    Examen nuevo;

    nuevo.setLegajoAlumno(legajoAlumno);
    nuevo.setIdMateria(idMateria);
    nuevo.setTipo("Recuperatorio");
    nuevo.setNumeroParcial(nroRec);
    nuevo.setNota(-1);
    nuevo.setCorregido(false);
    nuevo.setEliminado(false);

    time_t t = time(NULL);
    tm *f = localtime(&t);

    Fecha hoy;
    hoy.setDia(f->tm_mday);
    hoy.setMes(f->tm_mon + 1);
    hoy.setAnio(f->tm_year + 1900);

    nuevo.setFecha(hoy);

    if (_archivoExamen.agregarRegistro(nuevo))
        cout << "\nInscripción realizada con éxito.\n";
    else
        cout << "\nERROR al guardar el recuperatorio.\n";
}
// ======================================================================
// FUNCIONES UTILIZADAS POR ALUMNO Y REPORTES
// ======================================================================

float ManagerExamen::promedioConReglas(int legajo, int idMateria) {

    int p1 = -1, p2 = -1;
    int r1 = -1, r2 = -1;

    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajo ||
            ex.getIdMateria() != idMateria)
            continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) p1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) p2 = ex.getNota();
        }

        if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
            if (ex.getNumeroParcial() == 1) r1 = ex.getNota();
            if (ex.getNumeroParcial() == 2) r2 = ex.getNota();
        }
    }

    int nota1 = (r1 != -1 ? r1 : p1);
    int nota2 = (r2 != -1 ? r2 : p2);

    float suma = 0;
    int cant = 0;

    if (nota1 >= 0) { suma += nota1; cant++; }
    if (nota2 >= 0) { suma += nota2; cant++; }

    if (cant == 0) return 0;

    return suma / cant;
}



bool ManagerExamen::finalAprobado(int legajo, int idMateria) {

    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {

        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            ex.getNota() >= 4 &&
            !ex.getEliminado())
        {
            return true;
        }
    }

    return false;
}



void ManagerExamen::recalcularCondicion(int legajoAlumno, int idComision) {

    cout << "\nRecalculando condición académica...\n";

    if (estaPromocionado(legajoAlumno, idComision))
        cout << "ESTADO: PROMOCIONADO\n";

    else if (estaRegular(legajoAlumno, idComision))
        cout << "ESTADO: REGULAR\n";

    else
        cout << "ESTADO: LIBRE\n";
}
