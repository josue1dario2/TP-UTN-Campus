#include "ManagerDocente.h"
#include "ManagerInscripcionComision.h"
#include "Validacion.h"
#include <fstream>
#include <iomanip>

using namespace std;

ManagerDocente::ManagerDocente()
    : _archivoDocentes("Docentes.dat"),
      _archivoComisiones("Comisiones.dat"),
      _archivoInscripciones("InscripcionesComision.dat"),
      _archivoExamen("Examenes.dat"),
      _archivoMaterias("Materias.dat") {}


// --------------------------------------------------
// CRUD BÁSICO
// --------------------------------------------------
void ManagerDocente::registrarDocente() {
    Docente nuevo;
    nuevo.cargar();

    if (_archivoDocentes.buscarRegistro(nuevo.getLegajo()) != -1) {
        cout << "\n\tYa existe un docente con ese legajo.\n";
        return;
    }

    if (_archivoDocentes.agregarRegistro(nuevo))
        cout << "\n\tDocente registrado correctamente.\n";
    else
        cout << "\n\tError al guardar el docente.\n";
}

void ManagerDocente::listarDocentes() {
    int total = _archivoDocentes.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay docentes registrados.\n";
        return;
    }

    cout << "\n\t=== LISTADO DE DOCENTES ===\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Docente doc = _archivoDocentes.leerRegistro(i);
        if (!doc.getEliminado()) {
            mostrarRegistro(doc);
        }
    }

    mostrarPie();
}

void ManagerDocente::mostrarDocentePorLegajo(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos < 0) {
        cout << "\n\tNo se encontró el docente.\n";
        return;
    }
    Docente doc = _archivoDocentes.leerRegistro(pos);
    doc.mostrar();
}

void ManagerDocente::editarDocente(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos < 0) {
        cout << "\n\tDocente no encontrado.\n";
        return;
    }

    Docente doc = _archivoDocentes.leerRegistro(pos);

    if (doc.getEliminado()) {
        cout << "\n\tEl docente está dado de baja.\n";
        return;
    }

    cout << "\n\t=== EDITAR MIS DATOS ===\n";
    cout << "\n\tDatos actuales:\n";
    doc.mostrar();

<<<<<<< HEAD
    if (!Validacion::desearAccionar("\tDesea proceder? s/n "))
        {
        return;
        }


    cout << "\n\tIngrese los nuevos datos:\n";
    doc.cargar();

    if (Validacion::desearAccionar("\tDesea guardar los datos? s/n ")){
        if (_archivoDocentes.modificarRegistro(doc, pos))
            cout << "\n\tDatos actualizados correctamente.\n";
        else
            cout << "\n\tError al actualizar.\n";
        }

=======
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
            doc.setDni(dni);
            break;
        }
        case 2: {
            char nombre[50];
            cout << "\n\tNuevo nombre: ";
            cin.getline(nombre, 50);
            doc.setNombre(nombre);
            break;
        }
        case 3: {
            char apellido[50];
            cout << "\n\tNuevo apellido: ";
            cin.getline(apellido, 50);
            doc.setApellido(apellido);
            break;
        }
        case 4: {
            char telefono[50];
            cout << "\n\tNuevo teléfono: ";
            cin.getline(telefono, 50);
            doc.setTelefono(telefono);
            break;
        }
        case 5: {
            char email[50];
            cout << "\n\tNuevo email: ";
            cin.getline(email, 50);
            doc.setEmail(email);
            break;
        }
        case 6: {
            Direccion dir;
            cout << "\n\tNueva dirección:\n";
            dir.cargar();
            doc.setDireccion(dir);
            break;
        }
        case 7: {
            Fecha fechaNac;
            cout << "\n\tNueva fecha de nacimiento:\n";
            fechaNac.cargar();
            doc.setFechaNacimiento(fechaNac);
            break;
        }
        case 8: {
            Fecha fechaIng;
            cout << "\n\tNueva fecha de ingreso:\n";
            fechaIng.cargar();
            doc.setFechaIngreso(fechaIng);
            break;
        }
        case 0:
            cout << "\n\tOperación cancelada.\n";
            return;
        default:
            cout << "\n\tOpción inválida.\n";
            return;
    }

    if (_archivoDocentes.modificarRegistro(doc, pos)) {
        cout << "\n\t✓ Datos actualizados correctamente.\n";
    } else {
        cout << "\n\t✗ Error al actualizar los datos.\n";
    }
