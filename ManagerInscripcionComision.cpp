#include "ManagerInscripcionComision.h"
#include "Validacion.h"
using namespace std;

ManagerInscripcionComision::ManagerInscripcionComision() {}

void ManagerInscripcionComision::mostrarEncabezado() {
    cout << "\t+-------------+-------------+------------------+----------------------+\n";
    cout << "\t| Legajo Alum | ID Comision | Fecha Inscripción | Estado               |\n";
    cout << "\t+-------------+-------------+------------------+----------------------+\n";
}

void ManagerInscripcionComision::mostrarRegistro(const InscripcionComision& reg) {
    cout << "\t| " << setw(11) << reg.getLegajoAlumno()
         << " | " << setw(11) << reg.getIdComision()
         << " | ";
    reg.getFecha().mostrar();
    cout << " | ";

    if (reg.getEstado() == 0) cout << setw(20) << "Activa";
    else if (reg.getEstado() == 1) cout << setw(20) << "Pendiente de baja";
    else cout << setw(20) << "Baja";

    cout << " |\n";
}

void ManagerInscripcionComision::mostrarPie() {
    cout << "\t+-------------+-------------+------------------+----------------------+\n";
}

void ManagerInscripcionComision::cargar() {
    cout << "\n\t=== Nueva Inscripción a Comisión ===\n";

    int legajo = Validacion::validarEnteroEnRango("\tLegajo Alumno: ", 1, 99999);
    int idComision = Validacion::validarEnteroEnRango("\tID Comisión: ", 1, 99999);

    if (estaInscripto(legajo, idComision)) {
        cout << "\tEl alumno ya está inscripto en esta comisión.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();

    InscripcionComision nueva(legajo, idComision);
    nueva.setFecha(hoy);
    nueva.setEstado(0); // activa por defecto

    if (_archivo.agregarRegistro(nueva))
        cout << "\tInscripción guardada correctamente.\n";
    else
        cout << "\tError al guardar la inscripción.\n";
}

void ManagerInscripcionComision::listar() {
    cout << "\n\t=== Listado de Inscripciones a Comisión ===\n";
    int total = _archivo.contarRegistros();
    if (total == 0) {
        cout << "\tNo hay inscripciones.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; i++) {
        InscripcionComision reg = _archivo.leerRegistro(i);
        // Mostrar solo estado 0 (activa) o 1 (pendiente)
        if (reg.getEstado() != 2)
            mostrarRegistro(reg);
    }
    mostrarPie();
}

void ManagerInscripcionComision::borrar() {
    cout << "\n\t=== Baja Definitiva de Inscripción ===\n";

    int legajo = Validacion::validarEnteroEnRango("\tLegajo Alumno: ", 1, 99999);
    int idComision = Validacion::validarEnteroEnRango("\tID Comisión: ", 1, 99999);

    int pos = _archivo.buscarRegistro(legajo, idComision);

    if (pos >= 0) {
        if (_archivo.bajaDefinitiva(pos))
            cout << "\tInscripción dada de baja definitivamente.\n";
        else
            cout << "\tError al intentar borrar.\n";
    } else {
        cout << "\tNo se encontró inscripción activa o pendiente.\n";
    }
}

bool ManagerInscripcionComision::estaInscripto(int legajo, int idComision) {
    int total = _archivo.contarRegistros();

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivo.leerRegistro(i);

        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            ins.getEstado() != 2)  // activa o pendiente
        {
            return true;
        }
    }

    return false;
}
