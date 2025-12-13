#include <limits>
#include "ManagerAlumno.h"
#include "ArchivoComision.h"
#include "ArchivoDocente.h"
#include "ManagerCorrelativa.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
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

    // Carga sin pedir legajo
    nuevo.cargarDatosSinLegajo();

    // Generar legajo automático
    int nuevoLegajo = generarLegajo();
    if (nuevoLegajo == -1) return;

    nuevo.setLegajo(nuevoLegajo);
    cout << "\n\tLegajo asignado automáticamente: " << nuevoLegajo << "\n";

    // Validar DNI repetido
    if (_archivoAlumnos.buscarRegistroPorDni(nuevo.getDni()) >= 0) {
        cout << "\n\tERROR: Ya existe un alumno con ese DNI.\n";
        return;
    }

    // Validar fechas
    if (nuevo.getFechaNacimiento() >= nuevo.getFechaIngreso()) {
        cout << "\n\tERROR: La fecha de nacimiento no puede ser posterior a la de ingreso.\n";
        return;
    }

    // Guardar
    if (_archivoAlumnos.agregarRegistro(nuevo))
        cout << "\n\tAlumno registrado correctamente.\n";
    else
        cout << "\n\tERROR al guardar el alumno.\n";
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

    // Preguntar si quiere incluir inactivos
    char opc;
    cout << "\n\t¿Desea incluir alumnos inactivos? (s/n): ";
    cin >> opc;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool incluirInactivos = (opc == 's' || opc == 'S');

    cout << "\n\t=== LISTADO DE ALUMNOS ===\n";

    mostrarEncabezado();

    bool hayDatos = false;

    for (int i = 0; i < total; i++) {
        Alumno alu = _archivoAlumnos.leerRegistro(i);

        if (!incluirInactivos && alu.getEliminado())
            continue;

        mostrarRegistro(alu);
        hayDatos = true;
    }

    mostrarPie();

    if (!hayDatos) {
        if (incluirInactivos)
            cout << "\n\tNo hay alumnos registrados (ni activos ni inactivos).\n";
        else
            cout << "\n\tNo hay alumnos ACTIVOS registrados.\n";
    }
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

    ArchivoExamen   archEx("Examenes.dat");
    ArchivoMateria  archMat("Materias.dat");
    ArchivoComision archCom("Comisiones.dat");
    ArchivoDocente  archDoc("Docentes.dat");
    ArchivoAlumno   archAlu("Alumnos.dat");

    // ============================
    // DATOS DEL ALUMNO
    // ============================
    int posAlu = archAlu.buscarRegistro(legajo);
    Alumno alu = archAlu.leerRegistro(posAlu);

    string nombre   = quitarAcentos(alu.getNombre());
    string apellido = quitarAcentos(alu.getApellido());

    // ============================
    // TÍTULO CENTRADO
    // ============================
    string titulo = "HISTORIAL DE EXAMENES - " +
                    nombre + " " + apellido +
                    " - Legajo " + to_string(legajo);

    int ancho = 111;
    int espacios = (ancho - (int)titulo.length()) / 2;

    cout << string(ancho, '=') << "\n";
    cout << string(espacios, ' ') << titulo << "\n";
    cout << string(ancho, '=') << "\n\n";

    // ============================
    // ENCABEZADO TABLA
    // ============================
    cout << left
         << setw(40) << "Materia"
         << setw(18) << "Tipo"
         << setw(16) << "Fecha"
         << setw(15) << "Nota"
         << setw(22) << "Profesor"
         << "\n";

    cout << string(ancho, '-') << "\n";

    int total = archEx.contarRegistros();
    bool hay = false;

    // ============================
    // RECORRER EXÁMENES
    // ============================
    for (int i = 0; i < total; i++) {

        Examen ex = archEx.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajo) continue;
        if (ex.getEliminado()) continue;

        hay = true;

        // ---- MATERIA ----
        int posMat = archMat.buscarRegistro(ex.getIdMateria());
        Materia mat = archMat.leerRegistro(posMat);
        string nombreMat = quitarAcentos(mat.getNombre());

        // ---- TIPO ----
        string tipo = ex.getTipo();
        if (strcmp(ex.getTipo(), "Parcial") == 0 ||
            strcmp(ex.getTipo(), "Recuperatorio") == 0)
        {
            tipo += " (" + to_string(ex.getNumeroParcial()) + ")";
        }

        // ---- NOTA ----
        string notaStr = ex.getCorregido() ? to_string(ex.getNota())
                                           : "Pendiente";

        // ---- FECHA ----
        Fecha f = ex.getFecha();
        char fechaStr[11];
        sprintf(fechaStr, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());

        // ============================================
        // BUSCAR PROFESOR (mostrar nombre + id)
        // ============================================
        string profesor = "N/A";

        int totalCom = archCom.contarRegistros();
        for (int j = 0; j < totalCom; j++) {

            Comision com = archCom.leerRegistro(j);

            if (!com.getEliminado() && com.getIdMateria() == ex.getIdMateria()) {

                int posDoc = archDoc.buscarRegistro(com.getLegajoDocente());
                if (posDoc >= 0) {
                    Docente doc = archDoc.leerRegistro(posDoc);

                    string nombreProf = string(doc.getNombre()) + " " + doc.getApellido();
                    nombreProf = quitarAcentos(nombreProf.c_str());

                    // 💥 Concatenar ID real del docente
                    profesor = nombreProf + " (" + to_string(doc.getLegajo()) + ")";
                }
                break;
            }
        }

        // ============================
        // MOSTRAR FILA
        // ============================
        cout << left
             << setw(40) << nombreMat
             << setw(18) << tipo
             << setw(16) << fechaStr
             << setw(15) << notaStr
             << setw(22) << profesor
             << "\n";
    }

    if (!hay) {
        cout << "\nNo se encontraron examenes registrados.\n";
    }

    cout << string(ancho, '-') << "\n";
}


