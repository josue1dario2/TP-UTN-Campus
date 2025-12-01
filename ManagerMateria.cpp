#include "ManagerMateria.h"
#include "Validacion.h"
#include "ArchivoCorrelativa.h"
#include "utils.h"

#include <iostream>
#include <iomanip>
using namespace std;

/* ============================================================
                           HELPERS
   ============================================================ */

// Devuelve el nombre de la carrera de una materia
string ManagerMateria::nombreCarrera(int idCarrera) {
    int pos = _archivoCarreras.buscarPosicion(idCarrera);
    if (pos < 0) return "Desconocida";

    Carrera c = _archivoCarreras.leerRegistro(pos);
    return quitarAcentos(c.getNombre());
}

// Verifica si existe una materia con ese ID
bool ManagerMateria::obtenerMateriaValida(int id, Materia& out) {
    int pos = buscarPorId(id);
    if (pos < 0) return false;

    out = _archivoMaterias.leerRegistro(pos);
    return true;
}

// Verifica si existe y además NO está eliminada
bool ManagerMateria::obtenerMateriaActiva(int id, Materia& out) {
    if (!obtenerMateriaValida(id, out)) return false;
    return !out.getEliminado();
}

// Listado unificado para Activas / Inactivas / Todas
void ManagerMateria::listar(bool activas, bool inactivas, const string& titulo) {
    int total = _archivoMaterias.contarRegistros();

    cout << "\n\t=== " << titulo << " ===\n\n";

    cout << left;
    cout << setw(5)  << "ID"
         << setw(35) << "Nombre"
         << setw(40) << "Carrera"
         << setw(10) << "Cuat."
         << setw(12) << "Estado"
         << setw(12) << "Elimin."
         << "\n";

    cout << string(120, '-') << "\n";

    for (int i = 0; i < total; i++) {
        Materia m = _archivoMaterias.leerRegistro(i);

        // FILTROS
        if (m.getEliminado() && !inactivas) continue;
        if (!m.getEliminado() && !activas) continue;

        cout << setw(5)  << m.getIdMateria()
             << setw(35) << quitarAcentos(m.getNombre())
             << setw(40) << nombreCarrera(m.getIdCarrera())
             << setw(10) << m.getCuatrimestre()
             << setw(12) << m.getEstado()
             << setw(12) << (m.getEliminado() ? "SI" : "NO")
             << "\n";
    }

    cout << string(120, '-') << "\n\n";
}



/* ============================================================
                         ALTA
   ============================================================ */

void ManagerMateria::alta() {
    Materia reg;

    reg.setIdMateria(generarIdNuevo());
    reg.cargar();

    int idCarrera = reg.getIdCarrera();

    if (_archivoCarreras.existeCarrera(idCarrera)) {
        if (_archivoMaterias.agregarRegistro(reg))
            cout << "\n\tMateria guardada con éxito.\n";
        else
            cout << "\n\tError al guardar.\n";
    }
    else {
        cout << "\n\tEl ID de Carrera no existe.\n";
    }
}


/* ============================================================
                         ACTIVAR
   ============================================================ */

void ManagerMateria::activar() {
    cout << "\n\t=== Activar Materia ===\n";

    listarMateriasInactivas();

    int id = Validacion::validarEntero("\n\tID de la materia a activar: ");

    Materia m;
    if (!obtenerMateriaValida(id, m) || !m.getEliminado()) {
        cout << "\n\tLa materia no existe o ya está activa.\n";
        return;
    }

    if (Validacion::desearAccionar("\t¿Activar? (s/n): ")) {
        int pos = buscarPorId(id);
        _archivoMaterias.activarRegistro(pos);
        cout << "\n\tMateria activada correctamente.\n";
    }
}


/* ============================================================
                          BAJA
   ============================================================ */

void ManagerMateria::baja() {
    cout << "\n\t=== Eliminar Materia ===\n";

    listarMateriasActivas();

    int id = Validacion::validarEntero("\n\tID de la materia a eliminar: ");

    Materia m;
    if (!obtenerMateriaActiva(id, m)) {
        cout << "\n\tMateria inexistente o ya eliminada.\n";
        return;
    }

    if (Validacion::desearAccionar("\t¿Eliminar? (s/n): ")) {
        int pos = buscarPorId(id);
        _archivoMaterias.bajaLogica(pos);
        cout << "\n\tMateria eliminada correctamente.\n";
    }
}


/* ============================================================
                      LISTAR TODAS / ACTIVAS / INACTIVAS
   ============================================================ */

void ManagerMateria::listarTodas() {

    bool incluirEliminadas =
        Validacion::desearAccionar("\n\t¿Desea incluir materias eliminadas? (s/n): ");

    if (incluirEliminadas)
        listar(true, true, "LISTADO DE TODAS LAS MATERIAS");
    else
        listar(true, false, "LISTADO DE MATERIAS ACTIVAS");
}

void ManagerMateria::listarMateriasActivas() {
    listar(true, false, "LISTADO DE MATERIAS ACTIVAS");
}

void ManagerMateria::listarMateriasInactivas() {
    listar(false, true, "LISTADO DE MATERIAS INACTIVAS");
}


/* ============================================================
                        MODIFICACIÓN
   ============================================================ */

void ManagerMateria::modificacion() {
    cout << "\n\t=== Modificar Materia ===\n";

    listarMateriasActivas();

    int id = Validacion::validarEntero("\n\tID de materia a modificar: ");

    Materia actual;
    if (!obtenerMateriaActiva(id, actual)) {
        cout << "\n\tMateria inexistente o inactiva.\n";
        return;
    }

    cout << "\n\t=== Nuevos datos ===\n";

    Materia nueva;
    nueva.setIdMateria(id);
    nueva.cargar(false);

    if (Validacion::desearAccionar("\n\t¿Guardar cambios? (s/n): ")) {
        int pos = buscarPorId(id);
        _archivoMaterias.modificarRegistro(nueva, pos);
        cout << "\n\tMateria modificada correctamente.\n";
    }
}


/* ============================================================
                       VER CORRELATIVAS
   ============================================================ */

void ManagerMateria::verCorrelativas() {
    cout << "\n\t=== Ver Correlativas ===\n";

    listarMateriasActivas();

    int idMat = Validacion::validarEntero("\n\tIngrese ID de la materia: ");

    Materia m;
    if (!obtenerMateriaActiva(idMat, m)) {
        cout << "\n\tERROR: ID inválido o materia eliminada.\n";
        return;
    }

    clearScreen();
    ArchivoCorrelativa arch("Correlativas.dat");
    arch.listarDeMateria(idMat);

    cout << "\n";
    pauseScreen();
}


/* ============================================================
                BUSCAR Y GENERAR ID
   ============================================================ */

int ManagerMateria::buscarPorId(int idMateria) {
    return _archivoMaterias.buscarRegistro(idMateria);
}

int ManagerMateria::generarIdNuevo() {
    int cant = _archivoMaterias.contarRegistros();
    int maxID = 0;

    for (int i = 0; i < cant; i++) {
        Materia m = _archivoMaterias.leerRegistro(i);
        if (m.getIdMateria() > maxID)
            maxID = m.getIdMateria();
    }
    return maxID + 1;
}
