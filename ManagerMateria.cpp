#include "ManagerMateria.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// ============================================================
//                      ALTA
// ============================================================

void ManagerMateria::alta() {
    Materia reg;

    reg.setIdMateria(generarIdNuevo());
    reg.cargar();

    int idCarrera = reg.getIdCarrera();

    if (_archivoCarreras.existeCarrera(idCarrera)) {
        if (_archivoMaterias.agregarRegistro(reg) == 1)
            cout << "\n\tMateria guardada con éxito.\n";
        else
            cout << "\n\tError al guardar la materia.\n";
    }
    else {
        cout << "\n\tEl ID de Carrera no existe.\n";
    }
}



// ============================================================
//                      ACTIVAR
// ============================================================

void ManagerMateria::activar() {
    int id = Validacion::validarEnteroEnRango(
        "\tIngrese el ID de la materia a activar: ", 1,10000);

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    if (Validacion::desearAccionar("Desea activar la materia? s/n: ")) {
        if (_archivoMaterias.activarRegistro(pos))
            cout << "Materia activada correctamente.\n";
        else
            cout << "No se pudo activar.\n";
    }
}



// ============================================================
//                       BAJA
// ============================================================

void ManagerMateria::baja() {
    int id;
    cout << "Ingrese el ID de la materia a eliminar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    if (Validacion::desearAccionar("Desea borrar la materia? s/n: ")) {
        if (_archivoMaterias.bajaLogica(pos))
            cout << "Materia dada de baja correctamente.\n";
        else
            cout << "No se pudo eliminar.\n";
    }
}



// ============================================================
//                       LISTAR TODAS
// ============================================================

void ManagerMateria::listarTodas() {
    bool incluirBorrados =
        Validacion::desearAccionar("\n\t¿Desea incluir los registros borrados? (s/n): ");

    int cantidad = _archivoMaterias.contarRegistros();
    if (cantidad == 0) {
        cout << "\n\tNo hay materias registradas.\n";
        return;
    }

    ArchivoCarrera archCar("Carreras.dat");

    cout << "\n\t=== LISTADO DE MATERIAS ===\n\n";

    cout << left;
    cout << setw(30) << "Carrera"
         << setw(5)  << "ID"
         << setw(38) << "Nombre"
         << setw(12) << "Cuatrim."
         << setw(10) << "Estado"
         << setw(10) << "Elimin."
         << "\n";

    cout << string(105, '-') << "\n";

    for (int i = 0; i < cantidad; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);
        if (!incluirBorrados && mat.getEliminado()) continue;

        string nombreCarrera = "Desconocida";
        int posCar = archCar.buscarPosicion(mat.getIdCarrera());

        if (posCar >= 0) {
            Carrera c = archCar.leerRegistro(posCar);
            nombreCarrera = quitarAcentos(c.getNombre());
        }

        cout << setw(30) << nombreCarrera
             << setw(5)  << mat.getIdMateria()
             << setw(38) << quitarAcentos(mat.getNombre())
             << setw(12) << mat.getCuatrimestre()
             << setw(10) << mat.getEstado()
             << setw(10) << (mat.getEliminado() ? "Si" : "No")
             << "\n";
    }

    cout << string(105, '-') << "\n";
    cin.ignore(10000, '\n');
}



// ============================================================
//                   LISTAR SOLO ACTIVAS
// ============================================================

void ManagerMateria::listarMateriasActivas() {
    int total = _archivoMaterias.contarRegistros();
    if (total == 0) {
        cout << "\n\tNo existen materias cargadas.\n";
        return;
    }

    cout << "\n\t=== LISTADO DE MATERIAS ACTIVAS ===\n\n";

    cout << left;
    cout << setw(5)  << "ID"
         << setw(35) << "Nombre"
         << setw(32) << "Carrera"
         << setw(10) << "Cuat."
         << "\n";
    cout << string(82, '-') << "\n";

    for (int i = 0; i < total; i++) {
        Materia m = _archivoMaterias.leerRegistro(i);
        if (m.getEliminado()) continue;

        string nombreCarrera = "Desconocida";

        int posCar = _archivoCarreras.buscarPosicion(m.getIdCarrera());
        if (posCar >= 0) {
            Carrera c = _archivoCarreras.leerRegistro(posCar);
            nombreCarrera = quitarAcentos(c.getNombre());
        }

        cout << setw(5)  << m.getIdMateria()
             << setw(35) << quitarAcentos(m.getNombre())
             << setw(32) << nombreCarrera
             << setw(10) << m.getCuatrimestre()
             << "\n";
    }

    cout << string(75, '-') << "\n";
}



// ============================================================
//                       MODIFICACIÓN
// ============================================================

void ManagerMateria::modificacion() {
    cout << "\n\t=== Modificar Materia ===\n";

    // Mostrar solo materias activas ANTES de pedir ID
    listarMateriasActivas();

    // Pedir ID
    int id = Validacion::validarEntero("\n\tID de materia a modificar: ");
    int pos = buscarPorId(id);

    if (pos < 0) {
        cout << "\n\tMateria no encontrada.\n";
        return;
    }

    Materia actual = _archivoMaterias.leerRegistro(pos);

    if (actual.getEliminado()) {
        cout << "\n\tLa materia está eliminada.\n";
        return;
    }

    // Buscar nombre de la carrera para uso interno
    string nombreCarrera = "Desconocida";
    int posCar = _archivoCarreras.buscarPosicion(actual.getIdCarrera());

    if (posCar >= 0) {
        Carrera c = _archivoCarreras.leerRegistro(posCar);
        nombreCarrera = quitarAcentos(c.getNombre());
    }

    // --- Nuevos datos ---
    cout << "\n\t=== Nuevos datos ===\n";

    Materia nueva;
    nueva.setIdMateria(id);   // mantengo ID original
    nueva.cargar(false);      // cargar sin preguntar estado

    // Guardar cambios
    if (Validacion::desearAccionar("\n\t¿Desea guardar los cambios? (s/n): ")) {
        if (_archivoMaterias.modificarRegistro(nueva, pos))
            cout << "\n\tMateria modificada correctamente.\n";
        else
            cout << "\n\tError al modificar.\n";
    }
    else {
        cout << "\n\tOperación cancelada.\n";
    }
}




// ============================================================
//               BUSCAR - GENERAR ID
// ============================================================

int ManagerMateria::buscarPorId(int idMateria) {
    return _archivoMaterias.buscarRegistro(idMateria);
}


int ManagerMateria::generarIdNuevo() {
    int cant = _archivoMaterias.contarRegistros();
    int maxID = 0;

    for (int i = 0; i < cant; i++) {
        Materia reg = _archivoMaterias.leerRegistro(i);
        if (reg.getIdMateria() > maxID)
            maxID = reg.getIdMateria();
    }
    return maxID + 1;
}