void ManagerAlumno::mostrarMateriasAprobadas(int legajo) {
    cout << "\n\t=== MATERIAS APROBADAS ===\n";

    int totalMat = _archivoMaterias.contarRegistros();
    bool hay = false;

    for (int i = 0; i < totalMat; i++) {

        Materia mat = _archivoMaterias.leerRegistro(i);
        int idMateria = mat.getIdMateria();

        bool promo = _examenManager.estaPromocionado(legajo, idMateria);
        bool finalOk = _examenManager.finalAprobado(legajo, idMateria);

        // Solo mostrar si está realmente aprobada
        if (!promo && !finalOk) continue;

        hay = true;

        cout << "\t- " << mat.getNombre() << "  -->  ";

        // =====================================
        // 1) PROMOCIONADO
        // =====================================
        if (promo) {
            float prom = _examenManager.promedioConReglas(legajo, idMateria);
            cout << "PROMOCIONADO (Promedio: " << prom << ")";
            cout << endl;
            continue;
        }

        // =====================================
        // 2) FINAL APROBADO
        // =====================================
        ArchivoExamen arch("Examenes.dat");
        int totalEx = arch.contarRegistros();

        for (int e = 0; e < totalEx; e++) {
            Examen ex = arch.leerRegistro(e);

            if (ex.getLegajoAlumno() == legajo &&
                ex.getIdMateria() == idMateria &&
                strcmp(ex.getTipo(), "Final") == 0 &&
                ex.getNota() >= 4)
            {
                cout << "FINAL APROBADO (Nota: " << ex.getNota() << ")";
                break;
            }
        }

        cout << endl;
    }

    if (!hay) {
        cout << "\n\tNo tienes materias aprobadas.\n";
    }
}


void ManagerAlumno::mostrarMateriasPendientes(int legajo) {

    cout << "\n\t=== MATERIAS PENDIENTES ===\n";

    ArchivoInscripcionComision archIns("InscripcionesComision.dat");
    ArchivoComision archCom("Comisiones.dat");
    ArchivoMateria archMat("Materias.dat");

    int totalIns = archIns.contarRegistros();
    bool hay = false;

    for (int i = 0; i < totalIns; i++) {

        InscripcionComision ic = archIns.leerRegistro(i);

        if (ic.getLegajoAlumno() != legajo || ic.getEstado() != 0)
            continue;

        int posCom = archCom.buscarRegistro(ic.getIdComision());
        if (posCom < 0) continue;

        Comision com = archCom.leerRegistro(posCom);
        int idMateria = com.getIdMateria();

        // ---- Si está promocionado, NO es pendiente ----
        if (_examenManager.estaPromocionado(legajo, ic.getIdComision()))
            continue;

        // ---- Si aprobó el final, NO es pendiente ----
        if (_examenManager.finalAprobado(legajo, idMateria))
            continue;

        // ---- Caso contrario, es materia pendiente ----
        int posMat = archMat.buscarRegistro(idMateria);
        if (posMat >= 0) {
            Materia m = archMat.leerRegistro(posMat);
            cout << "\t- " << quitarAcentos(m.getNombre()) << endl;
            hay = true;
        }
    }

    if (!hay)
        cout << "\n\tNo tienes materias pendientes.\n";
}


