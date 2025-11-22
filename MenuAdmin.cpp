#include "MenuAdmin.h"
#include "Validacion.h"
#include "utils.h"

#include "ArchivoInscripcionComision.h"
#include "InscripcionComision.h"

#include <iostream>
using namespace std;

MenuAdministrador::MenuAdministrador() {
    _cantidadOpciones = 4;
}

void MenuAdministrador::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();

        if (opcion == 0) return;

        ejecutarOpcion(opcion);
        pauseScreen();

    } while (opcion != 0);
}

void MenuAdministrador::mostrarOpciones() {
    cout << "\n\tMENÚ ADMINISTRADOR\n";
    cout << "\t-----------------------------------------\n";
    cout << "\t1) ABM Carreras\n";
    cout << "\t2) ABM Materias\n";
    cout << "\t3) ABM Comisiones\n";
    cout << "\t4) Solicitudes de Baja de Comisiones\n";
    cout << "\t0) Volver\n";
}

int MenuAdministrador::seleccionOpcion() {
    mostrarOpciones();
    cout << "\t-----------------------------------------\n";
    cout << "\tOpción: ";
    return Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);
}

void MenuAdministrador::ejecutarOpcion(int opcion) {
    switch (opcion) {

        case 1:
            menuCarreras.mostrar();
            break;

        case 2:
            menuMaterias.mostrarMenuABMMaterias();
            break;

        case 3:
            menuComisiones.mostrar();
            break;

        case 4: {

            clearScreen();
            cout << "\n\t=== Solicitudes PENDIENTES de baja ===\n";

            ArchivoInscripcionComision arch("InscripcionesComision.dat");
            int total = arch.contarRegistros();

            bool hayPendientes = false;

            for (int i = 0; i < total; i++) {

                InscripcionComision ins = arch.leerRegistro(i);

                if (ins.getEstado() == 1) {  // 1 = Pendiente de baja

                    hayPendientes = true;

                    cout << "\n------------------------------------------\n";
                    cout << "Legajo Alumno: " << ins.getLegajoAlumno() << endl;
                    cout << "ID Comisión : " << ins.getIdComision() << endl;
                    cout << "Fecha Inscripción: ";
                    ins.getFecha().mostrar();
                    cout << endl;

                    cout << "\n¿Aprobar baja? (1 = Aprobar / 2 = Rechazar / 0 = Omitir): ";
                    int accion;
                    cin >> accion;

                    if (accion == 1) {
                        _managerAlumno.bajaInscripcionComision(
                            ins.getLegajoAlumno(),
                            ins.getIdComision()
                        );
                    }
                    else if (accion == 2) {
                        ins.setEstado(0); // Rechazada → vuelve a Activa
                        arch.modificarRegistro(ins, i);
                        cout << "\nSolicitud rechazada.\n";
                    }
                }
            }

            if (!hayPendientes) {
                cout << "\nNo hay solicitudes pendientes.\n";
            }

            break;
        }

        case 0:
            return;

        default:
            cout << "Opción inválida.\n";
            break;
    }
}
