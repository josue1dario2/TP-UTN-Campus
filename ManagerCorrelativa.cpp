#include "ManagerCorrelativa.h"
#include "Validacion.h"
using namespace std;

ManagerCorrelativa::ManagerCorrelativa() {}

void ManagerCorrelativa::mostrarEncabezado() {
    cout << "\t+-----------------+------------------+-----------+\n";
    cout << "\t| Materia Obj. ID | Materia Req. ID  | Borrado   |\n";
    cout << "\t+-----------------+------------------+-----------+\n";
}

void ManagerCorrelativa::mostrarRegistro(const Correlativa& reg) {
    cout << "\t| " << setw(15) << reg.getIdMateriaObjetivo()
         << " | " << setw(16) << reg.getIdMateriaRequisito()
         << " | " << setw(9)  << (reg.getEliminado() ? "Sí" : "No")
         << " |\n";
}

void ManagerCorrelativa::mostrarPie() {
    cout << "\t+-----------------+------------------+-----------+\n";
}

void ManagerCorrelativa::cargar() {
    cout << "\n\t=== Cargar Correlativa ===\n";

    int idObjetivo = Validacion::validarEnteroEnRango("\tID Materia Objetivo: ", 1, 9999);
    int idRequisito = Validacion::validarEnteroEnRango("\tID Materia Requisito: ", 1, 9999);

    if (idObjetivo == idRequisito) {
        cout << "\tUna materia no puede depender de sí misma.\n";
        return;
    }

    Correlativa nueva(idObjetivo, idRequisito, false);

    if (_archivo.agregarRegistro(nueva) > 0)
        cout << "\tCorrelativa agregada correctamente.\n";
    else
        cout << "\tError al guardar correlativa.\n";
}

void ManagerCorrelativa::listar() {
    cout << "\n\t=== Listado de Correlativas ===\n";
    int total = _archivo.contarRegistros();
    if (total == 0) {
        cout << "\tNo hay correlativas registradas.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; i++) {
        Correlativa reg = _archivo.leerRegistro(i);
        mostrarRegistro(reg);
    }
    mostrarPie();
}

void ManagerCorrelativa::borrar() {
    cout << "\n\t=== Borrar Correlativa ===\n";
    int idObj = Validacion::validarEnteroEnRango("\tID Materia Objetivo: ", 1, 9999);
    int pos = _archivo.buscarPorMateriaObjetivo(idObj);
    if (pos < 0) {
        cout << "\tNo se encontró esa correlativa.\n";
        return;
    }

    if (_archivo.bajaLogica(pos))
        cout << "\tCorrelativa dada de baja.\n";
    else
        cout << "\tError al borrar correlativa.\n";
}

void ManagerCorrelativa::activar() {
    cout << "\n\t=== Activar Correlativa ===\n";
    int idObj = Validacion::validarEnteroEnRango("\tID Materia Objetivo: ", 1, 9999);
    int pos = _archivo.buscarPorMateriaObjetivo(idObj);
    if (pos < 0) {
        cout << "\tNo se encontró esa correlativa.\n";
        return;
    }

    if (_archivo.activarRegistro(pos))
        cout << "\tCorrelativa activada correctamente.\n";
    else
        cout << "\tError al activar correlativa.\n";
}

bool ManagerCorrelativa::tieneCorrelativas(int idMateria) {
    int total = _archivo.contarRegistros();
    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (c.getIdMateriaObjetivo() == idMateria && !c.getEliminado())
            return true;
    }
    return false;
}
