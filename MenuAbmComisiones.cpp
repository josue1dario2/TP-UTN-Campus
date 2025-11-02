#include "MenuAbmComisiones.h"
#include <iostream>
#include <cstdlib>
using namespace std;

MenuAbmComisiones::MenuAbmComisiones() {
    _cantidadOpciones = 5;
}

void MenuAbmComisiones::mostrar() {
    int opcion;
    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        if (opcion != 0) system("pause");
    } while (opcion != 0);
}

void MenuAbmComisiones::mostrarOpciones() {
    cout << endl;
    cout << "\n\t===== ABM COMISIONES =====\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Comisión\n";
    cout << "\t2) Modificar Comisión\n";
    cout << "\t3) Baja lógica de Comisión\n";
    cout << "\t4) Listar todas las Comisiones\n";
    cout << "\t5) Listar Comisiones por Año\n";
    cout << "\t0) Volver\n";
}

int MenuAbmComisiones::seleccionOpcion() {
    int opcion;
    mostrarOpciones();

    string mensaje = "\t--------------------------------\n\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje, 0, _cantidadOpciones);
    return opcion;
}

void MenuAbmComisiones::ejecutarOpcion(int opcion) {
    int id, anio;

    switch (opcion) {
        case 1: {
            cout << "\n--- Alta de Comisión ---\n";
            Comision nueva;
            nueva.cargar();
            if (_archivoComision.agregarRegistro(nueva))
                cout << "Comisión registrada correctamente.\n";
            else
                cout << "Error al registrar la comisión.\n";
            break;
        }

        case 2: {
            cout << "\n--- Modificar Comisión ---\n";
            cout << "Ingrese ID de la comisión: ";
            cin >> id;

            int pos = _archivoComision.buscarRegistro(id);
            if (pos == -1) {
                cout << "No se encontró la comisión.\n";
                break;
            }

            Comision reg = _archivoComision.leerRegistro(pos);
            cout << "\nDatos actuales:\n";
            reg.mostrar();

            cout << "\nIngrese los nuevos datos:\n";
            reg.cargar();

            if (_archivoComision.modificarRegistro(reg, pos))
                cout << "Comisión modificada correctamente.\n";
            else
                cout << "Error al modificar la comisión.\n";
            break;
        }

        case 3: {
            cout << "\n--- Baja lógica de Comisión ---\n";
            cout << "Ingrese ID de la comisión: ";
            cin >> id;

            int pos = _archivoComision.buscarRegistro(id);
            if (pos == -1) {
                cout << "Comisión no encontrada.\n";
                break;
            }

            if (_archivoComision.bajaLogica(pos))
                cout << "Comisión dada de baja correctamente.\n";
            else
                cout << "Error al dar de baja la comisión.\n";
            break;
        }

        case 4: {
            cout << "\n--- Listado de Comisiones ---\n";
            _archivoComision.listarRegistros();
            break;
        }

        case 5: {
            cout << "\n--- Listar Comisiones por Año ---\n";
            cout << "Ingrese el año: ";
            cin >> anio;

            int total = _archivoComision.contarRegistros();
            bool encontrado = false;

            for (int i = 0; i < total; i++) {
                Comision c = _archivoComision.leerRegistro(i);
                if (!c.getEliminado() && c.getAnio() == anio) {
                    c.mostrar();
                    encontrado = true;
                }
            }

            if (!encontrado)
                cout << "No hay comisiones registradas para el año " << anio << ".\n";

            break;
        }

        case 0:
            cout << "Volviendo al menú anterior...\n";
            break;

        default:
            cout << "Opción no válida.\n";
            break;
    }
}
