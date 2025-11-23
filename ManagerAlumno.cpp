#include "ManagerAlumno.h"
#include "ArchivoComision.h"
#include "Validacion.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

ManagerAlumno::ManagerAlumno()
    : _archivoAlumnos("Alumnos.dat"),
      _archivoMaterias("Materias.dat"),
      _archivoInscripcionesComision("InscripcionesComision.dat") {}

// ----------------------------------------------------------
// CRUD BÁSICO DE ALUMNOS
// ----------------------------------------------------------

void ManagerAlumno::registrarAlumno() {
    Alumno nuevo;
    nuevo.cargar();

    int resultadoLegajo = _archivoAlumnos.buscarRegistro(nuevo.getLegajo());
    int resultadoDni = _archivoAlumnos.buscarRegistroPorDni(nuevo.getDni());

    if (resultadoLegajo == -1 || resultadoDni == -1) {
        cout << "\n\tError al acceder al archivo de alumnos.\n";
        return;
    }

    if (resultadoLegajo >= 0 || resultadoDni >= 0) { // encontrado en posición válida
        string mensaje ="\n\tYa existe un alumno con ese ";
        if (resultadoLegajo >= 0 && resultadoDni >= 0) {
            cout << mensaje << "legajo/dni.\n";
            return;
        }
        string resultado = (resultadoLegajo >= 0) ? "legajo.\n" : "dni.\n";
        cout << mensaje << resultado;
        return;
    }

    if (nuevo.getFechaNacimiento() >= nuevo.getFechaIngreso()){
        cout << "\n\tHay un problema con las fechas.";
        return;
    }

    // resultado == -2, no existe, se puede agregar
    if (_archivoAlumnos.agregarRegistro(nuevo)) {
        cout << "\n\tAlumno registrado correctamente.\n";
    } else {
        cout << "\n\tError al guardar el alumno.\n";
    }
}


void ManagerAlumno::modificarAlumno() {
    cout << "\n\t=== MODIFICAR ALUMNO ===\n";
    cout << "\n\tSeleccione modo de búsqueda:\n";
    cout << "\t1) Por Legajo\n";
    cout << "\t2) Por DNI\n";
    cout << "\t0) Cancelar\n";
    int modo = Validacion::validarEnteroEnRango("\n\tOpción: ", 0, 2);
    if (!modo ==0) {

        int pos = -1;
        int legajo = 0;
        int dni = 0;

        if (modo == 1) {
            legajo = Validacion::validarEnteroEnRango("\tIngrese Legajo: ", 1, 100000000);
            pos = _archivoAlumnos.buscarRegistro(legajo);
            if (pos < 0) { // -1 error / -2 no encontrado
                cout << "\tNo se encontró un alumno con ese legajo.\n";
                return;
            }
        } else {
            dni = Validacion::validarEnteroEnRango("\tIngrese DNI: ", 1, 100000000);
            pos = _archivoAlumnos.buscarRegistroPorDni(dni);
            if (pos < 0) {
                cout << "\tNo se encontró un alumno con ese DNI.\n";
                return;
            }
        }

        Alumno original = _archivoAlumnos.leerRegistro(pos);
        cout << "\n\tRegistro actual:\n\n";
        original.mostrar();

        cout << "\tIngrese nuevos datos (se solicitarán todos los campos)\n";
        Alumno actualizado;
        actualizado.cargar();

        int posNuevoLegajo = _archivoAlumnos.buscarRegistro(actualizado.getLegajo());
        if (posNuevoLegajo >= 0 && posNuevoLegajo != pos) {
            cout << "\n\tEl legajo ingresado ya está asignado a otro alumno. Operación cancelada.\n";
            return;
        }
        int posNuevoDNI = _archivoAlumnos.buscarRegistro(actualizado.getDni());
        if (posNuevoDNI >= 0 && posNuevoDNI != pos) {
            cout << "\n\tEl DNI ingresado ya está asignado a otro alumno. Operación cancelada.\n";
            return;
        }
        if (actualizado.getFechaNacimiento() >= actualizado.getFechaIngreso()){
        cout << "\n\tHay un problema con las fechas.";
        return;
        }

        actualizado.setEliminado(original.getEliminado());
        if (Validacion::desearAccionar("")){
            if (_archivoAlumnos.actualizarRegistro(pos, actualizado)) {
            cout << "\n\tAlumno modificado correctamente.\n";
            } else {
            cout << "\n\tError al modificar el alumno.\n";
        }
        }
    }
}