>>>>>>> a8db492aa40f9e6708faf4e3795888d6b6473540
}

void ManagerDocente::solicitarBaja(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);
    if (pos < 0) {
        cout << "\n\tDocente no encontrado.\n";
        return;
    }

    if (_archivoDocentes.bajaLogica(pos))
        cout << "\n\tBaja solicitada correctamente.\n";
    else
        cout << "\n\tError al realizar la baja.\n";
}


// --------------------------------------------------
// FUNCIONES ACADÉMICAS
// --------------------------------------------------

void ManagerDocente::verMisComisiones(int legajo) {
    cout << "\n\t=== MIS COMISIONES ===\n";

    int total = _archivoComisiones.contarRegistros();
    bool tieneComisiones = false;

    cout << "\t+------------+------------+------------+------------+------------+\n";
    cout << "\t| ID Comisión| ID Materia | Turno      | Modalidad  | Año        |\n";
    cout << "\t+------------+------------+------------+------------+------------+\n";

    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);

        if (!c.getEliminado() && c.getLegajoDocente() == legajo) {
            tieneComisiones = true;

            cout << "\t| " << setw(10) << right << c.getIdComision()
                 << " | " << setw(10) << right << c.getIdMateria()
                 << " | " << setw(10) << left  << c.getTurno()
                 << " | " << setw(10) << left  << c.getModalidad()
                 << " | " << setw(10) << right << c.getAnio() << " |\n";
        }
    }

    cout << "\t+------------+------------+------------+------------+------------+\n";

    if (!tieneComisiones)
        cout << "\tNo se encontraron comisiones asignadas.\n";
}

void ManagerDocente::verAlumnosDeComision(int idComision) {
    cout << "\n\t=== ALUMNOS DE LA COMISIÓN " << idComision << " ===\n";

    int total = _archivoInscripciones.contarRegistros();
    bool hayAlumnos = false;

    cout << "\t+--------------+--------------+\n";
    cout << "\t| Legajo Alumno| Fecha Inscrip|\n";
    cout << "\t+--------------+--------------+\n";

    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);

        if (ins.getIdComision() == idComision && ins.getEstado() == 0) {

            hayAlumnos = true;

            cout << "\t| " << setw(12) << right << ins.getLegajoAlumno()
                 << " | ";
            ins.getFecha().mostrar();
            cout << " |\n";
        }
    }

    cout << "\t+--------------+--------------+\n";

    if (!hayAlumnos)
        cout << "\tNo hay alumnos inscriptos.\n";
}


// --------------------------------------------------
// CARGA DE NOTAS DE PARCIAL / TP + VALIDACIÓN ACTA CERRADA
// --------------------------------------------------

void ManagerDocente::cargarNotasParcialTP(int legajoDocente) {
    int idComision, legajoAlumno, nota;

    cout << "\n\t=== CARGA DE NOTAS PARCIALES / TP ===\n";
    cout << "\tID Comisión: ";
    cin >> idComision;

    if (!dictaComision(legajoDocente, idComision)) {
        cout << "\n\tERROR: Usted NO dicta esta comisión.\n";
        return;
    }

    int pos = _archivoComisiones.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\n\tERROR: La comisión no existe.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(pos);

    // 🔥 VALIDACIÓN ACTA CERRADA
    if (com.getEliminado()) {
        cout << "\n\tERROR: El ACTA ya está CERRADA. No se pueden cargar parciales.\n";
        return;
    }

    int idMateria = com.getIdMateria();

    cout << "\tLegajo Alumno: ";
    cin >> legajoAlumno;

    ManagerInscripcionComision manIns;
    if (!manIns.estaInscripto(legajoAlumno, idComision)) {
        cout << "\n\tERROR: El alumno NO está inscripto en esta comisión.\n";
        return;
    }

    // Contar parciales existentes
    int totalEx = _archivoExamen.contarRegistros();
    int parciales = 0;

    for (int i = 0; i < totalEx; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajoAlumno &&
            ex.getIdMateria() == idMateria &&
            strcmp(ex.getTipo(), "Parcial") == 0)
        {
            parciales++;
        }
    }

    if (parciales >= 2) {
        cout << "\n\tERROR: Ya tiene los 2 parciales cargados.\n";
        return;
    }

    if (_examenManager.estaPromocionado(legajoAlumno, idComision)) {
        cout << "\n\tERROR: El alumno YA está promocionado.\n";
        return;
    }

    cout << "\tNota (1-10): ";
    cin >> nota;

    if (nota < 1 || nota > 10) {
        cout << "\n\tERROR: La nota debe estar entre 1 y 10.\n";
        return;
    }

    _examenManager.cargarParcial(legajoAlumno, idComision, nota);
}


