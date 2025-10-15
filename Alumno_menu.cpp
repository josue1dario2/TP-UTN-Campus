#include <iostream>
#include <vector>
using namespace std;

#include "Alumno_menu.h"
#include "Fecha.h"
#include "Inscripcion.h"
#include "InstanciaEvaluacion.h"

// ====== Datos compartidos (DEFINIDOS en otro .cpp, p.ej. main.cpp) ======
extern vector<Inscripcion>         g_inscripciones;
extern vector<InstanciaEvaluacion> g_instancias;

// ====== Periodos (declarados en otro módulo; acá solo los anunciamos) ======
enum PeriodoTipo { PERIODO_CURSADA=1, PERIODO_FINAL=2, PERIODO_BAJA=3 };
extern bool hayPeriodo(PeriodoTipo tipo, const Fecha& hoy);

// ====== Prototipos internos del menú Alumno ======
void alumnoVerInscripciones();
void alumnoInscribirseCursado();
void alumnoInscribirseFinal();
void alumnoVerEvaluaciones();

// ====== Implementación del menú ======
void menuAlumno() {
    int op;
    do {
        cout << "\n----- MENU ALUMNO -----\n";
        cout << "1) Ver mis inscripciones\n";
        cout << "2) Inscribirme a CURSADO (si hay periodo)\n";
        cout << "3) Inscribirme a FINAL (si cumplo)\n";
        cout << "4) Ver mis evaluaciones (historial)\n";
        cout << "0) Volver\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: alumnoVerInscripciones();   break;
            case 2: alumnoInscribirseCursado(); break;
            case 3: alumnoInscribirseFinal();   break;
            case 4: alumnoVerEvaluaciones();    break;
            case 0: break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (op != 0);
}

// ====== Acciones ======
void alumnoVerInscripciones() {
    int idAlu;
    cout << "ID Alumno: ";
    cin >> idAlu;

    bool hay = false;
    for (const auto& ins : g_inscripciones) {
        if (ins.getIdAlumno() == idAlu) {
            ins.mostrar();
            hay = true;
        }
    }
    if (!hay) cout << "No hay inscripciones para ese alumno.\n";
}

void alumnoInscribirseCursado() {
    cout << "Fecha actual (para validar periodo):\n";
    Fecha hoy; hoy.cargar();

    if (!hayPeriodo(PERIODO_CURSADA, hoy)) {
        cout << "No es periodo de INSCRIPCION A CURSADO.\n";
        return;
    }

    int idAlu, idCom;
    cout << "ID Alumno: ";            cin >> idAlu;
    cout << "ID Comision/Materia: ";  cin >> idCom;

    // Evitar duplicado
    for (const auto& ins : g_inscripciones) {
        if (ins.getIdAlumno() == idAlu && ins.getIdComision() == idCom) {
            cout << "Ya existe una inscripcion para esa materia. Estado: "
                 << ins.getEstado() << "\n";
            return;
        }
    }

    Inscripcion i;
    i.setIdInscripcion((int)g_inscripciones.size() + 1000); // id simple
    i.setIdAlumno(idAlu);
    i.setIdComision(idCom);
    i.setFechaInscripcion(hoy);
    i.setEstadoPorOpcion(1); // 1=ACTIVA
    i.setNotaCursada(1);     // luego el profesor la actualizará
    i.setIntentosFinal(0);

    g_inscripciones.push_back(i);
    cout << "Inscripto a cursado. ID Inscripcion: " << i.getIdInscripcion() << "\n";
}

void alumnoInscribirseFinal() {
    cout << "Fecha actual (para validar periodo):\n";
    Fecha hoy; hoy.cargar();

    if (!hayPeriodo(PERIODO_FINAL, hoy)) {
        cout << "No es periodo de INSCRIPCION A FINALES.\n";
        return;
    }

    int idIns;
    cout << "ID Inscripcion (de la materia a rendir): ";
    cin >> idIns;

    for (auto& ins : g_inscripciones) {
        if (ins.getIdInscripcion() == idIns) {
            // Tu clase Inscripcion debe validar: nota >= 6 y < 3 intentos,
            // y mostrar el motivo si no se puede.
            ins.inscribirAFinal();
            return;
        }
    }
    cout << "Inscripcion no encontrada.\n";
}

void alumnoVerEvaluaciones() {
    int idAlu;
    cout << "ID Alumno: ";
    cin >> idAlu;

    // Juntar IDs de inscripciones del alumno
    vector<int> ids;
    for (const auto& ins : g_inscripciones) {
        if (ins.getIdAlumno() == idAlu) ids.push_back(ins.getIdInscripcion());
    }

    if (ids.empty()) {
        cout << "El alumno no tiene inscripciones.\n";
        return;
    }

    bool hay = false;
    for (const auto& ev : g_instancias) {
        // Mostrar solo evaluaciones ligadas a mis inscripciones
        for (int id : ids) {
            if (ev.getIdInscripcion() == id) {
                ev.mostrar();
                hay = true;
            }
        }
    }
    if (!hay) cout << "Sin evaluaciones para este alumno.\n";
}
