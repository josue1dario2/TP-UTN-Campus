#include <iostream>
#include <vector>
using namespace std;

#include "tesoreria_menu.h"
#include "Cuota.h"
#include "Fecha.h"

// Definida en otro .cpp (por ejemplo en main.cpp)
extern vector<Cuota> g_cuotas;

// Prototipos internos
void tesoreriaCargarCuota();
void tesoreriaListarCuotas();
void tesoreriaMarcarPagada();

void menuTesoreria() {
    int op;
    do {
        cout << "\n--- TESORERIA (Cuotas) ---\n";
        cout << "1) Cargar cuota\n";
        cout << "2) Listar cuotas\n";
        cout << "3) Marcar cuota pagada\n";
        cout << "0) Volver\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1: tesoreriaCargarCuota();  break;
            case 2: tesoreriaListarCuotas(); break;
            case 3: tesoreriaMarcarPagada(); break;
            case 0: break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while (op != 0);
}

void tesoreriaCargarCuota() {
    Cuota c;

    int idCuota, idAlumno;
    char periodo[20];
    float monto;

    cout << "ID Cuota (>=0): ";
    cin >> idCuota;
    if (idCuota < 0) idCuota = 0;

    cout << "ID Alumno (>=0): ";
    cin >> idAlumno;
    if (idAlumno < 0) idAlumno = 0;

    cout << "Periodo (sin espacios, ej. 2025-03 o MAR-2025): ";
    cin >> periodo;  // simple: sin espacios

    cout << "Monto (>=0): ";
    cin >> monto;
    if (monto < 0.f) monto = 0.f;

    cout << "Fecha de vencimiento:\n";
    Fecha fv; fv.cargar();

    int pagadaOpcion;
    cout << "Esta pagada? (1=SI / 0=NO): ";
    cin >> pagadaOpcion;
    bool pagada = (pagadaOpcion == 1);

    c.setIdCuota(idCuota);
    c.setIdAlumno(idAlumno);
    c.setPeriodo(periodo);
    c.setMonto(monto);
    c.setFechaVencimiento(fv);
    c.setEstaPagada(pagada);

    g_cuotas.push_back(c);
    cout << "Cuota cargada. ID=" << c.getIdCuota() << "\n";
}

void tesoreriaListarCuotas() {
    if (g_cuotas.empty()) {
        cout << "No hay cuotas.\n";
        return;
    }
    // for con índice (simple)
    for (size_t i = 0; i < g_cuotas.size(); i++) {
        g_cuotas[i].mostrar();
    }
}

void tesoreriaMarcarPagada() {
    if (g_cuotas.empty()) {
        cout << "No hay cuotas cargadas.\n";
        return;
    }

    int id;
    cout << "ID de cuota a marcar como pagada: ";
    cin >> id;

    // for con índice (simple)
    for (size_t i = 0; i < g_cuotas.size(); i++) {
        if (g_cuotas[i].getIdCuota() == id) {
            g_cuotas[i].setEstaPagada(true);
            cout << "Cuota " << id << " marcada como PAGADA.\n";
            return;
        }
    }
    cout << "Cuota no encontrada.\n";
}