// --------------------------------------------------
// CARGA DE NOTAS DE FINAL + VALIDACIÓN ACTA CERRADA
// --------------------------------------------------

void ManagerDocente::cargarNotasFinal(int legajoDocente) {
    int idComision, legajoAlumno, nota;

    cout << "\n\t=== CARGA DE NOTAS FINALES ===\n";
    cout << "\tID Comisión: ";
    cin >> idComision;

    if (!dictaComision(legajoDocente, idComision)) {
        cout << "\n\tERROR: Esta comisión NO pertenece al docente.\n";
        return;
    }

    int pos = _archivoComisiones.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\n\tERROR: La comisión no existe.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(pos);

    // 🔥 VALIDACIÓN ACTA CERRADA
    if (com.getEliminado()) {
        cout << "\n\tERROR: ACTA DE CURSADA CERRADA. No se puede cargar FINAL.\n";
        return;
    }

    cout << "\tLegajo Alumno: ";
    cin >> legajoAlumno;

    cout << "\tNota (0-10): ";
    cin >> nota;

    _examenManager.cargarFinal(legajoAlumno, idComision, nota);
}


// --------------------------------------------------
// PRESENTACIÓN
// --------------------------------------------------

void ManagerDocente::mostrarEncabezado() {
    cout << "\t+--------+---------------------------+---------------------------+-------------+---------+\n";
    cout << "\t| Legajo | Nombre                    | Apellido                  | Teléfono    | Estado  |\n";
    cout << "\t+--------+---------------------------+---------------------------+-------------+---------+\n";
}

void ManagerDocente::mostrarRegistro(const Docente& doc) {
    cout << "\t| " << setw(6) << right << doc.getLegajo()
         << " | " << setw(25) << left << doc.getNombre()
         << " | " << setw(25) << left << doc.getApellido()
         << " | " << setw(11) << left << doc.getTelefono()
         << " | " << setw(7) << left << (doc.getEliminado() ? "Baja" : "Activo")
         << " |\n";
}

void ManagerDocente::mostrarPie() {
    cout << "\t+--------+---------------------------+---------------------------+-------------+---------+\n";
}


// --------------------------------------------------
// VERIFICACIÓN DE INTEGRIDAD
// --------------------------------------------------

bool ManagerDocente::dictaComision(int legajoDocente, int idComision) {
    int total = _archivoComisiones.contarRegistros();

    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);

        if (!c.getEliminado() &&
            c.getIdComision() == idComision &&
            c.getLegajoDocente() == legajoDocente)
        {
            return true;
        }
    }

    return false;
}


// --------------------------------------------------
// PUBLICAR NOTAS DE CURSADA
// --------------------------------------------------

