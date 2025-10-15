#include <iostream>
#include <vector>
using namespace std;

#include "profesor_menu.h"
#include "Fecha.h"
#include "Inscripcion.h"
#include "InstanciaEvaluacion.h"

// ================== Datos compartidos (definidos en otro .cpp) ==================
extern vector<Inscripcion>         g_inscripciones;
extern vector<InstanciaEvaluacion> g_instancias;

// ====== Comisiones simples (idComision == idMateria) ======
struct ComisionInfo {
    int  idComision;   // igual que id materia
    char aula[32];     // sin espacios (p.ej. 0_PACHECO_NOCHE)
    char horarios[80]; // sin espacios (p.ej. Mar18-22_Jue18-22)
};
extern vector<ComisionInfo> g_comisiones;   // definila en un .cpp (p.ej. main.cpp)

// ====== Períodos (definición/carga en otro módulo) ======
enum PeriodoTipo { PERIODO_CURSADA=1, PERIODO_FINAL=2, PERIODO_BAJA=3 };
extern void cargarPeriodosAnuales(int anio);  // implementada en otro .cpp

// ====== Prototipos de acciones ======
void profDefinirPeriodos();
void profAltaComision();
void profListarComisiones();
void profRegistrarParcialRecup();
void profRegistrarFinal();
void profCerrarCursada();

// ====== Menú Profesor ======
void menuProfesor() {
    int op;
    do {
        cout << "\n--- MENU PROFESOR (Admin + Academico) ---\n";
        cout << "1) Definir periodos (cursado/final/baja)\n";
        cout << "2) Alta comision (aula/horarios)\n";
        cout << "3) Listar comisiones\n";
        cout << "4) Registrar PARCIAL/RECUPERATORIO\n";
        cout << "5) Registrar FINAL\n";
        cout << "6) Cerrar cursada (REGULAR/LIBRE)\n";
        cout << "0) Volver\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: profDefinirPeriodos();       break;
            case 2: profAltaComision();          break;
            case 3: profListarComisiones();      break;
            case 4: profRegistrarParcialRecup(); break;
            case 5: profRegistrarFinal();        break;
            case 6: profCerrarCursada();         break;
            case 0: break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (op != 0);
}

// ====== Acciones ======
void profDefinirPeriodos() {
    int anio;
    cout << "Anio (2000..2100): ";
    cin >> anio;
    if (anio < 2000) anio = 2000;
    if (anio > 2100) anio = 2100;
    cargarPeriodosAnuales(anio);
    cout << "Periodos definidos para " << anio << ".\n";
}

void profAltaComision() {
    ComisionInfo c{};
    cout << "ID Comision/Materia: ";
    cin >> c.idComision;

    // Nota: sin espacios porque usamos solo '>>'
    cout << "Aula (sin espacios, ej. 0_PACHECO_NOCHE): ";
    cin >> c.aula;

    cout << "Horarios (sin espacios, ej. Mar18-22_Jue18-22): ";
    cin >> c.horarios;

    g_comisiones.push_back(c);
    cout << "Comision creada (ID=" << c.idComision << ").\n";
}

void profListarComisiones() {
    if (g_comisiones.empty()) { cout << "No hay comisiones.\n"; return; }
    cout << "\n-- Comisiones --\n";
    for (const auto& c : g_comisiones) {
        cout << "ID " << c.idComision
             << " | Aula: " << c.aula
             << " | Horarios: " << c.horarios << "\n";
    }
}

void profRegistrarParcialRecup() {
    cout << "=== Registrar PARCIAL/RECUPERATORIO ===\n";
    // Tu InstanciaEvaluacion::cargar() debe permitir elegir tipo (1=PARCIAL, 3=RECUPERATORIO)
    InstanciaEvaluacion ev;
    ev.cargar();  // pide fecha, nota (1..10), idInscripcion, tipo
    // aseguramos idEvaluacion secuencial simple
    ev.setIdEvaluacion((int)g_instancias.size() + 5000);
    g_instancias.push_back(ev);
    cout << "OK. Instancia registrada (idEval=" << ev.getIdEvaluacion() << ").\n";
}

void profRegistrarFinal() {
    cout << "=== Registrar FINAL ===\n";
    InstanciaEvaluacion ev;
    ev.cargar();  // elegí tipo 2=FINAL
    ev.setIdEvaluacion((int)g_instancias.size() + 5000);
    g_instancias.push_back(ev);

    // Si aprobó el final (umbral >= 6) marcamos la inscripción como APROBADA
    int idIns = ev.getIdInscripcion();
    for (auto& ins : g_inscripciones) {
        if (ins.getIdInscripcion() == idIns) {
            if (ev.getNota() >= 6) {
                ins.setEstadoPorOpcion(3); // 3 = APROBADA
                cout << "Inscripcion " << idIns << " pasa a APROBADA.\n";
            }
            break;
        }
    }
    cout << "Final registrado (idEval=" << ev.getIdEvaluacion() << ").\n";
}

void profCerrarCursada() {
    cout << "=== Cerrar cursada (REGULAR/LIBRE) ===\n";
    int idIns;
    cout << "ID Inscripcion: ";
    cin >> idIns;

    for (auto& ins : g_inscripciones) {
        if (ins.getIdInscripcion() == idIns) {
            int op;
            cout << "1) REGULAR  |  5) LIBRE\n";
            cout << "Opcion: ";
            cin >> op;
            if (op == 1) ins.setEstadoPorOpcion(2); // REGULAR
            else         ins.setEstadoPorOpcion(5); // LIBRE
            cout << "Cursada cerrada. Estado: " << ins.getEstado() << "\n";
            return;
        }
    }
    cout << "Inscripcion no encontrada.\n";
}
