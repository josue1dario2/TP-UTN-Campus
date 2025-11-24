#include "ManagerCorrelativa.h"
#include "Validacion.h"
#include <iostream>
#include <iomanip>
using namespace std;

ManagerCorrelativa::ManagerCorrelativa()
    : _archivo("Correlativas.dat") {}

bool ManagerCorrelativa::tieneCorrelativas(int idMateria) {
    int total = _archivo.contarRegistros();
    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateriaObjetivo() == idMateria)
            return true;
    }
    return false;
}

bool ManagerCorrelativa::existeCorrelativa(int idMateriaObj, int idMateriaReq) {
    int total = _archivo.contarRegistros();
    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);

        if (!c.getEliminado() &&
            c.getIdMateriaObjetivo() == idMateriaObj &&
            c.getIdMateriaRequisito() == idMateriaReq)
            return true;
    }
    return false;
}

void ManagerCorrelativa::listarTabla() {
    cout << "\n\t=== TABLA DE CORRELATIVAS ===\n";

    int total = _archivo.contarRegistros();
    if (total == 0) {
        cout << "\tNo hay correlativas cargadas.\n";
        return;
    }

    cout << "\t+-----------------+------------------+-----------+\n";
    cout << "\t| Materia Obj. ID | Materia Req. ID  | Activa    |\n";
    cout << "\t+-----------------+------------------+-----------+\n";

    for (int i = 0; i < total; i++) {
        Correlativa c = _archivo.leerRegistro(i);

        cout << "\t| " << setw(15) << c.getIdMateriaObjetivo()
             << " | " << setw(16) << c.getIdMateriaRequisito()
             << " | " << setw(9)  << (c.getEliminado() ? "No" : "Sí")
             << " |\n";
    }

    cout << "\t+-----------------+------------------+-----------+\n";
}