void ManagerAlumno::verCondicionMateria(int legajo, int idMateria) {
    cout << "\n\t=== CONDICIÓN ACADÉMICA ===\n";
    _examenManager.recalcularCondicion(legajo, idMateria);
}


int ManagerAlumno::buscarComisionDelAlumno(int legajoAlumno, int idMateria) {
    ArchivoInscripcionComision archIns;
    ArchivoComision archCom;

    int total = archIns.contarRegistros();

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = archIns.leerRegistro(i);

        if (ins.getLegajoAlumno() == legajoAlumno && ins.getEstado() == 0) {

            int posCom = archCom.buscarRegistro(ins.getIdComision());
            if (posCom >= 0) {
                Comision c = archCom.leerRegistro(posCom);

                if (c.getIdMateria() == idMateria) {
                    return c.getIdComision();
                }
            }
        }
    }
    return -1;
}

// ----------------------------------------------------------
// INSCRIPCIÓN A EXAMEN FINAL
// ----------------------------------------------------------


void ManagerAlumno::inscribirseAFinal(int legajo, int idMateria) {
    cout << "\n\t=== INSCRIPCIÓN A EXAMEN FINAL ===\n";

    int idComision = buscarComisionDelAlumno(legajo, idMateria);

    if (idComision < 0) {
        cout << "\tERROR: No estás inscripto en ninguna comisión de esta materia.\n";
        return;
    }

    if (!_examenManager.puedeRendirFinal(legajo, idComision)) {
        cout << "\tNo cumple los requisitos para rendir final.\n";
        return;
    }

    Fecha hoy;
    hoy.cargar();

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
    ArchivoDocente archDoc("Docentes.dat");

    int totalMat = archMat.contarRegistros();
    if (totalMat == 0) {
        cout << "\n\tNo hay materias disponibles.\n";
        return;
    }

    // ======================================================
    // MOSTRAR MATERIAS DISPONIBLES (quitar acentos OK)
    // ======================================================
    cout << "\n\t=== MATERIAS DISPONIBLES ===\n";
    for (int i = 0; i < totalMat; i++) {
        Materia m = archMat.leerRegistro(i);
        if (!m.getEliminado())
            cout << "\t" << m.getIdMateria()
                 << ") " << quitarAcentos(m.getNombre()) << endl;
    }

    int idMateria;
    cout << "\n\tIngrese el ID de la materia: ";
    cin >> idMateria;

    // ======================================================
    // COMISIONES EN TABLA
    // ======================================================
    cout << "\n\t=== COMISIONES DISPONIBLES PARA LA MATERIA ===\n\n";

    cout << "\t+------------+------------+-------------+-------------------------+----------------------+\n";
    cout << "\t| ID COMISION| ID MATERIA |   TURNO     |       MODALIDAD         |     DOCENTE          |\n";
    cout << "\t+------------+------------+-------------+-------------------------+----------------------+\n";

    int totalCom = archCom.contarRegistros();
    bool hay = false;

    for (int i = 0; i < totalCom; i++) {
        Comision c = archCom.leerRegistro(i);

        if (c.getIdMateria() == idMateria && !c.getEliminado()) {
            hay = true;

            // === DOCENTE ===
            string nombreDoc = "N/A";
            int posDoc = archDoc.buscarRegistro(c.getLegajoDocente());
            if (posDoc >= 0) {
                Docente d = archDoc.leerRegistro(posDoc);

                string nombreApellido = string(d.getNombre()) + " " + d.getApellido();
                nombreDoc = quitarAcentos(nombreApellido.c_str());
            }

            string turno     = quitarAcentos(c.getTurno());
            string modalidad = quitarAcentos(c.getModalidad());

            cout << "\t| " << setw(10) << left << c.getIdComision()
                 << " | " << setw(10) << left << c.getIdMateria()
                 << " | " << setw(11) << left << turno
                 << " | " << setw(23) << left << modalidad
                 << " | " << setw(20) << left << nombreDoc
                 << " |\n";
        }
    }

    cout << "\t+------------+------------+-------------+-------------------------+----------------------+\n";

    if (!hay) {
        cout << "\n\tNo hay comisiones disponibles para esta materia.\n";
        return;
    }

    // ======================================================
    // VALIDAR ID COMISIÓN
    // ======================================================
    int idComision;
    cout << "\n\tIngrese el ID de la comisión: ";
    cin >> idComision;

    int posSel = archCom.buscarRegistro(idComision);
    if (posSel < 0) {
        cout << "\n\tERROR: La comisión no existe.\n";
        return;
    }

    Comision cSel = archCom.leerRegistro(posSel);

    if (cSel.getIdMateria() != idMateria) {
        cout << "\n\tERROR: Esa comisión NO pertenece a la materia seleccionada.\n";
        return;
    }

    // ======================================================
    // VALIDAR QUE NO ESTÉ INSCRIPTO
    // ======================================================
    int totalIns = _archivoInscripcionesComision.contarRegistros();
    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripcionesComision.leerRegistro(i);

        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            ins.getEstado() != 2) {
            cout << "\n\tERROR: Ya estás inscripto en esta comisión.\n";
            return;
        }
    }

    // ======================================================
    // CREAR INSCRIPCIÓN
    // ======================================================
    InscripcionComision nueva(legajo, idComision);
    Fecha hoy;
    hoy.cargar();
    nueva.setFecha(hoy);
    nueva.setEstado(0);

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

    clearScreen();
    cout << "\n=== MESAS DE EXAMEN FINAL ===\n\n";

    ArchivoExamen   archEx("Examenes.dat");
    ArchivoMateria  archMat("Materias.dat");
    ArchivoComision archCom("Comisiones.dat");
    ArchivoDocente  archDoc("Docentes.dat");

    int total = archEx.contarRegistros();
    bool hay = false;

    // ============================
    // ENCABEZADO DE TABLA
    // ============================
    cout << "+--------+----------------------------------------+--------------+----------------------+--------------+\n";
    cout << "| OPCION |                MATERIA                 |  COMISION    |       PROFESOR       |    FECHA     |\n";
    cout << "+--------+----------------------------------------+--------------+----------------------+--------------+\n";

    int opcion = 1;

    for (int i = 0; i < total; i++) {

        Examen ex = archEx.leerRegistro(i);

        // Mostrar solo finales no eliminados
        if (ex.getLegajoAlumno() != legajo) continue;
        if (strcmp(ex.getTipo(), "Final") != 0) continue;
        if (ex.getEliminado()) continue;

        hay = true;

        // ============================
        // MATERIA
        // ============================
        string matNombre = "N/A";
        int posMat = archMat.buscarRegistro(ex.getIdMateria());
        if (posMat >= 0) {
            Materia m = archMat.leerRegistro(posMat);
            matNombre = quitarAcentos(m.getNombre());
        }

        // ============================
        // COMISIÓN & PROFESOR
        // ============================
        int idComision = -1;
        string profesor = "N/A";

        int totalCom = archCom.contarRegistros();
        for (int c = 0; c < totalCom; c++) {
            Comision cm = archCom.leerRegistro(c);

            if (!cm.getEliminado() && cm.getIdMateria() == ex.getIdMateria()) {

                idComision = cm.getIdComision();

                int posDoc = archDoc.buscarRegistro(cm.getLegajoDocente());
                if (posDoc >= 0) {
                    Docente d = archDoc.leerRegistro(posDoc);

                    profesor = quitarAcentos(
                        (string(d.getNombre()) + " " + d.getApellido()).c_str()
                    );
                    profesor += " (" + to_string(d.getLegajo()) + ")";
                }

                break;
            }
        }

        // ============================
        // FECHA
        // ============================
        Fecha f = ex.getFecha();
        char fechaStr[12];
        sprintf(fechaStr, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());

        cout << "| " << setw(6) << left << opcion
             << " | " << setw(38) << left << matNombre
             << " | " << setw(12) << left << idComision
             << " | " << setw(20) << left << profesor
             << " | " << setw(12) << left << fechaStr
             << " |\n";

        opcion++;
    }

    cout << "+--------+----------------------------------------+--------------+----------------------+--------------+\n";

    if (!hay)
        cout << "\nNo estás inscripto en ninguna mesa final.\n";

    pauseScreen();
}

