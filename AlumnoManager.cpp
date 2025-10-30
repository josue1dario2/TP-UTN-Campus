#include "AlumnoManager.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

AlumnoManager::AlumnoManager()
    : _archivoAlumnos("Alumnos.dat"),
      _archivoMaterias("Materias.dat") {}

void AlumnoManager::registrarAlumno() {
    Alumno nuevo;
    nuevo.cargar();

    if (_archivoAlumnos.buscarRegistro(nuevo.getLegajo()) != -1) {
        cout << "Ya existe un alumno con ese legajo.\n";
        return;
    }

    if (_archivoAlumnos.agregarRegistro(nuevo)) {
        cout << "Alumno registrado correctamente.\n";
    } else {
        cout << "Error al guardar el alumno.\n";
    }
}

void AlumnoManager::listarAlumnos() {
    cout << "\nLISTADO DE ALUMNOS\n";
    cout << "------------------------------------\n";
    _archivoAlumnos.listarRegistros();
}

void AlumnoManager::mostrarAlumnoPorLegajo(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "No se encontró un alumno con ese legajo.\n";
        return;
    }
    Alumno alu = _archivoAlumnos.leerRegistro(pos);
    alu.mostrar();
}

int AlumnoManager::buscarAlumno(int legajo) {
    return _archivoAlumnos.buscarRegistro(legajo);
}

// ----------------------------------------------------------
// CONSULTAS ACADÉMICAS
// ----------------------------------------------------------

void AlumnoManager::mostrarHistorialNotas(int legajo) {
    cout << "\nHISTORIAL DE NOTAS - Legajo " << legajo << "\n";
    _examenManager.mostrarHistorial(legajo);
}

void AlumnoManager::mostrarMateriasAprobadas(int legajo) {
    cout << "\nMATERIAS APROBADAS - Legajo " << legajo << "\n";
    int totalMaterias = _archivoMaterias.contarRegistros();

    for (int i = 0; i < totalMaterias; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);
        if (_examenManager.estaPromocionado(legajo, mat.getIdMateria()) ||
            _examenManager.estaRegular(legajo, mat.getIdMateria())) {
            cout << mat.getNombre() << endl;
        }
    }
}

void AlumnoManager::mostrarMateriasPendientes(int legajo) {
    cout << "\nMATERIAS PENDIENTES - Legajo " << legajo << "\n";
    int totalMaterias = _archivoMaterias.contarRegistros();

    for (int i = 0; i < totalMaterias; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);
        if (_examenManager.estaLibre(legajo, mat.getIdMateria())) {
            cout << mat.getNombre() << endl;
        }
    }
}

void AlumnoManager::verCondicionMateria(int legajo, int idMateria) {
    cout << "\nCONDICIÓN ACADÉMICA - Legajo " << legajo
         << " | Materia ID: " << idMateria << "\n";
    _examenManager.recalcularCondicion(legajo, idMateria);
}

// ----------------------------------------------------------
// ACCIONES ACADÉMICAS
// ----------------------------------------------------------

void AlumnoManager::inscribirseAFinal(int legajo, int idMateria) {
    cout << "\nINSCRIPCIÓN A EXAMEN FINAL\n";

    if (!_examenManager.puedeRendirFinal(legajo, idMateria)) {
        cout << "No cumple los requisitos para rendir final.\n";
        cout << "Debe tener todos los parciales aprobados (nota >=6).\n";
        return;
    }

    Examen examen;
    examen.setLegajoAlumno(legajo);
    examen.setIdComision(idMateria);
    examen.setTipoExamen(7);
    examen.setNota(-1);
    examen.setCorregido(false);
    examen.setEliminado(false);

    ArchivoExamen archEx("Examenes.dat");
    if (archEx.inscribirExamen(examen)) {
        cout << "Inscripción registrada correctamente.\n";
    } else {
        cout << "No se pudo registrar la inscripción.\n";
    }
}

void AlumnoManager::solicitarBaja(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "Alumno no encontrado.\n";
        return;
    }

    if (_archivoAlumnos.bajaLogica(pos)) {
        cout << "Alumno dado de baja correctamente.\n";
    } else {
        cout << "Error al dar de baja.\n";
    }
}

