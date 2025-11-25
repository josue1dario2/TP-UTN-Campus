#include "ManagerAlumno.h"
#include "ArchivoComision.h"
#include "ManagerCorrelativa.h"
#include "Validacion.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

ManagerAlumno::ManagerAlumno()
    : _archivoAlumnos("Alumnos.dat"),
      _archivoMaterias("Materias.dat"),
      _archivoInscripcionesComision("InscripcionesComision.dat")
{}

// ==========================================================
// VALIDACIÓN DE CORRELATIVAS
// ==========================================================

bool ManagerAlumno::cumpleCorrelativas(int legajoAlumno, int idMateriaObjetivo) {

    ManagerCorrelativa mgrCor;               // Usamos el manager (mejor arquitectura)
    ArchivoCorrelativa archCor("Correlativas.dat");
    ArchivoExamen archEx("Examenes.dat");

    // Si no tiene correlativas → puede inscribirse
    if (!mgrCor.tieneCorrelativas(idMateriaObjetivo)) {
        return true;
    }

    int total = archCor.contarRegistros();
    bool ok = true;

    for (int i = 0; i < total; i++) {
        Correlativa c = archCor.leerRegistro(i);

        if (c.getEliminado()) continue;
        if (c.getIdMateriaObjetivo() != idMateriaObjetivo) continue;

        int idReq = c.getIdMateriaRequisito();
        bool aprobada = false;

        // Buscar examen del alumno
        int totalEx = archEx.contarRegistros();
        for (int j = 0; j < totalEx; j++) {
            Examen ex = archEx.leerRegistro(j);

            if (!ex.getEliminado()
                && ex.getLegajoAlumno() == legajoAlumno
                && ex.getIdMateria() == idReq
                && ex.getNota() >= 4) {

                aprobada = true;
                break;
                }
        }

        if (!aprobada) {
            cout << "\nFalta aprobar correlativa obligatoria:";
            cout << "\n   - Debe aprobar la materia ID: " << idReq << "\n";
            ok = false;
        }
    }

    return ok;
}


// ----------------------------------------------------------
// CRUD BÁSICO DE ALUMNOS
// ----------------------------------------------------------

void ManagerAlumno::registrarAlumno() {
    Alumno nuevo;
    nuevo.cargar();

    int resultadoLegajo = _archivoAlumnos.buscarRegistro(nuevo.getLegajo());
    int resultadoDni    = _archivoAlumnos.buscarRegistroPorDni(nuevo.getDni());

    // Eliminado el bloqueo por -1: ahora -2 significa “no existe”, se puede continuar.
    if (resultadoLegajo >= 0 || resultadoDni >= 0) {
        cout << "\n\tYa existe un alumno con ese "
             << ((resultadoLegajo >= 0 && resultadoDni >= 0) ? "legajo/dni.\n"
                 : (resultadoLegajo >= 0 ? "legajo.\n" : "dni.\n"));
        return;
    }

    if (nuevo.getFechaNacimiento() >= nuevo.getFechaIngreso()) {
        cout << "\n\tHay un problema con las fechas.";
        return;
    }

    if (_archivoAlumnos.agregarRegistro(nuevo) == 1) {
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
// INSCRIPCIÓN A EXAMEN FINAL
// ----------------------------------------------------------

void ManagerAlumno::inscribirseAFinal(int legajo, int idMateria) {
    cout << "\n\t=== INSCRIPCIÓN A EXAMEN FINAL ===\n";

    if (!_examenManager.puedeRendirFinal(legajo, idMateria)) {
        cout << "\tNo cumple los requisitos (parciales >= 4).\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();

    // Constructor corregido (nuevo parámetro numeroParcial = 0)
    Examen examen(0, idMateria, legajo, "Final", 0, hoy, false);


    ArchivoExamen archEx("Examenes.dat");

    if (archEx.agregarRegistro(examen))
        cout << "\tInscripción realizada correctamente.\n";
    else
        cout << "\tError al registrar la inscripción.\n";
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

            if (archEx.modificarRegistro(ex, i))
                cout << "\n\tBaja del examen final realizada correctamente.\n";
            else
                cout << "\n\tError al procesar la baja.\n";

            encontrado = true;
            break;
        }
    }

    if (!encontrado)
        cout << "\n\tNo se encontró inscripción activa para esa materia.\n";
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

    int totalIns = _archivoInscripcionesComision.contarRegistros();
    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);

        // Evita duplicados activos o pendientes
        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            ins.getEstado() != 2) {
            cout << "\tYa estás inscripto en esta comisión.\n";
            return;
        }
    }

    InscripcionComision nueva(legajo, idComision);
    Fecha hoy;
    hoy.cargar();
    nueva.setFecha(hoy);
    nueva.setEstado(0); // Activa

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

    cout << "\n\t=== MIS COMISIONES ===\n";

    bool hay = false;

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);

        if (ins.getLegajoAlumno() == legajo && ins.getEstado() != 2) {
            cout << "\tComisión ID: " << ins.getIdComision()
                 << " | Fecha: ";
            ins.getFecha().mostrar();

            if (ins.getEstado() == 0)
                cout << " | Estado: Activa";
            else if (ins.getEstado() == 1)
                cout << " | Estado: Pendiente de baja";

            cout << endl;
            hay = true;
        }
    }

    if (!hay)
        cout << "\tNo estás inscripto en ninguna comisión.\n";
}

// ----------------------------------------------------------
// BAJAS DE COMISIONES
// ----------------------------------------------------------