bool ManagerAlumno::solicitarBaja(int legajo) {
    int pos = _archivoAlumnos.buscarRegistro(legajo);

    if (pos == -1 || pos == -2) {
        cout << "\n\tAlumno no encontrado.\n";
        return false;
    }

    Alumno alu = _archivoAlumnos.leerRegistro(pos);

    if (alu.getEliminado()) {
        cout << "\n\tEl alumno ya está dado de baja.\n";
        return false;
    }

    cout << "\n\t¿CONFIRMAR SOLICITUD DE BAJA? (1=Sí / 0=No): ";
    int opc;
    cin >> opc;

    if (opc != 1) {
        cout << "\n\tOperación cancelada.\n";
        return false;
    }

    alu.setEliminado(true);

    if (_archivoAlumnos.modificarRegistro(alu, pos)) {
        cout << "\n\tSolicitud de baja procesada correctamente.\n";
        return true;
    } else {
        cout << "\n\tError al procesar la solicitud.\n";
        return false;
    }
}



// ----------------------------------------------------------
// PRESENTACIÓN EN TABLA
// ----------------------------------------------------------
void ManagerAlumno::mostrarEncabezado() {
    cout << "\t+--------+---------------------------+---------------------------+--------------------+---------+\n";
    cout << "\t| Legajo | Nombre                    | Apellido                  | Telefono           | Estado  |\n";
    cout << "\t+--------+---------------------------+---------------------------+--------------------+---------+\n";
}