void ManagerAlumno::listarAlumnos(bool incluirBorrados) {
    int total = _archivoAlumnos.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay alumnos registrados.\n";
        return;
    }

    cout << "\n\t=== LISTADO DE ALUMNOS ===\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Alumno alu = _archivoAlumnos.leerRegistro(i);

        if (incluirBorrados || !alu.getEliminado()) {
            mostrarRegistro(alu);
        }
    }

    mostrarPie();

}


void ManagerAlumno::mostrarAlumnoPorLegajo(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "\n\tNo se encontró un alumno con ese legajo.\n";
        return;
    }
    Alumno alu = _archivoAlumnos.leerRegistro(pos);
    alu.mostrar();
}

int ManagerAlumno::buscarAlumno(int legajo) {
    return _archivoAlumnos.buscarRegistro(legajo);
}

// ----------------------------------------------------------
// CONSULTAS ACADÉMICAS
// ----------------------------------------------------------

void ManagerAlumno::mostrarHistorialNotas(int legajo) {
    cout << "\n\t=== HISTORIAL DE NOTAS - Legajo " << legajo << " ===\n";
    _examenManager.mostrarHistorial(legajo);
}

void ManagerAlumno::mostrarMateriasAprobadas(int legajo) {
    cout << "\n\t=== MATERIAS APROBADAS ===\n";
    int total = _archivoMaterias.contarRegistros();

    for (int i = 0; i < total; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);
        if (_examenManager.estaPromocionado(legajo, mat.getIdMateria()) ||
            _examenManager.estaRegular(legajo, mat.getIdMateria())) {
            cout << "\t- " << mat.getNombre() << endl;
        }
    }
}

void ManagerAlumno::mostrarMateriasPendientes(int legajo) {
    cout << "\n\t=== MATERIAS PENDIENTES ===\n";
    int total = _archivoMaterias.contarRegistros();

    for (int i = 0; i < total; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);
        if (_examenManager.estaLibre(legajo, mat.getIdMateria())) {
            cout << "\t- " << mat.getNombre() << endl;
        }
    }
}

void ManagerAlumno::verCondicionMateria(int legajo, int idMateria) {
    cout << "\n\t=== CONDICIÓN ACADÉMICA ===\n";
    _examenManager.recalcularCondicion(legajo, idMateria);
}

// ----------------------------------------------------------
// ACCIONES ACADÉMICAS
// ----------------------------------------------------------

void ManagerAlumno::inscribirseAFinal(int legajo, int idMateria) {
    cout << "\n\t=== INSCRIPCIÓN A EXAMEN FINAL ===\n";

    if (!_examenManager.puedeRendirFinal(legajo, idMateria)) {
        cout << "\tNo cumple los requisitos (debe tener parciales >= 4).\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();
    Examen examen(0, idMateria, legajo, "Final", hoy, false);

    ArchivoExamen archEx("Examenes.dat");
    if (archEx.agregarRegistro(examen))
        cout << "\tInscripción al final realizada correctamente.\n";
    else
        cout << "\tError al registrar la inscripción.\n";
}

void ManagerAlumno::solicitarBaja(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "\n\tAlumno no encontrado.\n";
        return;
    }

    if (_archivoAlumnos.bajaLogica(pos))
        cout << "\n\tAlumno dado de baja correctamente.\n";
    else
        cout << "\n\tError al dar de baja.\n";
}

void ManagerAlumno::reactivarAlumno(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos == -1) {
        cout << "\n\tAlumno no encontrado.\n";
        return;
    }

    if (_archivoAlumnos.activarRegistro(pos))
        cout << "\n\tAlumno reactivado correctamente.\n";
    else
        cout << "\n\tError al reactivar el alumno.\n";
}

// ----------------------------------------------------------
// INSCRIPCIONES A COMISIONES
// ----------------------------------------------------------

