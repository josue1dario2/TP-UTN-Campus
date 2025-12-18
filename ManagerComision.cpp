#include "ManagerComision.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ----------------------------------------------------
// INTERNOS
// ----------------------------------------------------
void ManagerComision::listarEncabezado() {
    cout << "\t+------------+------------+------------------------------+------------+------------+------------+------------+\n";
    cout << "\t| IDComision | IDMateria  | Docente                      | Turno      | Modalidad  | Año        | Eliminado  |\n";
    cout << "\t+------------+------------+------------------------------+------------+------------+------------+------------+\n";
}

void ManagerComision::listarRegistro(const Comision& c) {

    string nomDoc = nombreCompletoDocente(c.getLegajoDocente());

    cout << "\t| " << setw(10) << right << c.getIdComision()
         << " | " << setw(10) << right << c.getIdMateria()
         << " | " << setw(28) << left  << nomDoc
         << " | " << setw(10) << left  << c.getTurno()
         << " | " << setw(10) << left  << c.getModalidad()
         << " | " << setw(10) << right << c.getAnio()
         << " | " << setw(10) << right << (c.getEliminado() ? "Sí" : "No")
         << " |\n";
}


void ManagerComision::listarPie() {
    cout << "\t+------------+------------+------------------------------+------------+------------+------------+------------+\n";
}

bool ManagerComision::obtenerComisionValida(int id, Comision& out) {
    int pos = _archivo.buscarRegistro(id);
    if (pos < 0) return false;
    out = _archivo.leerRegistro(pos);
    return true;
}

bool ManagerComision::existeIDMateria(int idMateria) {
    return _archMaterias.buscarRegistro(idMateria) >= 0;
}

bool ManagerComision::existeLegajoDocente(int legajo) {
    return _archDocentes.buscarRegistro(legajo) >= 0;
}

int ManagerComision::generarIDComision() {
    return _archivo.contarRegistros() + 1;
}

// ----------------------------------------------------
// ALTA
// ----------------------------------------------------
void ManagerComision::alta() {
    cout << "\n\t=== ALTA DE COMISIÓN ===\n";

    // Mostrar docentes
    cout << "\n\t--- DOCENTES DISPONIBLES ---\n";
    int cantDoc = _archDocentes.contarRegistros();
    for (int i = 0; i < cantDoc; i++) {
        Docente d = _archDocentes.leerRegistro(i);
        if (!d.getEliminado())
            cout << "\tLegajo: " << d.getLegajo()
                 << " | " << quitarAcentos(d.getNombre()) << " " << quitarAcentos(d.getApellido()) << "\n";
    }

    int legajoDoc = Validacion::validarEntero("\n\tIngrese legajo del docente: ");
    if (!existeLegajoDocente(legajoDoc)) {
        cout << "\n\tERROR: El docente no existe.\n";
        return;
    }

    // Mostrar materias
    cout << "\n\t--- MATERIAS DISPONIBLES ---\n";
    int cantMat = _archMaterias.contarRegistros();
    for (int i = 0; i < cantMat; i++) {
        Materia m = _archMaterias.leerRegistro(i);
        if (!m.getEliminado())
            cout << "\tID: " << m.getIdMateria()
                 << " | " << quitarAcentos(m.getNombre()) << "\n";
    }

    int idMat = Validacion::validarEntero("\n\tIngrese ID de materia: ");
    if (!existeIDMateria(idMat)) {
        cout << "\n\tERROR: La materia no existe.\n";
        return;
    }

    // Turno
    string turno;
    int t = Validacion::validarEnteroEnRango("\tTurno (1-Mañana, 2-Tarde, 3-Noche): ", 1, 3);
    turno = (t == 1 ? "Manana" : t == 2 ? "Tarde" : "Noche");

    // Modalidad
    string modalidad;
    int m = Validacion::validarEnteroEnRango("\tModalidad (1-Presenc., 2-Virtual, 3-Híbrida): ", 1, 3);
    modalidad = (m == 1 ? "Presenc." : m == 2 ? "Virtual" : "Híbrida");

    // Cuatrimestre / año
    int cuatr = Validacion::validarEnteroEnRango("\tCuatrimestre (1-2): ", 1, 2);
    int anio = Validacion::validarEnteroEnRango("\tAño (2020-2030): ", 2020, 2030);

    Comision nueva(generarIDComision(), idMat, turno.c_str(), modalidad.c_str(),
                   cuatr, anio, legajoDoc, false);

    if (_archivo.agregarRegistro(nueva))
        cout << "\n\tComisión cargada correctamente.\n";
    else
        cout << "\n\tERROR al guardar.\n";
}