void ManagerAlumno::mostrarRegistro(const Alumno& alu) {

    string nombre   = quitarAcentos(alu.getNombre());
    string apellido = quitarAcentos(alu.getApellido());

    cout << "\t| " << setw(6) << right << alu.getLegajo()
         << " | " << setw(25) << left << nombre
         << " | " << setw(25) << left << apellido
         << " | " << setw(18) << left << alu.getTelefono()
         << " | " << setw(7) << left << (alu.getEliminado() ? "Baja" : "Activo")
         << " |\n";
}

void ManagerAlumno::mostrarPie() {
    cout << "\t+--------+---------------------------+---------------------------+--------------------+---------+\n";

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
    cout << "\t1 - DNI\n";
    cout << "\t2 - Nombre\n";
    cout << "\t3 - Apellido\n";
    cout << "\t4 - Teléfono\n";
    cout << "\t5 - Email\n";
    cout << "\t6 - Dirección\n";
    cout << "\t7 - Fecha de Nacimiento\n";
    cout << "\t8 - Fecha de Ingreso\n";
    cout << "\t0 - Cancelar\n";
    cout << "\tOpción: ";

    int opcion;
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
        case 1: {
            int dni;
            cout << "\n\tNuevo DNI: ";
            cin >> dni;
            cin.ignore();
            alu.setDni(dni);
            break;
        }
        case 2: {
            char nombre[50];
            cout << "\n\tNuevo nombre: ";
            cin.getline(nombre, 50);
            alu.setNombre(nombre);
            break;
        }
        case 3: {
            char apellido[50];
            cout << "\n\tNuevo apellido: ";
            cin.getline(apellido, 50);
            alu.setApellido(apellido);
            break;
        }
        case 4: {
            char telefono[50];
            cout << "\n\tNuevo teléfono: ";
            cin.getline(telefono, 50);
            alu.setTelefono(telefono);
            break;
        }
        case 5: {
            char email[50];
            cout << "\n\tNuevo email: ";
            cin.getline(email, 50);
            alu.setEmail(email);
            break;
        }
        case 6: {
            Direccion dir;
            cout << "\n\tNueva dirección:\n";
            dir.cargar();
            alu.setDireccion(dir);
            break;
        }
        case 7: {
            Fecha fechaNac;
            cout << "\n\tNueva fecha de nacimiento:\n";
            fechaNac.cargar();
            alu.setFechaNacimiento(fechaNac);
            break;
        }
        case 8: {
            Fecha fechaIng;
            cout << "\n\tNueva fecha de ingreso:\n";
            fechaIng.cargar();
            alu.setFechaIngreso(fechaIng);
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
int ManagerAlumno::generarLegajo() {
    int total = _archivoAlumnos.contarRegistros();
    int maxLegajo = 999;

    for (int i = 0; i < total; i++) {
        Alumno a = _archivoAlumnos.leerRegistro(i);
        if (a.getLegajo() > maxLegajo) {
            maxLegajo = a.getLegajo();
        }
    }

    int nuevo = maxLegajo + 1;

    if (nuevo > 9999) {
        cout << "\nERROR: Se alcanzó el límite máximo de legajos (9999).\n";
        return -1;
    }

    return nuevo;
}
void ManagerAlumno::borrarDefinitivo() {
    cout << "\nIngrese legajo del alumno a borrar definitivamente: ";
    int legajo;
    cin >> legajo;

    int total = _archivoAlumnos.contarRegistros();
    int pos = -1;
    Alumno encontradoAlu;

    for (int i = 0; i < total; i++) {
        Alumno a = _archivoAlumnos.leerRegistro(i);
        if (a.getLegajo() == legajo) {
            pos = i;
            encontradoAlu = a;
            break;
        }
    }

    if (pos == -1) {
        cout << "\nNo existe un alumno con ese legajo.\n";
        return;
    }

    cout << "\nATENCIÓN: Está a punto de borrar DEFINITIVAMENTE al alumno:\n";
    cout << "  Nombre: " << encontradoAlu.getNombre() << " " << encontradoAlu.getApellido() << endl;
    cout << "  Legajo: " << encontradoAlu.getLegajo() << endl;

    cout << "\n¿Está seguro que desea BORRAR este registro? (S/N): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'S' && confirm != 's') {
        cout << "\nOperación cancelada. No se borró ningún registro.\n";
        return;
    }

    ArchivoAlumno temp("Alumnos_temp.dat");

    for (int i = 0; i < total; i++) {
        if (i == pos) continue;
        Alumno a = _archivoAlumnos.leerRegistro(i);
        temp.agregarRegistro(a);
    }

    remove("Alumnos.dat");
    rename("Alumnos_temp.dat", "Alumnos.dat");

    cout << "\nAlumno borrado DEFINITIVAMENTE.\n";
}
void ManagerAlumno::inscribirseAParcial(int legajoAlumno) {

    clearScreen();
    cout << "\n=== INSCRIPCION A PARCIAL ===\n\n";

    ArchivoInscripcionComision archIns;
    ArchivoComision archCom;
    ArchivoMateria archMat;
    ArchivoDocente archDoc;
    ArchivoExamen archEx;

    int totalIns = archIns.contarRegistros();

    // ========================================
    // ARREGLO DINÁMICO para comisiones válidas
    // ========================================
    int* comisionesValidas = new int[totalIns];
    int cantCom = 0;

    cout << "=== COMISIONES DONDE ESTAS INSCRIPTO ===\n\n";

    cout << "+--------+------------------------------------------+--------------+--------------+------------------------+\n";
    cout << "| OPCION |                  MATERIA                 |    TURNO     |  MODALIDAD   |        DOCENTE         |\n";
    cout << "+--------+------------------------------------------+--------------+--------------+------------------------+\n";

    bool hay = false;

    for (int i = 0; i < totalIns; i++) {

        InscripcionComision ic = archIns.leerRegistro(i);
        if (ic.getLegajoAlumno() != legajoAlumno || ic.getEstado() == 2)
            continue;

        int posCom = archCom.buscarRegistro(ic.getIdComision());
        if (posCom < 0) continue;

        Comision c = archCom.leerRegistro(posCom);

        // ------ materia ------
        string nombreMat = "N/A";
        int posMat = archMat.buscarRegistro(c.getIdMateria());
        if (posMat >= 0) {
            Materia m = archMat.leerRegistro(posMat);
            nombreMat = quitarAcentos(m.getNombre());
        }

        // ------ docente ------
        string docente = "N/A";
        int posDoc = archDoc.buscarRegistro(c.getLegajoDocente());
        if (posDoc >= 0) {
            Docente d = archDoc.leerRegistro(posDoc);
            docente = quitarAcentos((string(d.getNombre()) + " " + d.getApellido() +
                                    " (" + to_string(d.getLegajo()) + ")").c_str());
        }

        int opcion = cantCom + 1;
        comisionesValidas[cantCom] = c.getIdComision();
        cantCom++;

        cout << "| " << setw(6) << left << opcion
             << " | " << setw(40) << left << nombreMat
             << " | " << setw(12) << left << quitarAcentos(c.getTurno())
             << " | " << setw(12) << left << quitarAcentos(c.getModalidad())
             << " | " << setw(22) << left << docente
             << " |\n";

        hay = true;
    }

    cout << "+--------+------------------------------------------+--------------+--------------+------------------------+\n";

    if (!hay) {
        delete[] comisionesValidas;
        cout << "\nNo estas inscripto en ninguna comision.\n";
        return;
    }

    int seleccion = Validacion::validarEntero("\nIngrese numero de opcion: ");

    if (seleccion < 1 || seleccion > cantCom) {
        delete[] comisionesValidas;
        cout << "\nERROR: Opcion invalida.\n";
        return;
    }

    int idComision = comisionesValidas[seleccion - 1];
    delete[] comisionesValidas;

    int posC = archCom.buscarRegistro(idComision);
    if (posC < 0) {
        cout << "\nERROR: Comision no encontrada.\n";
        return;
    }

    Comision com = archCom.leerRegistro(posC);
    int idMateria = com.getIdMateria();


    // ======================================================
    // BUSCAR PARCIALES Y RECUPERATORIOS DEL ALUMNO
    // ======================================================
    bool tieneP1 = false, tieneP2 = false;
    bool corrP1 = false, corrP2 = false;
    int notaP1 = -1, notaP2 = -1;

    bool recu1Rendido = false;
    bool recu2Rendido = false;

    int totalEx = archEx.contarRegistros();

    for (int i = 0; i < totalEx; i++) {
        Examen ex = archEx.leerRegistro(i);

        if (ex.getLegajoAlumno() != legajoAlumno ||
            ex.getIdMateria() != idMateria ||
            ex.getEliminado())
            continue;

        if (strcmp(ex.getTipo(), "Parcial") == 0) {
            if (ex.getNumeroParcial() == 1) {
                tieneP1 = true;
                corrP1 = ex.getCorregido();
                notaP1 = ex.getNota();
            }
            if (ex.getNumeroParcial() == 2) {
                tieneP2 = true;
                corrP2 = ex.getCorregido();
                notaP2 = ex.getNota();
            }
        }

        if (strcmp(ex.getTipo(), "Recuperatorio") == 0 && ex.getCorregido()) {
            if (ex.getNumeroParcial() == 1) recu1Rendido = true;
            if (ex.getNumeroParcial() == 2) recu2Rendido = true;
        }
    }


    // ======================================================
    // DETERMINAR QUE PUEDE RENDIR
    // ======================================================

    const char* tipo = "";
    int numero = 0;

    if (!tieneP1) {
        tipo = "Parcial";
        numero = 1;
        cout << "\nTe puedes inscribir a PARCIAL 1.\n";
    }
    else if (tieneP1 && corrP1 && !tieneP2) {
        tipo = "Parcial";
        numero = 2;
        cout << "\nTe puedes inscribir a PARCIAL 2.\n";
    }
    else if (corrP1 && corrP2) {

        if (notaP1 < 4) {
            if (recu1Rendido) {
                cout << "\nYa rendiste RECUPERATORIO 1.\n";
                return;
            }
            tipo = "Recuperatorio";
            numero = 1;
            cout << "\nTe puedes inscribir a RECUPERATORIO 1.\n";
        }
        else if (notaP2 < 4) {
            if (recu2Rendido) {
                cout << "\nYa rendiste RECUPERATORIO 2.\n";
                return;
            }
            tipo = "Recuperatorio";
            numero = 2;
            cout << "\nTe puedes inscribir a RECUPERATORIO 2.\n";
        }
        else {
            cout << "\nNo tienes parciales pendientes. Puedes rendir FINAL.\n";
            return;
        }
    }
    else {
        cout << "\nNo tienes evaluaciones disponibles.\n";
        return;
    }


    // ======================================================
    // CREAR EXAMEN
    // ======================================================

    Examen nuevo;
    nuevo.setIdExamen(totalEx + 1);
    nuevo.setIdMateria(idMateria);
    nuevo.setLegajoAlumno(legajoAlumno);
    nuevo.setTipo(tipo);
    nuevo.setNumeroParcial(numero);
    nuevo.setNota(-1);
    nuevo.setCorregido(false);

    // Fecha
    int mes, dia;
    cout << "\nIngrese mes (1-12): ";
    cin >> mes;
    cout << "Ingrese dia (1-31): ";
    cin >> dia;

    Fecha f;
    f.setDia(dia);
    f.setMes(mes);
    f.setAnio(com.getAnio());

    nuevo.setFecha(f);

    if (archEx.agregarRegistro(nuevo))
        cout << "\nInscripcion realizada correctamente.\n";
    else
        cout << "\nError al guardar la inscripcion.\n";
}


void ManagerAlumno::mostrarMateriasHabilitadasFinal(int legajoAlumno) {

    ArchivoInscripcionComision archIns("InscripcionesComision.dat");
    ArchivoComision archCom("Comisiones.dat");
    ArchivoMateria archMat("Materias.dat");
    ManagerExamen manEx;

    int totalIns = archIns.contarRegistros();

    // Arreglo dinámico para guardar COMISIONES reales
    int* opciones = new int[totalIns];
    int cantOpc = 0;

    cout << "\n=== MATERIAS HABILITADAS PARA RENDIR FINAL ===\n\n";

    cout << "+--------+----------------------------------------+--------------+--------------+\n";
    cout << "| OPCION |                MATERIA                  |  COMISION    |  CONDICION   |\n";
    cout << "+--------+----------------------------------------+--------------+--------------+\n";

    for (int i = 0; i < totalIns; i++) {

        InscripcionComision ins = archIns.leerRegistro(i);

        if (ins.getLegajoAlumno() != legajoAlumno || ins.getEstado() == 2)
            continue;

        int posC = archCom.buscarRegistro(ins.getIdComision());
        if (posC < 0) continue;

        Comision com = archCom.leerRegistro(posC);
        int idMateria = com.getIdMateria();

        // VALIDACIÓN REAL → ¿Puede rendir final esta materia?
        if (!manEx.puedeRendirFinal(legajoAlumno, ins.getIdComision()))
            continue;

        // Traer nombre de materia
        int posM = archMat.buscarRegistro(idMateria);
        Materia m = archMat.leerRegistro(posM);
        string nombreMat = quitarAcentos(m.getNombre());

        // Guardar ID comisión real
        opciones[cantOpc] = ins.getIdComision();
        cantOpc++;

        // Mostrar fila
        cout << "| " << setw(6) << left << cantOpc
             << " | " << setw(38) << left << nombreMat
             << " | " << setw(12) << left << ins.getIdComision()
             << " | " << setw(12) << left << "Regular"
             << " |\n";
    }

    cout << "+--------+----------------------------------------+--------------+--------------+\n";

    // NADIE HABILITADO
    if (cantOpc == 0) {
        cout << "\nNo hay materias habilitadas para rendir final.\n";
        delete[] opciones;
        pauseScreen();
        return;
    }

    // SELECCIÓN DE OPCIÓN
    int seleccion = Validacion::validarEntero("\nSeleccione opción: ");

    if (seleccion < 1 || seleccion > cantOpc) {
        cout << "\nERROR: opción inválida.\n";
        delete[] opciones;
        pauseScreen();
        return;
    }

    // ID REAL DE COMISIÓN ELEGIDO
    int idComision = opciones[seleccion - 1];
    delete[] opciones;

    // Recuperar materia
    int posCom = archCom.buscarRegistro(idComision);
    int idMateria = archCom.leerRegistro(posCom).getIdMateria();

    // ====================
    // CREAR INSCRIPCIÓN
    // ====================
    cout << "\nInscribiendo al examen final...\n";

    Fecha f;
    f.cargar();

    Examen final(0, idMateria, legajoAlumno, "Final", 0, f, false);

    ArchivoExamen archEx("Examenes.dat");

    if (archEx.agregarRegistro(final))
        cout << "\nInscripción al FINAL realizada correctamente.\n";
    else
        cout << "\nERROR al registrar la inscripción.\n";

    pauseScreen();
}