void ManagerAlumno::inscribirseAComision(int legajo) {
    ArchivoMateria archMat("Materias.dat");
    ArchivoComision archCom("Comisiones.dat");

    int totalMat = archMat.contarRegistros();
    if (totalMat == 0) {
        cout << "\n\tNo hay materias disponibles.\n";
        return;
    }

    cout << "\n\t=== MATERIAS DISPONIBLES ===\n";
    for (int i = 0; i < totalMat; i++) {
        Materia m = archMat.leerRegistro(i);
        if (!m.getEliminado())
            cout << "\t" << m.getIdMateria() << ") " << m.getNombre() << endl;
    }

    int idMateria;
    cout << "\n\tIngrese el ID de la materia: ";
    cin >> idMateria;

    cout << "\n\t=== COMISIONES DISPONIBLES ===\n";
    int totalCom = archCom.contarRegistros();
    bool hay = false;

    for (int i = 0; i < totalCom; i++) {
        Comision c = archCom.leerRegistro(i);
        if (c.getIdMateria() == idMateria && !c.getEliminado()) {
            cout << "\tID Comisión: " << c.getIdComision()
                 << " | Turno: " << c.getTurno()
                 << " | Docente: " << c.getLegajoDocente() << endl;
            hay = true;
        }
    }

    if (!hay) {
        cout << "\tNo hay comisiones disponibles.\n";
        return;
    }

    int idComision;
    cout << "\n\tIngrese el ID de la comisión: ";
    cin >> idComision;

    // Evitar duplicados
    int totalIns = _archivoInscripcionesComision.contarRegistros();
    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            !ins.getEliminado()) {
            cout << "\tYa estás inscripto en esta comisión.\n";
            return;
        }
    }

    InscripcionComision nueva(legajo, idComision);
    Fecha hoy;
    hoy.cargar();
    nueva.setFecha(hoy);

    if (_archivoInscripcionesComision.agregarRegistro(nueva))
        cout << "\n\tInscripción realizada correctamente.\n";
    else
        cout << "\n\tError al registrar la inscripción.\n";
}

void ManagerAlumno::verMisComisiones(int legajo) {
    int total = _archivoInscripcionesComision.contarRegistros();
    if (total == 0) {
        cout << "\n\tNo hay inscripciones registradas.\n";
        return;
    }

    cout << "\n\t=== COMISIONES INSCRIPTAS ===\n";
    bool hay = false;

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);
        if (ins.getLegajoAlumno() == legajo && !ins.getEliminado()) {
            cout << "\tComisión ID: " << ins.getIdComision() << " | Fecha: ";
            ins.getFecha().mostrar();
            cout << endl;
            hay = true;
        }
    }

    if (!hay)
        cout << "\tNo estás inscripto en ninguna comisión.\n";
}

// ----------------------------------------------------------
// EXÁMENES Y MESAS
// ----------------------------------------------------------

void ManagerAlumno::verMisMesas(int legajo) {
    cout << "\n\t=== MESAS DE EXAMEN FINAL ===\n";
    ArchivoExamen arch("Examenes.dat");
    int total = arch.contarRegistros();
    bool hay = false;

    for (int i = 0; i < total; i++) {
        Examen ex = arch.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajo &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            !ex.getEliminado()) {
            cout << "\tMesa Final - Materia: " << ex.getIdMateria()
                 << " | Fecha: ";
            ex.getFecha().mostrar();
            cout << endl;
            hay = true;
            }
    }

    if (!hay)
        cout << "\tNo estás inscripto en ninguna mesa final.\n";
}


// ----------------------------------------------------------
// PRESENTACIÓN EN TABLA
// ----------------------------------------------------------

void ManagerAlumno::mostrarEncabezado() {
    cout << "  +--------+----------+---------------+---------------+---------------------------+-------------+---------+\n";
    cout << "  | Legajo | DNI      | Nombre        | Apellido      | E-mail                    | Teléfono    | Estado  |\n";
    cout << "  +--------+----------+---------------+---------------+---------------------------+-------------+---------+\n";
}

void ManagerAlumno::mostrarRegistro(const Alumno& alu) {
    cout << "  | " << setw(6) << right << alu.getLegajo()
         << " | " << setw(6) << right << alu.getDni()
         << " | " << setw(13) << left << alu.getNombre()
         << " | " << setw(13) << left << alu.getApellido()
         << " | " << setw(25) << left << alu.getEmail()
         << " | " << setw(11) << left << alu.getTelefono()
         << " | " << setw(7) << left << (alu.getEliminado() ? "Inact." : "Activo")
         << " |\n";
}

void ManagerAlumno::mostrarPie() {
        cout << "  +--------+----------+---------------+---------------+---------------------------+-------------+---------+\n";
}
void ManagerAlumno::bajaInscripcionExamenFinal(int legajo, int idMateria) {
    ArchivoExamen archEx("Examenes.dat");
    int total = archEx.contarRegistros();
    bool encontrado = false;

    for (int i = 0; i < total; i++) {
        Examen ex = archEx.leerRegistro(i);
        if (ex.getLegajoAlumno() == legajo &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            ex.getIdMateria() == idMateria &&
            !ex.getEliminado()) {

            ex.setEliminado(true);
            if (archEx.modificarRegistro(ex, i)) {
                cout << "\n\tBaja del examen final realizada correctamente.\n";
            } else {
                cout << "\n\tError al dar de baja el examen final.\n";
            }
            encontrado = true;
            break;
            }
    }

    if (!encontrado)
        cout << "\n\tNo se encontró un examen final activo para esa materia.\n";
}
