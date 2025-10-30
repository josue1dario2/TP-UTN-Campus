#include "MenuDocente.h"
#include "ExamenManager.h"
#include "ComisionManager.h"
#include "AlumnoManager.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

MenuDocente::MenuDocente() {
    _cantidadOpciones = 10;
}

void MenuDocente::mostrar() {
    int opcion;
    do {
        system("cls");
        opcion = seleccionOpcion();
        system("cls");
        ejecutarOpcion(opcion);
        system("pause");
    } while (opcion != 0);
}

void MenuDocente::mostrarOpciones() {
    cout << "\n\tMENÚ DEL DOCENTE\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Ver Mis Comisiones\n";
    cout << "\t2) Ver Alumnos de una Comisión\n";
    cout << "\t3) Gestión de Notas (Parcial / TP / Recuperatorio)\n";
    cout << "\t4) Publicar Notas de Cursada\n";
    cout << "\t5) Cerrar Acta de Cursada\n";
    cout << "\t6) Ver Mis Mesas de Examen\n";
    cout << "\t7) Cargar Notas de Final\n";
    cout << "\t8) Exportar CSV (mis comisiones/mesas)\n";
    cout << "\t9) Solicitar baja (cerrar legajo)\n";
    cout << "\t10) Editar mis datos\n";
    cout << "\t0) Volver\n";
}

int MenuDocente::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();

    string mensaje="\t----------------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);

    return opcion;
}

//------------------------------------------------------
// SUBMENÚ DE NOTAS
//------------------------------------------------------

void MenuDocente::mostrarSubmenuNotas() {
    cout << "\n\tGESTIÓN DE NOTAS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Cargar Nota de Parcial / TP\n";
    cout << "\t2) Cargar Nota de Recuperatorio\n";
    cout << "\t3) Ver Historial de Exámenes de un Alumno\n";
    cout << "\t4) Ver Condición Académica\n";
    cout << "\t0) Volver\n";
}

int MenuDocente::seleccionarSubopcionNotas() {
    int opcion;
    mostrarSubmenuNotas();
    cout << "\t--------------------------------" << endl;
    cout << "\tOpción: ";
    cin >> opcion;

    while (opcion < 0 || opcion > 4) {
        cout << "\tOpción incorrecta..." << endl;
        cout << "\tOpción: ";
        cin >> opcion;
    }
    return opcion;
}

//------------------------------------------------------
// EJECUCIÓN DE OPCIONES
//------------------------------------------------------

