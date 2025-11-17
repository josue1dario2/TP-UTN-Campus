#include "AlumnoManager.h"
#include "ArchivoComision.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

AlumnoManager::AlumnoManager()
    : _archivoAlumnos("Alumnos.dat"),
      _archivoMaterias("Materias.dat"),
      _archivoInscripcionesComision("InscripcionesComision.dat") {}

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
        cout << "Debe tener los parciales aprobados (nota >=4).\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();
    Examen examen(0, idMateria, legajo, "Final", 0, hoy, false);

    ArchivoExamen archEx("Examenes.dat");
    if (archEx.inscribirExamen(examen))
        cout << "Inscripción al final realizada correctamente.\n";
    else
        cout << "No se pudo registrar la inscripción.\n";
}

void AlumnoManager::solicitarBaja(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "Alumno no encontrado.\n";
        return;
    }

    if (_archivoAlumnos.bajaLogica(pos))
        cout << "Alumno dado de baja correctamente.\n";
    else
        cout << "Error al dar de baja.\n";
}

void AlumnoManager::reactivarAlumno(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "Alumno no encontrado.\n";
        return;
    }

    if (_archivoAlumnos.activarRegistro(pos))
        cout << "Alumno reactivado correctamente.\n";
    else
        cout << "Error al reactivar el alumno.\n";
}

// ----------------------------------------------------------
// INSCRIPCIÓN A COMISIONES
// ----------------------------------------------------------

void AlumnoManager::inscribirseAComision(int legajo) {
    ArchivoMateria archMat("Materias.dat");
    ArchivoComision archCom("Comisiones.dat");

    int totalMat = archMat.contarRegistros();
    if (totalMat == 0) {
        cout << "No hay materias disponibles.\n";
        return;
    }

    cout << "\n=== MATERIAS DISPONIBLES ===\n";
    for (int i = 0; i < totalMat; i++) {
        Materia m = archMat.leerRegistro(i);
        if (!m.getEliminado()) {
            cout << m.getIdMateria() << ") " << m.getNombre() << endl;
        }
    }

    int idMateria;
    cout << "\nIngrese el ID de la materia: ";
    cin >> idMateria;

    cout << "\n=== COMISIONES DISPONIBLES ===\n";
    int totalCom = archCom.contarRegistros();
    bool hayComisiones = false;

    for (int i = 0; i < totalCom; i++) {
        Comision c = archCom.leerRegistro(i);
        if (c.getIdMateria() == idMateria && !c.getEliminado()) {
            cout << "ID Comisión: " << c.getIdComision()
                 << " | Turno: " << c.getTurno()
                 << " | Docente: " << c.getLegajoDocente() << endl;
            hayComisiones = true;
        }
    }

    if (!hayComisiones) {
        cout << "No hay comisiones disponibles para esta materia.\n";
        return;
    }

    int idComision;
    cout << "\nIngrese el ID de la comisión a inscribirse: ";
    cin >> idComision;

    // Validar duplicado
    int totalIns = _archivoInscripcionesComision.contarRegistros();
    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            !ins.getEliminado()) {
            cout << "Ya estás inscripto en esta comisión.\n";
            return;
        }
    }

    // Crear nueva inscripción
    InscripcionComision nueva(legajo, idComision);
    Fecha hoy;
    hoy.cargar();
    nueva.setFecha(hoy);

    if (_archivoInscripcionesComision.agregarRegistro(nueva))
        cout << "\nInscripción realizada correctamente.\n";
    else
        cout << "\nError al registrar la inscripción.\n";
}

void AlumnoManager::verMisComisiones(int legajo) {
    int total = _archivoInscripcionesComision.contarRegistros();
    if (total == 0) {
        cout << "No hay inscripciones registradas.\n";
        return;
    }

    cout << "\n=== COMISIONES INSCRIPTAS ===\n";
    bool hay = false;

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo && !ins.getEliminado()) {
            cout << "Comisión ID: " << ins.getIdComision() << " | Fecha: ";
            ins.getFecha().mostrar();
            cout << endl;
            hay = true;
        }
    }

    if (!hay)
        cout << "No estás inscripto en ninguna comisión.\n";
}

void AlumnoManager::bajaInscripcionComision(int legajo, int idComision) {
    int total = _archivoInscripcionesComision.contarRegistros();

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            !ins.getEliminado()) {
            _archivoInscripcionesComision.bajaLogica(i);
            cout << "Inscripción dada de baja correctamente.\n";
            return;
        }
    }

    cout << "No se encontró una inscripción activa para esa comisión.\n";
}

// ----------------------------------------------------------
// EXÁMENES Y MESAS FINALES
// ----------------------------------------------------------

void AlumnoManager::verMisMesas(int legajo) {
    cout << "\n=== MESAS DE EXAMEN FINAL ===\n";
    ArchivoExamen arch("Examenes.dat");
    int total = arch.contarRegistros();
    bool hay = false;

    for (int i = 0; i < total; i++) {
        Examen ex = arch.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajo &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            !ex.getEliminado()) {
            cout << "Mesa Final - Comisión ID: " << ex.getIdComision() << " | Fecha: ";
            ex.getFecha().mostrar();
            cout << endl;
            hay = true;
        }
    }

    if (!hay)
        cout << "No estás inscripto en ninguna mesa de examen final.\n";
}

void AlumnoManager::verMisInscripciones(int legajo) {
    cout << "\n=== INSCRIPCIONES DEL ALUMNO ===\n";
    cout << "1) Comisiones en curso:\n";
    verMisComisiones(legajo);
    cout << "\n2) Exámenes / Mesas finales:\n";
    _examenManager.mostrarHistorial(legajo);
}

void AlumnoManager::bajaInscripcionMesaFinal(int legajo, int idComision) {
    cout << "\nDAR DE BAJA INSCRIPCIÓN A MESA FINAL\n";
    ArchivoExamen arch("Examenes.dat");
    int total = arch.contarRegistros();

    for (int i = 0; i < total; i++) {
        Examen ex = arch.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdComision() == idComision &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            !ex.getEliminado()) {
            arch.bajaLogica(i);
            cout << "Inscripción al examen final dada de baja.\n";
            return;
        }
    }

    cout << "No se encontró una inscripción activa a mesa final para esa comisión.\n";
}