// ----------------------------------------------------
// MODIFICAR
// ----------------------------------------------------
void ManagerComision::modificar() {
    cout << "\n\t=== MODIFICAR COMISIÓN ===\n";

    int total = _archivo.contarRegistros();
    bool hayActivas = false;

    // Verificar si existen comisiones activas
    for (int i = 0; i < total; i++) {
        if (!_archivo.leerRegistro(i).getEliminado()) {
            hayActivas = true;
            break;
        }
    }

    if (!hayActivas) {
        cout << "\n\tNo hay comisiones activas.\n";
        return;
    }

    // Si hay activas, ahora sí mostramos la tabla
    mostrarComisionesActivas();

    int id = Validacion::validarEntero("\n\tID de comisión: ");

    Comision c;
    if (!obtenerComisionValida(id, c) || c.getEliminado()) {
        cout << "\n\tERROR: Comisión inexistente o dada de baja.\n";
        return;
    }

    cout << "\n\t=== NUEVOS DATOS ===\n";

    int idMat = Validacion::validarEntero("\tID Materia: ");
    if (!existeIDMateria(idMat)) {
        cout << "\n\tERROR: Materia no válida.\n";
        return;
    }

    string turno;
    int t = Validacion::validarEnteroEnRango("\tTurno (1-Mañana, 2-Tarde, 3-Noche): ", 1, 3);
    turno = (t == 1 ? "Manana" : t == 2 ? "Tarde" : "Noche");

    string modalidad;
    int m = Validacion::validarEnteroEnRango("\tModalidad (1-Presenc., 2-Virtual, 3-Híbrida): ", 1, 3);
    modalidad = (m == 1 ? "Presenc." : m == 2 ? "Virtual" : "Híbrida");

    int cuatr = Validacion::validarEnteroEnRango("\tCuatrimestre (1-2): ", 1, 2);
    int anio = Validacion::validarEnteroEnRango("\tAño (2020-2030): ", 2020, 2030);
    int legajo = Validacion::validarEntero("\tLegajo docente: ");

    Comision nueva(id, idMat, turno.c_str(), modalidad.c_str(), cuatr, anio, legajo, false);

    int pos = _archivo.buscarRegistro(id);
    if (_archivo.modificarRegistro(nueva, pos))
        cout << "\n\tModificación exitosa.\n";
    else
        cout << "\n\tError al modificar.\n";
}



// ----------------------------------------------------
// BAJA LÓGICA
// ----------------------------------------------------
void ManagerComision::borrar() {
    cout << "\n\t=== BAJA LÓGICA DE COMISIÓN ===\n";

    int total = _archivo.contarRegistros();
    bool hayActivas = false;

    // Primero revisamos si HAY comisiones activas
    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado()) {
            hayActivas = true;
            break;
        }
    }

    // Si NO hay comisiones activas → cortar acá
    if (!hayActivas) {
        cout << "\n\tNo hay comisiones activas.\n";
        return;
    }

    // Si hay activas → recién ahí las mostramos
    mostrarComisionesActivas();

    int id = Validacion::validarEntero("\n\tID de comisión: ");

    Comision c;
    if (!obtenerComisionValida(id, c) || c.getEliminado()) {
        cout << "\n\tID inválido.\n";
        return;
    }

    int pos = _archivo.buscarRegistro(id);
    if (_archivo.bajaLogica(pos))
        cout << "\n\tComisión dada de baja.\n";
    else
        cout << "\n\tError al eliminar.\n";
}



// ----------------------------------------------------
// REACTIVAR
// ----------------------------------------------------
void ManagerComision::activar() {
    mostrarComisionesInactivas();

    int id = Validacion::validarEntero("\n\tID de comisión a reactivar: ");

    Comision c;
    if (!obtenerComisionValida(id, c) || !c.getEliminado()) {
        cout << "\n\tERROR: ID inválido.\n";
        return;
    }

    int pos = _archivo.buscarRegistro(id);
    if (_archivo.activarRegistro(pos))
        cout << "\n\tComisión reactivada.\n";
    else
        cout << "\n\tError al reactivar.\n";
}



