#include "ManagerInscripcionComision.h"
#include "ManagerComision.h"
#include "ManagerAlumno.h"
#include "ArchivoComision.h"
#include "ArchivoExamen.h"
#include "Examen.h"
#include "Validacion.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

ManagerInscripcionComision::ManagerInscripcionComision() {}

void ManagerInscripcionComision::mostrarEncabezado() {
    cout << "\t+-------------+-------------+------------------+----------------------+\n";
    cout << "\t| Legajo Alum | ID Comision | Fecha Inscripción | Estado               |\n";
    cout << "\t+-------------+-------------+------------------+----------------------+\n";
}

void ManagerInscripcionComision::mostrarRegistro(const InscripcionComision& reg) {
    cout << "\t| " << setw(11) << reg.getLegajoAlumno()
         << " | " << setw(11) << reg.getIdComision()
         << " | ";
    reg.getFecha().mostrar();
    cout << " | ";

    if (reg.getEstado() == 0) cout << setw(20) << "Activa";
    else if (reg.getEstado() == 1) cout << setw(20) << "Pendiente de baja";
    else cout << setw(20) << "Baja";

    cout << " |\n";
}

void ManagerInscripcionComision::mostrarPie() {
    cout << "\t+-------------+-------------+------------------+----------------------+\n";
}

void ManagerInscripcionComision::cargar() {
    cout << "\n\t=== Nueva Inscripción a Comisión ===\n";

    int legajo = Validacion::validarEnteroEnRango("\tLegajo Alumno: ", 1, 99999);
    int idComision = Validacion::validarEnteroEnRango("\tID Comisión: ", 1, 99999);

    // 1) Validar que la comisión exista
    ManagerComision manCom;
    if (!manCom.existeComision(idComision)) {
        cout << "\n\tERROR: La comisión no existe o está dada de baja.\n";
        return;
    }

    // 2) Verificar doble inscripción
    if (estaInscripto(legajo, idComision)) {
        cout << "\tEl alumno ya está inscripto en esta comisión.\n";
        return;
    }

    // 3) Obtener idMateria desde Comisión
    ArchivoComision arcCom;
    int posCom = arcCom.buscarRegistro(idComision);
    Comision com = arcCom.leerRegistro(posCom);
    int idMateria = com.getIdMateria();

    // 4) Validar CORRELATIVAS para cursar
    ManagerAlumno manAlumno;
    if (!manAlumno.cumpleCorrelativas(legajo, idMateria)) {
        cout << "\n\tERROR: El alumno NO cumple las correlativas para cursar esta materia.\n";
        return;
    }

    // 5) Validar si ya aprobó la materia
    ArchivoExamen arcExamen;
    int totalEx = arcExamen.contarRegistros();
    for (int i = 0; i < totalEx; i++) {
        Examen ex = arcExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            ex.getNota() >= 4)
        {
            cout << "\n\tERROR: El alumno ya APROBÓ la materia. No puede cursarla.\n";
            return;
        }
    }

    // 6) Crear inscripción válida
    Fecha hoy;
    hoy.cargar();

    InscripcionComision nueva(legajo, idComision);
    nueva.setFecha(hoy);
    nueva.setEstado(0);  // activo

    if (_archivo.agregarRegistro(nueva))
        cout << "\tInscripción guardada correctamente.\n";
    else
        cout << "\tError al guardar la inscripción.\n";
}

void ManagerInscripcionComision::listar() {
    cout << "\n\t=== Listado de Inscripciones a Comisión ===\n";
    int total = _archivo.contarRegistros();
    if (total == 0) {
        cout << "\tNo hay inscripciones.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; i++) {
        InscripcionComision reg = _archivo.leerRegistro(i);

        if (reg.getEstado() != 2) // activo o pendiente
            mostrarRegistro(reg);
    }
    mostrarPie();
}

void ManagerInscripcionComision::borrar() {
    cout << "\n\t=== Solicitud de Baja ===\n";

    int legajo = Validacion::validarEnteroEnRango("\tLegajo Alumno: ", 1, 99999);
    int idComision = Validacion::validarEnteroEnRango("\tID Comisión: ", 1, 99999);

    int pos = _archivo.buscarRegistro(legajo, idComision);

    if (pos >= 0) {
        InscripcionComision reg = _archivo.leerRegistro(pos);

        if (reg.getEstado() == 2) {
            cout << "\tLa inscripción ya está dada de baja definitivamente.\n";
            return;
        }

        reg.setEstado(1);   // Pendiente de baja
        _archivo.modificarRegistro(reg, pos);

        cout << "\tBaja solicitada correctamente. El ADMINISTRADOR debe aprobarla.\n";
    }
    else {
        cout << "\tNo se encontró inscripción activa.\n";
    }
}


bool ManagerInscripcionComision::estaInscripto(int legajo, int idComision) {
    int total = _archivo.contarRegistros();

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivo.leerRegistro(i);

        if (ins.getLegajoAlumno() == legajo &&
            ins.getIdComision() == idComision &&
            ins.getEstado() != 2) // activo o pendiente
        {
            return true;
        }
    }

    return false;
}

void ManagerInscripcionComision::procesarSolicitudesPendientes() {
    cout << "\n\t=== Solicitudes PENDIENTES DE BAJA ===\n";

    int total = _archivo.contarRegistros();
    bool hay = false;

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivo.leerRegistro(i);

        if (ins.getEstado() == 1) { // 1 = Pendiente de baja
            hay = true;

            cout << "\n-------------------------------------------\n";
            cout << "Legajo: " << ins.getLegajoAlumno() << endl;
            cout << "ID Comisión: " << ins.getIdComision() << endl;
            cout << "Fecha: ";
            ins.getFecha().mostrar();
            cout << endl;

            int opcion = Validacion::validarEnteroEnRango(
                "\n 1) Aprobar\n 2) Rechazar\n 0) Omitir\n Opción: ",
                0, 2
            );

            if (opcion == 1) {
                ins.setEstado(2); // BAJA DEFINITIVA
                _archivo.modificarRegistro(ins, i);
                cout << "\tBAJA APROBADA.\n";
            }
            else if (opcion == 2) {
                ins.setEstado(0); // Vuelve a activa
                _archivo.modificarRegistro(ins, i);
                cout << "\tSOLICITUD RECHAZADA.\n";
            }
        }
    }

    if (!hay) {
        cout << "\nNo hay solicitudes pendientes.\n";
    }
}