void ManagerAlumno::solicitarBajaComision(int legajo, int idComision) {
    int pos = _archivoInscripcionesComision.buscarRegistro(legajo, idComision);

    if (pos < 0) {
        cout << "\n\tNo estás inscripto en esta comisión.\n";
        return;
    }

    InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(pos);

    if (ins.getEstado() == 2) {
        cout << "\n\tLa inscripción ya fue dada de baja definitivamente.\n";
        return;
    }

    if (ins.getEstado() == 1) {
        cout << "\n\tYa solicitaste la baja.\n";
        return;
    }

    ins.setEstado(1); // Pendiente de baja

    if (_archivoInscripcionesComision.modificarRegistro(ins, pos))
        cout << "\n\tSolicitud enviada correctamente.\n";
    else
        cout << "\n\tError al solicitar la baja.\n";
}

void ManagerAlumno::bajaInscripcionComision(int legajo, int idComision) {
    int pos = _archivoInscripcionesComision.buscarRegistro(legajo, idComision);

    if (pos < 0) {
        cout << "\n\tInscripción no encontrada.\n";
        return;
    }

    InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(pos);

    if (ins.getEstado() == 2) {
        cout << "\n\tLa inscripción ya se encuentra dada de baja.\n";
        return;
    }

    ins.setEstado(2); // Baja definitiva

    if (_archivoInscripcionesComision.modificarRegistro(ins, pos))
        cout << "\n\tBaja realizada correctamente.\n";
    else
        cout << "\n\tError al procesar la baja.\n";
}

// ----------------------------------------------------------
// MESAS DE EXAMEN
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

            cout << "\tMateria: " << ex.getIdMateria()
                 << " | Fecha: ";
            ex.getFecha().mostrar();
            cout << endl;

            hay = true;
        }
    }

    if (!hay)
        cout << "\tNo estás inscripto en ninguna mesa final.\n";
}
void ManagerAlumno::solicitarBaja(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);

    if (pos == -1 || pos == -2) {
        cout << "\n\tAlumno no encontrado.\n";
        return;
    }

    Alumno alu = _archivoAlumnos.leerRegistro(pos);

    if (alu.getEliminado()) {
        cout << "\n\tEl alumno ya está dado de baja.\n";
        return;
    }

    cout << "\n\t¿CONFIRMAR SOLICITUD DE BAJA? (1=Sí / 0=No): ";
    int opc;
    cin >> opc;

    if (opc != 1) {
        cout << "\n\tOperación cancelada.\n";
        return;
    }

    alu.setEliminado(true);

    if (_archivoAlumnos.modificarRegistro(alu, pos))
        cout << "\n\tSolicitud de baja procesada correctamente.\n";
    else
        cout << "\n\tError al procesar la solicitud.\n";
}


// ----------------------------------------------------------
// PRESENTACIÓN EN TABLA
// ----------------------------------------------------------

void ManagerAlumno::mostrarEncabezado() {
    cout << "\t+--------+---------------------------+---------------------------+-------------+---------+\n";
    cout << "\t| Legajo | Nombre                    | Apellido                  | Teléfono    | Estado  |\n";
    cout << "\t+--------+---------------------------+---------------------------+-------------+---------+\n";
}

void ManagerAlumno::mostrarRegistro(const Alumno& alu) {
    cout << "\t| " << setw(6) << right << alu.getLegajo()
         << " | " << setw(25) << left << alu.getNombre()
         << " | " << setw(25) << left << alu.getApellido()
         << " | " << setw(11) << left << alu.getTelefono()
         << " | " << setw(7) << left << (alu.getEliminado() ? "Baja" : "Activo")
         << " |\n";
}

void ManagerAlumno::mostrarPie() {
    cout << "\t+--------+---------------------------+---------------------------+-------------+---------+\n";
}

void ManagerAlumno::editarDatos(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);

    if (pos == -1) {
        cout << "\n\tAlumno no encontrado.\n";
        return;
    }

    Alumno alu = _archivoAlumnos.leerRegistro(pos);

    if (alu.getEliminado()) {
        cout << "\n\tEl alumno está dado de baja.\n";
        return;
    }

    cout << "\n\t=== EDITAR MIS DATOS ===\n";
    cout << "\n\tDatos actuales:\n";
    alu.mostrar();

    cout << "\n\t¿Qué dato desea modificar?\n";
    cout << "\t1 - Teléfono\n";
    cout << "\t2 - Email\n";
    cout << "\t3 - Dirección\n";
    cout << "\t0 - Cancelar\n";
    cout << "\tOpción: ";

    int opcion;
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
        case 1: {
            char telefono[50];
            cout << "\n\tNuevo teléfono: ";
            cin.getline(telefono, 50);
            alu.setTelefono(telefono);
            break;
        }
        case 2: {
            char email[50];
            cout << "\n\tNuevo email: ";
            cin.getline(email, 50);
            alu.setEmail(email);
            break;
        }
        case 3: {
            Direccion dir;
            cout << "\n\tNueva dirección:\n";
            dir.cargar();
            alu.setDireccion(dir);
            break;
        }
        case 0:
            cout << "\n\tOperación cancelada.\n";
            return;
        default:
            cout << "\n\tOpción inválida.\n";
            return;
    }

    if (_archivoAlumnos.modificarRegistro(alu, pos)) {
        cout << "\n\t✓ Datos actualizados correctamente.\n";
    } else {
        cout << "\n\t✗ Error al actualizar los datos.\n";
    }
}