void AlumnoManager::reactivarAlumno(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "Alumno no encontrado.\n";
        return;
    }

    if (_archivoAlumnos.activarRegistro(pos)) {
        cout << "Alumno reactivado correctamente.\n";
    } else {
        cout << "Error al reactivar el alumno.\n";
    }
}
// ----------------------------------------------------------
// NUEVAS FUNCIONES - OPCIONES 5, 6 Y 7 DEL MENÚ ALUMNO
// ----------------------------------------------------------

void AlumnoManager::verMisComisiones(int legajo) {
    cout << "\nCOMISIONES INSCRIPTAS - Legajo " << legajo << "\n";
    cout << "--------------------------------------\n";

    int total = _archivoInscripciones.contarRegistros();
    bool encontrado = false;

    for (int i = 0; i < total; i++) {
        Inscripcion ins = _archivoInscripciones.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo && !ins.getEliminado()) {
            cout << "Comisión ID: " << ins.getIdComision()
                 << " | Estado: " << ins.getEstado()
                 << " | Fecha: ";
            ins.getFechaInscripcion().mostrar();
            cout << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No hay comisiones activas para este alumno.\n";
}

void AlumnoManager::verMisMesas(int legajo) {
    cout << "\nMESAS DE EXAMEN FINAL - Legajo " << legajo << "\n";
    cout << "--------------------------------------\n";

    ArchivoExamen archivoExamen("Examenes.dat");
    int total = archivoExamen.contarRegistros();
    bool encontrado = false;

    for (int i = 0; i < total; i++) {
        Examen ex = archivoExamen.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajo &&
            ex.getTipoExamen() == 7 &&
            !ex.getEliminado()) {
            cout << "Mesa Final (ID Comisión: " << ex.getIdComision() << ")\n";
            encontrado = true;
            }
    }

    if (!encontrado)
        cout << "No estás inscripto en ninguna mesa final.\n";
}

void AlumnoManager::bajaInscripcionMateria(int legajo, int idComision) {
    cout << "\nDAR DE BAJA INSCRIPCIÓN A MATERIA\n";
    int total = _archivoInscripciones.contarRegistros();

    for (int i = 0; i < total; i++) {
        Inscripcion ins = _archivoInscripciones.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            !ins.getEliminado()) {
            _archivoInscripciones.bajaLogica(i);
            cout << "Inscripción a la comisión " << idComision << " dada de baja.\n";
            return;
        }
    }

    cout << "No se encontró una inscripción activa para esa comisión.\n";
}
void AlumnoManager::bajaInscripcionMesaFinal(int legajo, int idComision) {
    cout << "\nDAR DE BAJA INSCRIPCIÓN A MESA FINAL\n";
    ArchivoExamen archivo("Examenes.dat");
    int total = archivo.contarRegistros();
    bool encontrado = false;

    for (int i = 0; i < total; i++) {
        Examen ex = archivo.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdComision() == idComision &&
            ex.getTipoExamen() == 7 &&
            !ex.getEliminado()) {

            archivo.bajaLogica(i);
            cout << "Inscripción a mesa final (Comisión " << idComision << ") dada de baja.\n";
            encontrado = true;
            break;
            }
    }

    if (!encontrado) {
        cout << "No se encontró una inscripción activa a mesa final para esa comisión.\n";
    }
}
void AlumnoManager::inscribirseAMateria(int legajo, int idComision) {
    cout << "\nINSCRIPCIÓN A MATERIA (COMISIÓN)\n";

    // 1. Verificar que el alumno exista
    int posAlumno = _archivoAlumnos.buscarRegistro(legajo);
    if (posAlumno == -1) {
        cout << "No existe un alumno con ese legajo.\n";
        return;
    }

    // 2. Verificar si ya está inscripto en la comisión
    int total = _archivoInscripciones.contarRegistros();
    for (int i = 0; i < total; i++) {
        Inscripcion ins = _archivoInscripciones.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            !ins.getEliminado()) {
            cout << "Ya estás inscripto en esta comisión.\n";
            return;
            }
    }

    // 3. Crear nueva inscripción
    Inscripcion nueva;
    Fecha hoy;
    hoy.cargar();

    nueva.setIdInscripcion(total + 1);
    nueva.setLegajoAlumno(legajo);
    nueva.setIdComision(idComision);
    nueva.setFechaInscripcion(hoy);
    nueva.setEstado("Regular");
    nueva.setEliminado(false);

    if (_archivoInscripciones.agregarRegistro(nueva)) {
        cout << "Inscripción realizada correctamente.\n";
    } else {
        cout << "Error al registrar la inscripción.\n";
    }
}