void ManagerDocente::publicarNotasCursada(int legajoDocente) {
    int idComision;
    cout << "\n\t=== PUBLICAR NOTAS DE CURSADA ===\n";
    cout << "\tID Comisión: ";
    cin >> idComision;

    // 1) Verificar que dicta la comisión
    if (!dictaComision(legajoDocente, idComision)) {
        cout << "\n\tERROR: Esta comisión NO pertenece al docente.\n";
        return;
    }

    // 2) Obtener comisión
    int posCom = _archivoComisiones.buscarRegistro(idComision);
    if (posCom < 0) {
        cout << "\n\tERROR: La comisión no existe.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(posCom);
    int idMateria = com.getIdMateria();

    // 🔥 3) ACTA CERRADA → NO SE PUEDE PUBLICAR
    if (com.getEliminado()) {
        cout << "\n\tERROR: El ACTA ya fue CERRADA. No se pueden publicar notas.\n";
        return;
    }

    int totalIns = _archivoInscripciones.contarRegistros();
    int totalEx = _archivoExamen.contarRegistros();
    bool hay = false;

    cout << "\n\tProcesando alumnos...\n";

    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);

        if (ins.getIdComision() != idComision || ins.getEstado() != 0)
            continue;

        hay = true;
        int legA = ins.getLegajoAlumno();

        // Evitar publicar 2 veces
        bool yaPublicada = false;

        for (int j = 0; j < totalEx; j++) {
            Examen ex = _archivoExamen.leerRegistro(j);

            if (ex.getLegajoAlumno() == legA &&
                ex.getIdMateria() == idMateria &&
                strcmp(ex.getTipo(), "Cursada") == 0)
            {
                yaPublicada = true;
                break;
            }
        }

        if (yaPublicada) {
            cout << "\n\tAlumno " << legA << ": YA TENÍA CURSADA PUBLICADA. (Se omite)";
            continue;
        }

        // Calcular condición
        bool promo   = _examenManager.estaPromocionado(legA, idComision);
        bool regular = _examenManager.estaRegular(legA, idComision);
        bool libre   = !promo && !regular;

        int notaFinal = (promo ? 10 : regular ? 4 : 2);

        // Guardar cursada
        Fecha hoy;
        hoy.cargar();

        Examen ex(0, idMateria, legA, "Cursada", 0, hoy, false);
        ex.setNota(notaFinal);
        ex.setCorregido(true);

        _archivoExamen.agregarRegistro(ex);

        cout << "\n\tAlumno " << legA
             << ": " << (promo ? "PROMOCIONADO" : regular ? "REGULAR" : "LIBRE")
             << " → Nota Cursada: " << notaFinal;
    }

    if (!hay) {
        cout << "\n\tNo hay alumnos inscriptos en esta comisión.\n";
        return;
    }

    cout << "\n\n\tNotas de Cursada PUBLICADAS correctamente.\n";
}



// --------------------------------------------------
// CERRAR ACTA DE CURSADA
// --------------------------------------------------

void ManagerDocente::cerrarActaCursada(int legajoDocente) {
    int idComision;
    cout << "\n\t=== CERRAR ACTA DE CURSADA ===\n";
    cout << "\tID Comisión: ";
    cin >> idComision;

    if (!dictaComision(legajoDocente, idComision)) {
        cout << "\n\tERROR: Esta comisión NO pertenece al docente.\n";
        return;
    }

    int posCom = _archivoComisiones.buscarRegistro(idComision);
    if (posCom < 0) {
        cout << "\n\tERROR: La comisión no existe.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(posCom);

    if (com.getEliminado()) {
        cout << "\n\tEl acta YA estaba cerrada previamente.\n";
        return;
    }

    bool hayCursada = false;
    int total = _archivoExamen.contarRegistros();

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamen.leerRegistro(i);

        if (!ex.getEliminado() &&
            ex.getIdMateria() == com.getIdMateria() &&
            strcmp(ex.getTipo(), "Cursada") == 0)
        {
            hayCursada = true;
            break;
        }
    }

    if (!hayCursada) {
        cout << "\n\tERROR: Debe PUBLICAR notas de cursada antes de cerrar el acta.\n";
        return;
    }

    com.setEliminado(true);
    _archivoComisiones.modificarRegistro(com, posCom);

    cout << "\n\tActa CERRADA exitosamente.\n";
    cout << "\tYa NO pueden cargarse notas en esta comisión.\n";
}


