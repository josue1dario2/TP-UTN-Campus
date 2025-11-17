#include "DocenteManager.h"
#include <fstream>
#include <iomanip>
using namespace std;

DocenteManager::DocenteManager()
    : _archivoDocentes("Docentes.dat"),
      _archivoComisiones("Comisiones.dat"),
      _archivoInscripciones("InscripcionesComision.dat"),
      _archivoExamen("Examenes.dat"),
      _archivoMaterias("Materias.dat") {}

// --------------------------------------------------
// CRUD básico
// --------------------------------------------------

void DocenteManager::listarDocentes() {
    cout << "\n=== LISTADO DE DOCENTES ===\n";
    _archivoDocentes.listarRegistros();
}

void DocenteManager::mostrarDocentePorLegajo(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos == -1 || pos == -2) {
        cout << "No se encontró un docente con ese legajo.\n";
        return;
    }
    Docente doc = _archivoDocentes.leerRegistro(pos);
    doc.mostrar();
}

void DocenteManager::editarDocente(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos == -1 || pos == -2) {
        cout << "Docente no encontrado.\n";
        return;
    }
    Docente doc = _archivoDocentes.leerRegistro(pos);
    cout << "Editar los datos del docente (actual):\n";
    doc.mostrar();
    cout << "Ingrese nuevos datos:\n";
    doc.cargar();
    _archivoDocentes.modificarRegistro(doc, pos);
    cout << "Datos actualizados correctamente.\n";
}

void DocenteManager::solicitarBaja(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos == -1 || pos == -2) {
        cout << "Docente no encontrado.\n";
        return;
    }
    if (_archivoDocentes.bajaLogica(pos))
        cout << "Baja solicitada correctamente.\n";
    else
        cout << "Error al realizar la baja.\n";
}

// --------------------------------------------------
// Funciones académicas
// --------------------------------------------------

void DocenteManager::verMisComisiones(int legajo) {
    cout << "\n=== MIS COMISIONES ===\n";
    int total = _archivoComisiones.contarRegistros();
    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);
        if (!c.getEliminado()) {
            cout << "ID Comisión: " << c.getIdComision()
                 << " | Materia ID: " << c.getIdMateria()
                 << " | Turno: " << c.getTurno()
                 << " | Modalidad: " << c.getModalidad()
                 << " | Año: " << c.getAnio() << endl;
        }
    }
}

void DocenteManager::verAlumnosDeComision(int idComision) {
    cout << "\n=== ALUMNOS DE LA COMISIÓN " << idComision << " ===\n";
    int total = _archivoInscripciones.contarRegistros();
    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);
        if (ins.getIdComision() == idComision && !ins.getEliminado()) {
            cout << "Legajo alumno: " << ins.getLegajoAlumno() << endl;
        }
    }
}

void DocenteManager::cargarNotasParcialTP(int legajoDocente) {
    int idComision, legajoAlumno, nota, numeroParcial;
    cout << "\nID Comisión: ";
    cin >> idComision;
    cout << "Legajo Alumno: ";
    cin >> legajoAlumno;
    cout << "Número de parcial (1-3): ";
    cin >> numeroParcial;
    cout << "Nota: ";
    cin >> nota;

    _examenManager.cargarParcial(legajoAlumno, idComision, numeroParcial, nota);
}

void DocenteManager::cargarNotasFinal(int legajoDocente) {
    int idComision, legajoAlumno, nota;
    cout << "\nID Comisión: ";
    cin >> idComision;
    cout << "Legajo Alumno: ";
    cin >> legajoAlumno;
    cout << "Nota final: ";
    cin >> nota;

    _examenManager.cargarFinal(legajoAlumno, idComision, nota);
}

void DocenteManager::publicarNotasCursada(int legajoDocente) {
    cout << "\nPublicando notas de cursada...\n";
    cout << "Funcionalidad simulada (pendiente de implementación real)\n";
}

void DocenteManager::cerrarActaCursada(int legajoDocente) {
    cout << "\nCerrando acta de cursada...\n";
    cout << "Funcionalidad simulada (pendiente de implementación real)\n";
}

void DocenteManager::exportarCSV(int legajoDocente) {
    ofstream archivo("comisiones_docente.csv");
    if (!archivo.is_open()) {
        cout << "Error al crear el archivo CSV.\n";
        return;
    }

    archivo << "ID_Comision,ID_Materia,Turno,Modalidad,Anio\n";

    int total = _archivoComisiones.contarRegistros();
    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);
        if (!c.getEliminado()) {
            archivo << c.getIdComision() << ","
                    << c.getIdMateria() << ","
                    << c.getTurno() << ","
                    << c.getModalidad() << ","
                    << c.getAnio() << "\n";
        }
    }
    archivo.close();
    cout << "Archivo CSV exportado correctamente.\n";
}