void MenuDocente::ejecutarOpcion(int opcion) {
    ExamenManager examenMgr;
    int legajo, idComision, numero, nota;
    int subopcion;

    switch (opcion) {

        case 1: {
            ComisionManager comMgr;
            comMgr.mostrarTodasLasComisiones();
            break;
        }

        case 2: {
            AlumnoManager alumMgr;
            cout << "\nIngrese ID de la comisión: ";
            cin >> idComision;
            system("cls");
            cout << "=== Alumnos de la Comisión " << idComision << " ===\n";
            alumMgr.verMisComisiones(idComision);
            cout << "(Fin del listado)\n";
            break;
        }

        case 3: { // SUBMENÚ DE NOTAS
            do {
                system("cls");
                subopcion = seleccionarSubopcionNotas();
                system("cls");

                switch (subopcion) {
                    case 1: {
                        cout << "Ingrese legajo del alumno: ";
                        cin >> legajo;
                        cout << "Ingrese ID de comisión: ";
                        cin >> idComision;
                        cout << "Número de parcial (1, 2 o 3): ";
                        cin >> numero;
                        cout << "Nota (1 a 10): ";
                        cin >> nota;
                        examenMgr.cargarParcial(legajo, idComision, numero, nota);
                        examenMgr.recalcularCondicion(legajo, idComision);
                        break;
                    }

                    case 2: {
                        cout << "Ingrese legajo del alumno: ";
                        cin >> legajo;
                        cout << "Ingrese ID de comisión: ";
                        cin >> idComision;
                        cout << "Número del parcial a recuperar (1, 2 o 3): ";
                        cin >> numero;
                        cout << "Nota del recuperatorio (1 a 10): ";
                        cin >> nota;
                        examenMgr.cargarRecuperatorio(legajo, idComision, numero, nota);
                        examenMgr.recalcularCondicion(legajo, idComision);
                        break;
                    }

                    case 3: {
                        cout << "Ingrese legajo del alumno: ";
                        cin >> legajo;
                        examenMgr.mostrarHistorial(legajo);
                        break;
                    }

                    case 4: {
                        cout << "Ingrese legajo del alumno: ";
                        cin >> legajo;
                        cout << "Ingrese ID de comisión: ";
                        cin >> idComision;
                        examenMgr.recalcularCondicion(legajo, idComision);
                        break;
                    }

                    case 0:
                        cout << "Volviendo al menú principal...\n";
                        break;
                }

                if (subopcion != 0) system("pause");
            } while (subopcion != 0);
            break;
        }

        case 4: {
            cout << "\nIngrese ID de comisión: ";
            cin >> idComision;
            cout << "\nPublicando notas de cursada...\n";
            cout << "Notas publicadas correctamente para la comisión " << idComision << ".\n";
            break;
        }

        case 5: {
            cout << "\nIngrese ID de comisión a cerrar: ";
            cin >> idComision;
            int confirmar;
            cout << "¿Está seguro que desea cerrar el acta? (1=Sí / 0=No): ";
            cin >> confirmar;
            if (confirmar == 1)
                cout << "Acta de la comisión " << idComision << " cerrada exitosamente.\n";
            else
                cout << "Operación cancelada.\n";
            break;
        }

        case 6: {
            int idDocente;
            cout << "\nIngrese su ID de docente: ";
            cin >> idDocente;
            cout << "\n=== MESAS DE EXAMEN DEL DOCENTE " << idDocente << " ===\n";
            cout << "(Simulación) Mesa Final - Programación II - Comisión 12 - 10/11/2025\n";
            cout << "(Simulación) Mesa Final - Base de Datos I - Comisión 18 - 12/11/2025\n";
            break;
        }

        case 7: {
            cout << "Ingrese legajo del alumno: ";
            cin >> legajo;
            cout << "Ingrese ID de comisión: ";
            cin >> idComision;
            cout << "Nota final (1 a 10): ";
            cin >> nota;
            examenMgr.cargarFinal(legajo, idComision, nota);
            examenMgr.recalcularCondicion(legajo, idComision);
            break;
        }

        case 8: {
            cout << "\nExportando datos de comisiones y mesas a CSV...\n";
            ofstream file("ReporteDocente.csv");
            if (!file.is_open()) {
                cout << "Error al crear el archivo CSV.\n";
                break;
            }
            file << "ID_Comision,Materia,Tipo,Fecha\n";
            file << "12,Programacion II,Cursada,10/10/2025\n";
            file << "18,Base de Datos I,Mesa Final,12/11/2025\n";
            file.close();
            cout << "Archivo 'ReporteDocente.csv' generado exitosamente.\n";
            break;
        }

        case 9: {
            int idDocente, confirmar;
            cout << "\nIngrese su ID de docente: ";
            cin >> idDocente;
            cout << "¿Confirma la baja del legajo docente " << idDocente << "? (1=Sí / 0=No): ";
            cin >> confirmar;
            if (confirmar == 1)
                cout << "Solicitud de baja enviada al administrador.\n";
            else
                cout << "Operación cancelada.\n";
            break;
        }

        case 10: {
            string nombre, email;
            cout << "\n--- Edición de datos personales ---\n";
            cout << "Nuevo nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Nuevo email: ";
            getline(cin, email);
            cout << "Datos actualizados correctamente (simulación).\n";
            cout << "Nombre: " << nombre << "\nEmail: " << email << endl;
            break;
        }

        case 0: {
            cout << "Volviendo al menú anterior...\n";
            break;
        }

        default: {
            cout << "Opción no válida.\n";
            break;
        }
    }
}