void ManagerDocente::exportarCSV(int legajoDocente) {
    int idComision;
    cout << "\n\t=== EXPORTAR CURSADA A CSV ===\n";
    cout << "\tID Comisión: ";
    cin >> idComision;

    // 1) Verificar docente
    if (!dictaComision(legajoDocente, idComision)) {
        cout << "\n\tERROR: Esta comisión NO pertenece al docente.\n";
        return;
    }

    // 2) Traer comisión
    int posCom = _archivoComisiones.buscarRegistro(idComision);
    if (posCom < 0) {
        cout << "\n\tERROR: La comisión no existe.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(posCom);
    int idMateria = com.getIdMateria();

    // 🔥 3) Archivo destino
    string nombre = "cursada_comision_" + to_string(idComision) + ".csv";
    ofstream file(nombre);

    if (!file.is_open()) {
        cout << "\n\tERROR: No se pudo crear el archivo CSV.\n";
        return;
    }

    // Encabezado CSV
    file << "Legajo,Promedio,Condicion\n";

    int totalIns = _archivoInscripciones.contarRegistros();
    int totalEx = _archivoExamen.contarRegistros();

    // 4) Procesar alumnos
    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);

        if (ins.getIdComision() != idComision || ins.getEstado() != 0)
            continue;

        int legajo = ins.getLegajoAlumno();

        // Calcular notas
        int suma = 0, cant = 0;

        for (int j = 0; j < totalEx; j++) {
            Examen ex = _archivoExamen.leerRegistro(j);

            if (ex.getIdMateria() == idMateria &&
                ex.getLegajoAlumno() == legajo &&
                (strcmp(ex.getTipo(), "Parcial") == 0 ||
                 strcmp(ex.getTipo(), "Recuperatorio") == 0))
            {
                suma += ex.getNota();
                cant++;
            }
        }

        float prom = (cant == 0 ? 0 : (float)suma / cant);

        string condicion;
        if (_examenManager.estaPromocionado(legajo, idComision)) condicion = "Promo";
        else if (_examenManager.estaRegular(legajo, idComision)) condicion = "Regular";
        else condicion = "Libre";

        // Escribir fila CSV
        file << legajo << "," << prom << "," << condicion << "\n";
    }

    file.close();

    cout << "\n\tArchivo generado correctamente: " << nombre << "\n";
}


// --------------------------------------------------
// REPORTE DE CURSADA
// --------------------------------------------------

void ManagerDocente::reporteCursada(int idComision) {

    int pos = _archivoComisiones.buscarRegistro(idComision);
    if (pos < 0) {
        cout << "\nERROR: Comisión inexistente.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(pos);
    int idMateria = com.getIdMateria();

    cout << "\n=========== REPORTE DE CURSADA ===========\n";
    cout << "Materia ID: " << idMateria << "\n";
    cout << "Comisión:   " << idComision << "\n\n";

    cout << left
         << setw(10) << "Legajo"
         << setw(10) << "P1"
         << setw(10) << "P2"
         << setw(10) << "R1"
         << setw(10) << "R2"
         << setw(10) << "Prom"
         << setw(12) << "Condición"
         << "\n---------------------------------------------------------------\n";

    int totalIns = _archivoInscripciones.contarRegistros();
    int totalEx  = _archivoExamen.contarRegistros();

    for (int i = 0; i < totalIns; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);

        if (ins.getIdComision() != idComision || ins.getEstado() != 0) continue;

        int legajo = ins.getLegajoAlumno();

        int p1 = -1, p2 = -1;
        int r1 = -1, r2 = -1;
        int suma = 0, cant = 0;

        for (int j = 0; j < totalEx; j++) {
            Examen ex = _archivoExamen.leerRegistro(j);

            if (ex.getIdMateria() == idMateria &&
                ex.getLegajoAlumno() == legajo)
            {
                if (strcmp(ex.getTipo(), "Parcial") == 0) {
                    if (ex.getNumeroParcial() == 1) p1 = ex.getNota();
                    if (ex.getNumeroParcial() == 2) p2 = ex.getNota();
                    suma += ex.getNota();
                    cant++;
                }

                if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
                    if (ex.getNumeroParcial() == 1) r1 = ex.getNota();
                    if (ex.getNumeroParcial() == 2) r2 = ex.getNota();
                    suma += ex.getNota();
                    cant++;
                }
            }
        }

        float prom = (cant == 0 ? 0 : (float)suma / cant);

        string condicion;
        if (_examenManager.estaPromocionado(legajo, idComision)) condicion = "Promo";
        else if (_examenManager.estaRegular(legajo, idComision)) condicion = "Regular";
        else condicion = "Libre";

        cout << left
             << setw(10) << legajo
             << setw(10) << (p1 == -1 ? "-" : to_string(p1))
             << setw(10) << (p2 == -1 ? "-" : to_string(p2))
             << setw(10) << (r1 == -1 ? "-" : to_string(r1))
             << setw(10) << (r2 == -1 ? "-" : to_string(r2))
             << setw(10) << fixed << setprecision(1) << prom
             << setw(12) << condicion
             << "\n";
    }

    cout << "---------------------------------------------------------------\n";
}