// ----------------------------------------------------
// LISTADOS
// ----------------------------------------------------
void ManagerComision::listarComisiones() {
    bool incluirBajas =
        Validacion::desearAccionar("\n\t¿Mostrar comisiones eliminadas? (s/n): ");

    int total = _archivo.contarRegistros();
    bool hay = false;

    // --- Verificar si hay algo para mostrar ---
    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);

        // Si debe incluir bajas → cualquier registro es válido
        // Si no → solo comisiones activas
        if (incluirBajas || !c.getEliminado()) {
            hay = true;
            break;
        }
    }

    // --- Si no hay comisiones coincidentes, mostrar mensaje y salir ---
    if (!hay) {
        cout << "\n\tNo hay comisiones para mostrar.\n";
        return;
    }

    // --- Mostrar tabla ---
    listarEncabezado();

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);

        if (!incluirBajas && c.getEliminado()) continue;

        listarRegistro(c);
    }

    listarPie();
}

void ManagerComision::listarPorMateria() {
    // Listar materias
    cout << "\n\t=== MATERIAS DISPONIBLES ===\n";
    int cant = _archMaterias.contarRegistros();

    for (int i = 0; i < cant; i++) {
        Materia m = _archMaterias.leerRegistro(i);
        if (!m.getEliminado())
            cout << "\tID: " << m.getIdMateria()
                 << " | " << quitarAcentos(m.getNombre()) << "\n";
    }

    int idMat = Validacion::validarEntero("\n\tIngrese ID de materia: ");

    int posMat = _archMaterias.buscarRegistro(idMat);
    if (posMat < 0) {
        cout << "\n\tERROR: La materia ingresada NO existe.\n";
        return;
    }

    Materia mat = _archMaterias.leerRegistro(posMat);
    if (mat.getEliminado()) {
        cout << "\n\tERROR: Esa materia está eliminada.\n";
        return;
    }

    cout << "\n\t=== COMISIONES DE LA MATERIA: "
         << quitarAcentos(mat.getNombre()) << " ===\n";

    int total = _archivo.contarRegistros();
    bool found = false;

    // Primero verificamos si existe alguna comisión antes de imprimir tabla
    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateria() == idMat) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\tNo hay comisiones para esta materia.\n";
        return;
    }

    listarEncabezado();

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateria() == idMat) {
            listarRegistro(c);
        }
    }

    listarPie();
}


void ManagerComision::mostrarComisionesActivas() {
    int total = _archivo.contarRegistros();
    bool hayActivas = false;

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado()) {
            hayActivas = true;
            break;
        }
    }

    if (!hayActivas) {
        cout << "\n\tNo hay comisiones activas.\n";
        return;
    }

    listarEncabezado();
    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado()) {
            listarRegistro(c);
        }
    }
    listarPie();
}


void ManagerComision::mostrarComisionesInactivas() {
    int total = _archivo.contarRegistros();
    bool hayInactivas = false;

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (c.getEliminado()) {
            hayInactivas = true;
            break;
        }
    }

    if (!hayInactivas) {
        cout << "\n\tNo hay comisiones inactivas.\n";
        return;
    }

    listarEncabezado();
    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (c.getEliminado())
            listarRegistro(c);
    }
    listarPie();
}

bool ManagerComision::existeComision(int idComision) {
    int pos = _archivo.buscarRegistro(idComision);
    if (pos < 0) return false;

    Comision c = _archivo.leerRegistro(pos);
    return !c.getEliminado();
}

string ManagerComision::nombreCompletoDocente(int legajo) {
    int pos = _archDocentes.buscarRegistro(legajo);
    if (pos < 0) return "Desconocido";

    Docente d = _archDocentes.leerRegistro(pos);

    string nombre = quitarAcentos(d.getNombre());
    string apellido = quitarAcentos(d.getApellido());

    return nombre + " " + apellido + " (" + to_string(d.getLegajo()) + ")";
}
