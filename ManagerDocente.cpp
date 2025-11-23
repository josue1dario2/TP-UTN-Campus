#include "ManagerDocente.h"
#include <fstream>
#include <iomanip>
using namespace std;

ManagerDocente::ManagerDocente()
    : _archivoDocentes("Docentes.dat"),
      _archivoComisiones("Comisiones.dat"),
      _archivoInscripciones("InscripcionesComision.dat"),
      _archivoExamen("Examenes.dat"),
      _archivoMaterias("Materias.dat") {}

// --------------------------------------------------
// CRUD BÁSICO
// --------------------------------------------------

void ManagerDocente::listarDocentes(bool incluirBorrados) {
    int total = _archivoDocentes.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay docentes registrados.\n";
        return;
    }

    cout << "\n\t=== LISTADO DE DOCENTES ===\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Docente doc = _archivoDocentes.leerRegistro(i);
        if (incluirBorrados || doc.getEliminado()) {
            mostrarRegistro(doc);
        }
    }

    mostrarPie();


}

void ManagerDocente::mostrarDocentePorLegajo(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos == -1 || pos == -2) {
        cout << "\n\tNo se encontró un docente con ese legajo.\n";
        return;
    }
    Docente doc = _archivoDocentes.leerRegistro(pos);
    doc.mostrar();
}

void ManagerDocente::editarDocente(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos == -1 || pos == -2) {
        cout << "\n\tDocente no encontrado.\n";
        return;
    }

    Docente doc = _archivoDocentes.leerRegistro(pos);
    cout << "\n\tDatos actuales del docente:\n";
    doc.mostrar();

    cout << "\n\tIngrese los nuevos datos:\n";
    doc.cargar();

    if (_archivoDocentes.modificarRegistro(doc, pos))
        cout << "\n\tDatos actualizados correctamente.\n";
    else
        cout << "\n\tError al actualizar los datos.\n";
}

void ManagerDocente::solicitarBaja(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos == -1 || pos == -2) {
        cout << "\n\tDocente no encontrado.\n";
        return;
    }

    if (_archivoDocentes.bajaLogica(pos))
        cout << "\n\tBaja solicitada correctamente.\n";
    else
        cout << "\n\tError al realizar la baja.\n";
}

// --------------------------------------------------
// FUNCIONES ACADÉMICAS
// --------------------------------------------------

void ManagerDocente::verMisComisiones(int legajo) {
    cout << "\n\t=== MIS COMISIONES ===\n";
    int total = _archivoComisiones.contarRegistros();
    bool tieneComisiones = false;

    cout << "\t+------------+------------+------------+------------+------------+\n";
    cout << "\t| ID Comisión| ID Materia | Turno      | Modalidad  | Año        |\n";
    cout << "\t+------------+------------+------------+------------+------------+\n";

    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);
        if (!c.getEliminado() && c.getLegajoDocente() == legajo) {
            tieneComisiones = true;
            cout << "\t| " << setw(10) << right << c.getIdComision()
                 << " | " << setw(10) << right << c.getIdMateria()
                 << " | " << setw(10) << left << c.getTurno()
                 << " | " << setw(10) << left << c.getModalidad()
                 << " | " << setw(10) << right << c.getAnio() << " |\n";
        }
    }

    cout << "\t+------------+------------+------------+------------+------------+\n";

    if (!tieneComisiones)
        cout << "\tNo se encontraron comisiones asignadas.\n";
}

void ManagerDocente::verAlumnosDeComision(int idComision) {
    cout << "\n\t=== ALUMNOS DE LA COMISIÓN " << idComision << " ===\n";
    int total = _archivoInscripciones.contarRegistros();
    bool hayAlumnos = false;

    cout << "\t+--------------+--------------+\n";
    cout << "\t| Legajo Alumno| Fecha Inscrip|\n";
    cout << "\t+--------------+--------------+\n";

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);
        if (ins.getIdComision() == idComision && !ins.getEliminado()) {
            hayAlumnos = true;
            cout << "\t| " << setw(12) << right << ins.getLegajoAlumno() << " | ";
            ins.getFecha().mostrar();
            cout << " |\n";
        }
    }

    cout << "\t+--------------+--------------+\n";

    if (!hayAlumnos)
        cout << "\tNo hay alumnos inscriptos en esta comisión.\n";
}

void ManagerDocente::cargarNotasParcialTP(int legajoDocente) {
    int idMateria, legajoAlumno, nota;
    cout << "\n\t=== CARGA DE NOTAS PARCIALES / TP ===\n";
    cout << "\tID Materia: ";
    cin >> idMateria;
    cout << "\tLegajo Alumno: ";
    cin >> legajoAlumno;
    cout << "\tNota (0-10): ";
    cin >> nota;

    _examenManager.cargarParcial(legajoAlumno, idMateria, nota);
}

void ManagerDocente::cargarNotasFinal(int legajoDocente) {
    int idComision, legajoAlumno, nota;
    cout << "\n\t=== CARGA DE NOTAS FINALES ===\n";
    cout << "\tID Comisión: ";
    cin >> idComision;
    cout << "\tLegajo Alumno: ";
    cin >> legajoAlumno;
    cout << "\tNota final (0-10): ";
    cin >> nota;

    _examenManager.cargarFinal(legajoAlumno, idComision, nota);
}

void ManagerDocente::publicarNotasCursada(int legajoDocente) {
    cout << "\n\tPublicando notas de cursada...\n";
    cout << "\tFuncionalidad pendiente de implementación real.\n";
}

void ManagerDocente::cerrarActaCursada(int legajoDocente) {
    cout << "\n\tCerrando acta de cursada...\n";
    cout << "\tFuncionalidad pendiente de implementación real.\n";
}

void ManagerDocente::exportarCSV(int legajoDocente) {
    ofstream archivo("comisiones_docente.csv");
    if (!archivo.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }

    archivo << "ID_Comision,ID_Materia,Turno,Modalidad,Anio\n";

    int total = _archivoComisiones.contarRegistros();
    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);
        if (!c.getEliminado() && c.getLegajoDocente() == legajoDocente) {
            archivo << c.getIdComision() << ","
                    << c.getIdMateria() << ","
                    << c.getTurno() << ","
                    << c.getModalidad() << ","
                    << c.getAnio() << "\n";
        }
    }

    archivo.close();
    cout << "\n\tArchivo CSV exportado correctamente.\n";
}

// --------------------------------------------------
// PRESENTACIÓN EN TABLA
// --------------------------------------------------

void ManagerDocente::mostrarEncabezado() {
    cout << "  +--------+----------+---------------+---------------+---------------------------+-------------+---------+\n";
    cout << "  | Legajo | DNI      | Nombre        | Apellido      | E-mail                    | Teléfono    | Estado  |\n";
    cout << "  +--------+----------+---------------+---------------+---------------------------+-------------+---------+\n";
}

void ManagerDocente::mostrarRegistro(const Docente& doc) {
    cout << "  | " << setw(6) << right << doc.getLegajo()
         << " | " << setw(6) << right << doc.getDni()
         << " | " << setw(13) << left << doc.getNombre()
         << " | " << setw(13) << left << doc.getApellido()
         << " | " << setw(25) << left << doc.getEmail()
         << " | " << setw(11) << left << doc.getTelefono()
         << " | " << setw(7) << left << (doc.getEliminado() ? "Inact." : "Activo")
         << " |\n";

}

void ManagerDocente::mostrarPie() {
    cout << "  +--------+----------+---------------+---------------+---------------------------+-------------+---------+\n";
}
