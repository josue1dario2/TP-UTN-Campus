#include <limits>
#include "ManagerDocente.h"
#include "ManagerInscripcionComision.h"
#include "Validacion.h"
#include "ArchivoAlumno.h"
#include "Alumno.h"
#include "utils.h"
#include <fstream>
#include <vector>
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

    nuevo.cargarDatosSinLegajo();
    int nuevoLegajo = generarLegajo();
    nuevo.setLegajo(nuevoLegajo);

    cout << "\n\tLegajo asignado automáticamente: " << nuevoLegajo << "\n";

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

    // Preguntar al usuario
    char opcion;
    cout << "\n\t¿Desea incluir también los docentes INACTIVOS? (s/n): ";
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool incluirInactivos = (opcion == 's' || opcion == 'S');

    cout << "\n\t=== LISTADO DE DOCENTES ===\n";
    mostrarEncabezado();

    bool hayDatos = false;

    for (int i = 0; i < total; i++) {
        Docente doc = _archivoDocentes.leerRegistro(i);

        // Si NO quiere ver inactivos → omitir eliminados
        if (!incluirInactivos && doc.getEliminado()) {
            continue;
        }

        mostrarRegistro(doc);
        hayDatos = true;
    }

    mostrarPie();

    if (!hayDatos) {
        if (incluirInactivos)
            cout << "\n\tNo hay docentes activos ni inactivos registrados.\n";
        else
            cout << "\n\tNo hay docentes ACTIVOS registrados.\n";
    }
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
        cout << "\n\tDatos actualizados correctamente.\n";
    } else {
        cout << "\n\tError al actualizar los datos.\n";
    }

}

bool ManagerDocente::solicitarBaja(int legajo) {
    int pos = _archivoDocentes.buscarRegistro(legajo);

    if (pos < 0) {
        cout << "\n\tDocente no encontrado.\n";
        return false;
    }

    Docente doc = _archivoDocentes.leerRegistro(pos);

    if (doc.getEliminado()) {
        cout << "\n\tEl docente ya está dado de baja.\n";
        return false;
    }

    cout << "\n\t¿CONFIRMAR SOLICITUD DE BAJA? (1=Sí / 0=No): ";
    int opc;
    cin >> opc;

    if (opc != 1) {
        cout << "\n\tOperación cancelada.\n";
        return false;
    }

    doc.setEliminado(true);

    if (_archivoDocentes.modificarRegistro(doc, pos)) {
        cout << "\n\tBaja solicitada correctamente.\n";
        return true;
    }
    else {
        cout << "\n\tError al realizar la baja.\n";
        return false;
    }
}



// --------------------------------------------------
// FUNCIONES ACADÉMICAS
// --------------------------------------------------
void ManagerDocente::verMisComisiones(int legajo) {
    cout << "\n\t=== MIS COMISIONES ===\n";

    int total = _archivoComisiones.contarRegistros();
    bool tiene = false;

    // Primero verificamos si tiene comisiones
    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);
        if (!c.getEliminado() && c.getLegajoDocente() == legajo) {
            tiene = true;
            break;
        }
    }

    if (!tiene) {
        cout << "\tNo se encontraron comisiones asignadas.\n";
        return;
    }

    cout << "\t+------------+------------+------------+------------+------------+\n";
    cout << "\t| ID Comisión| ID Materia | Turno      | Modalidad  | Año        |\n";
    cout << "\t+------------+------------+------------+------------+------------+\n";

    for (int i = 0; i < total; i++) {
        Comision c = _archivoComisiones.leerRegistro(i);

        if (!c.getEliminado() && c.getLegajoDocente() == legajo) {
            cout << "\t| " << setw(10) << right << c.getIdComision()
                 << " | " << setw(10) << right << c.getIdMateria()
                 << " | " << setw(10) << left  << c.getTurno()
                 << " | " << setw(10) << left  << c.getModalidad()
                 << " | " << setw(10) << right << c.getAnio() << " |\n";
        }
    }
    cout << "\t+------------+------------+------------+------------+------------+\n";
}

void ManagerDocente::seleccionarComisionParaVerAlumnos(int legajoDocente) {
    ArchivoComision archCom;
    ArchivoMateria archMat;
    ArchivoDocente archDoc;

    vector<int> opciones;   // Guardará los ID reales

    cout << "\n=== MIS COMISIONES ===\n\n";

    cout << "+--------+------------------------------+--------------+--------------+\n";
    cout << "| OPCION |           MATERIA            |    TURNO     |  MODALIDAD   |\n";
    cout << "+--------+------------------------------+--------------+--------------+\n";

    int total = archCom.contarRegistros();
    bool hay = false;

    for (int i = 0; i < total; i++) {
        Comision c = archCom.leerRegistro(i);

        if (c.getEliminado()) continue;
        if (c.getLegajoDocente() != legajoDocente) continue;

        hay = true;

        // Guardamos la comisión real
        opciones.push_back(c.getIdComision());
        int op = opciones.size();

        // Materia
        string mat = "N/A";
        int posMat = archMat.buscarRegistro(c.getIdMateria());
        if (posMat >= 0) mat = quitarAcentos(archMat.leerRegistro(posMat).getNombre());

        // Turno / Modalidad
        string turno = quitarAcentos(c.getTurno());
        string modalidad = quitarAcentos(c.getModalidad());

        cout << "| " << setw(6) << left << op
             << " | " << setw(28) << left << mat
             << " | " << setw(12) << left << turno
             << " | " << setw(12) << left << modalidad
             << " |\n";
    }

    cout << "+--------+------------------------------+--------------+--------------+\n";

    if (!hay) {
        cout << "\nNo tenés comisiones asignadas.\n";
        return;
    }

    // Seleccionar opción
    int seleccion = Validacion::validarEntero("\nSeleccione opción: ");

    if (seleccion < 1 || seleccion > opciones.size()) {
        cout << "\nERROR: Opción inválida.\n";
        return;
    }

    int idReal = opciones[seleccion - 1]; // ID REAL de la comisión

    verAlumnosDeComision(idReal);
}

void ManagerDocente::verAlumnosDeComision(int idComision) {

    cout << "\n\t=== ALUMNOS DE LA COMISIÓN " << idComision << " ===\n\n";

    ArchivoAlumno archAlu("Alumnos.dat");

    int total = _archivoInscripciones.contarRegistros();
    bool hay = false;

    // Verificar si hay alumnos
    for (int i = 0; i < total; i++) {
        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);
        if (ins.getIdComision() == idComision && ins.getEstado() == 0) {
            hay = true;
            break;
        }
    }

    if (!hay) {
        cout << "\tNo hay alumnos inscriptos en esta comisión.\n";
        return;
    }

    // TABLA
    cout << "\t+--------+-------------------------------+----------------------+\n";
    cout << "\t| Legajo | Alumno                        | Fecha Inscripción    |\n";
    cout << "\t+--------+-------------------------------+----------------------+\n";

    for (int i = 0; i < total; i++) {

        InscripcionComision ins = _archivoInscripciones.leerRegistro(i);

        if (ins.getIdComision() == idComision && ins.getEstado() == 0) {

            // Buscar datos del alumno
            int posAlu = archAlu.buscarRegistro(ins.getLegajoAlumno());
            string nombreCompleto = "N/A";

            if (posAlu >= 0) {
                Alumno a = archAlu.leerRegistro(posAlu);
                nombreCompleto = string(a.getNombre()) + " " + a.getApellido();
                nombreCompleto = quitarAcentos(nombreCompleto.c_str());
            }

            // Fecha sin sprintf → usando strings
            Fecha f = ins.getFecha();

            auto twoDigits = [](int n) {
                return (n < 10 ? "0" : "") + to_string(n);
            };

            string fechaStr = twoDigits(f.getDia()) + "/" +
                              twoDigits(f.getMes()) + "/" +
                              to_string(f.getAnio());

            // Mostrar fila
            cout << "\t| " << setw(6) << left << ins.getLegajoAlumno()
                 << " | " << setw(29) << left << nombreCompleto
                 << " | " << setw(20) << left << fechaStr
                 << " |\n";
        }
    }

    cout << "\t+--------+-------------------------------+----------------------+\n";
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
    clearScreen();
    cout << "\n\t=== CARGA DE NOTAS FINALES ===\n";

    ArchivoComision archCom;
    ArchivoMateria archMat;
    ArchivoInscripcionComision archIns;
    ArchivoAlumno archAlu;

    int totalCom = archCom.contarRegistros();
    if (totalCom == 0) {
        cout << "\nNo hay comisiones registradas.\n";
        return;
    }

    // ============================================
    // 1) LISTAR COMISIONES DEL DOCENTE
    // ============================================
    int* comisiones = new int[totalCom];
    int cantCom = 0;

    cout << "\n=== COMISIONES QUE DICTA EL DOCENTE ===\n\n";

    cout << "+--------+--------------+-------------------------------------------+\n";
    cout << "| OPCION | ID COMISION  |                 MATERIA                   |\n";
    cout << "+--------+--------------+-------------------------------------------+\n";

    for (int i = 0; i < totalCom; i++) {
        Comision c = archCom.leerRegistro(i);

        if (!c.getEliminado() && c.getLegajoDocente() == legajoDocente) {
            string mat = "N/A";
            int posM = archMat.buscarRegistro(c.getIdMateria());
            if (posM >= 0) mat = quitarAcentos(archMat.leerRegistro(posM).getNombre());

            comisiones[cantCom] = c.getIdComision();

            cout << "| " << setw(6) << left << (cantCom + 1)
                 << " | " << setw(12) << left << c.getIdComision()
                 << " | " << setw(41) << left << mat
                 << " |\n";

            cantCom++;
        }
    }

    cout << "+--------+--------------+-------------------------------------------+\n";

    if (cantCom == 0) {
        cout << "\nNo dictas ninguna comisión.\n";
        delete[] comisiones;
        return;
    }

    int opcionC = Validacion::validarEntero("\nSeleccione opción de comisión: ");
    if (opcionC < 1 || opcionC > cantCom) {
        cout << "\nOpción inválida.\n";
        delete[] comisiones;
        return;
    }

    int idComision = comisiones[opcionC - 1];
    delete[] comisiones;


    // ============================================
    // 2) LISTAR ALUMNOS INSCRIPTOS A EXAMEN FINAL
    // ============================================
    int totalIns = archIns.contarRegistros();
    int* alumnos = new int[totalIns];
    int cantAlu = 0;

    cout << "\n=== ALUMNOS INSCRIPTOS A FINAL ===\n\n";

    cout << "+--------+--------------+-----------------------------+\n";
    cout << "| OPCION |   LEGAJO     |         ALUMNO              |\n";
    cout << "+--------+--------------+-----------------------------+\n";

    ArchivoExamen archEx;
    int totalEx = archEx.contarRegistros();

    for (int i = 0; i < totalEx; i++) {
        Examen ex = archEx.leerRegistro(i);

        if (ex.getIdMateria() == archCom.leerRegistro(archCom.buscarRegistro(idComision)).getIdMateria()
            && strcmp(ex.getTipo(), "Final") == 0
            && !ex.getEliminado()
            && !ex.getCorregido())     // SOLO FINALES SIN CORREGIR
        {
            int legajo = ex.getLegajoAlumno();

            // Datos del alumno
            int posA = archAlu.buscarRegistro(legajo);
            if (posA < 0) continue;

            Alumno a = archAlu.leerRegistro(posA);
            string nombre = quitarAcentos((string(a.getNombre()) + " " + a.getApellido()).c_str());

            alumnos[cantAlu] = legajo;

            cout << "| " << setw(6) << left << (cantAlu + 1)
                 << " | " << setw(12) << left << legajo
                 << " | " << setw(27) << left << nombre
                 << " |\n";

            cantAlu++;
        }
    }

    cout << "+--------+--------------+-----------------------------+\n";

    if (cantAlu == 0) {
        cout << "\nNo hay alumnos inscriptos a final.\n";
        delete[] alumnos;
        return;
    }

    int opcionA = Validacion::validarEntero("\nSeleccione opción de alumno: ");
    if (opcionA < 1 || opcionA > cantAlu) {
        cout << "\nOpción inválida.\n";
        delete[] alumnos;
        return;
    }

    int legajoAlumno = alumnos[opcionA - 1];
    delete[] alumnos;

    // ============================================
    // 3) CARGAR NOTA DEL FINAL
    // ============================================
    int nota = Validacion::validarEnteroEnRango("\nIngrese Nota Final (0-10): ", 0, 10);

    _examenManager.cargarFinal(legajoAlumno, idComision, nota);
}


// --------------------------------------------------
// PRESENTACIÓN
// --------------------------------------------------
void ManagerDocente::mostrarEncabezado() {
    cout << "\t+--------+---------------------------+---------------------------+--------------------+---------+\n";
    cout << "\t| Legajo | Nombre                    | Apellido                  | Telefono           | Estado  |\n";
    cout << "\t+--------+---------------------------+---------------------------+--------------------+---------+\n";
}

void ManagerDocente::mostrarRegistro(const Docente& doc) {

    string nombre   = quitarAcentos(doc.getNombre());
    string apellido = quitarAcentos(doc.getApellido());

    cout << "\t| " << setw(6) << right << doc.getLegajo()
         << " | " << setw(25) << left << nombre
         << " | " << setw(25) << left << apellido
         << " | " << setw(18) << left << doc.getTelefono()
         << " | " << setw(7) << left << (doc.getEliminado() ? "Baja" : "Activo")
         << " |\n";
}

void ManagerDocente::mostrarPie() {
    cout << "\t+--------+---------------------------+---------------------------+--------------------+---------+\n";
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
int ManagerDocente::generarLegajo() {
    int total = _archivoDocentes.contarRegistros();
    int maxLegajo = 999;

    for (int i = 0; i < total; i++) {
        Docente d = _archivoDocentes.leerRegistro(i);
        if (d.getLegajo() > maxLegajo) {
            maxLegajo = d.getLegajo();
        }
    }

    int nuevo = maxLegajo + 1;

    if (nuevo > 9999) {
        cout << "\nERROR: Limite máximo de legajos alcanzado.\n";
        return -1;
    }

    return nuevo;
}
void ManagerDocente::borrarDefinitivo() {
    cout << "\nIngrese legajo del docente a borrar definitivamente: ";
    int legajo;
    cin >> legajo;

    int total = _archivoDocentes.contarRegistros();
    int pos = -1;
    Docente encontradoDoc;

    for (int i = 0; i < total; i++) {
        Docente d = _archivoDocentes.leerRegistro(i);
        if (d.getLegajo() == legajo) {
            pos = i;
            encontradoDoc = d;
            break;
        }
    }

    if (pos == -1) {
        cout << "\nNo existe un docente con ese legajo.\n";
        return;
    }

    cout << "\nATENCIÓN: Está a punto de borrar DEFINITIVAMENTE al docente:\n";
    cout << "  Nombre: " << encontradoDoc.getNombre() << " " << encontradoDoc.getApellido() << endl;
    cout << "  Legajo: " << encontradoDoc.getLegajo() << endl;

    cout << "\n¿Está seguro que desea BORRAR este registro? (S/N): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'S' && confirm != 's') {
        cout << "\nOperación cancelada. No se borró ningún registro.\n";
        return;
    }

    ArchivoDocente temp("Docentes_temp.dat");

    for (int i = 0; i < total; i++) {
        if (i == pos) continue;
        Docente d = _archivoDocentes.leerRegistro(i);
        temp.agregarRegistro(d);
    }

    remove("Docentes.dat");
    rename("Docentes_temp.dat", "Docentes.dat");

    cout << "\nDocente borrado DEFINITIVAMENTE.\n";
}
void ManagerDocente::corregirParciales(int legajoDocente) {

    clearScreen();
    cout << "\n=== EXÁMENES PENDIENTES DE CORRECCIÓN ===\n\n";

    ArchivoExamen   archEx("Examenes.dat");
    ArchivoComision archCom("Comisiones.dat");
    ArchivoAlumno   archAlu("Alumnos.dat");
    ArchivoMateria  archMat("Materias.dat");

    int totalEx = archEx.contarRegistros();

    // ======================================================
    // RESERVA DE MEMORIA DINÁMICA PARA GUARDAR OPCIONES
    // ======================================================
    int* opciones = new int[totalEx];
    int cantidadOpciones = 0;

    // ======================================================
    // PRIMER PASO: determinar si hay exámenes para mostrar
    // ======================================================
    for (int i = 0; i < totalEx; i++) {

        Examen ex = archEx.leerRegistro(i);
        if (ex.getEliminado() || ex.getCorregido()) continue;

        bool dicta = false;
        int totalCom = archCom.contarRegistros();

        for (int c = 0; c < totalCom; c++) {
            Comision com = archCom.leerRegistro(c);

            if (!com.getEliminado() &&
                com.getIdMateria() == ex.getIdMateria() &&
                com.getLegajoDocente() == legajoDocente)
            {
                dicta = true;
                break;
            }
        }

        if (!dicta) continue;

        cantidadOpciones++;
    }

    // ======================================================
    // SI NO HAY EXÁMENES → NO MOSTRAR TABLA VACÍA
    // ======================================================
    if (cantidadOpciones == 0) {
        delete[] opciones;
        cout << "No hay exámenes pendientes para sus comisiones.\n";
        pauseScreen();
        return;
    }

    // ======================================================
    // MOSTRAR TABLA SOLO SI HAY EXÁMENES
    // ======================================================
    cout << "+--------+---------------------------+------------------------------------+-------------+-------------+\n";
    cout << "| OPCION |          ALUMNO           |                MATERIA             |    TIPO     |    FECHA    |\n";
    cout << "+--------+---------------------------+------------------------------------+-------------+-------------+\n";

    cantidadOpciones = 0; // reinicio para el llenado real

    for (int i = 0; i < totalEx; i++) {

        Examen ex = archEx.leerRegistro(i);
        if (ex.getEliminado() || ex.getCorregido()) continue;

        // Verificar que el docente dicta esa materia
        bool dicta = false;
        int totalCom = archCom.contarRegistros();

        for (int c = 0; c < totalCom; c++) {
            Comision com = archCom.leerRegistro(c);

            if (!com.getEliminado() &&
                com.getIdMateria() == ex.getIdMateria() &&
                com.getLegajoDocente() == legajoDocente)
            {
                dicta = true;
                break;
            }
        }

        if (!dicta) continue;

        // ================================
        // Alumno
        // ================================
        string alumnoStr = "N/A";
        int posAlu = archAlu.buscarRegistro(ex.getLegajoAlumno());

        if (posAlu >= 0) {
            Alumno a = archAlu.leerRegistro(posAlu);
            alumnoStr = quitarAcentos(a.getNombre());
            alumnoStr += " ";
            alumnoStr += quitarAcentos(a.getApellido());
            alumnoStr += " (";
            alumnoStr += to_string(a.getLegajo());
            alumnoStr += ")";
        }

        // ================================
        // Materia
        // ================================
        string materiaStr = "N/A";
        int posMat = archMat.buscarRegistro(ex.getIdMateria());

        if (posMat >= 0) {
            Materia m = archMat.leerRegistro(posMat);
            materiaStr = quitarAcentos(m.getNombre());
        }

        // ================================
        // Tipo
        // ================================
        string tipoStr = ex.getTipo();
        if (strcmp(ex.getTipo(), "Parcial") == 0 ||
            strcmp(ex.getTipo(), "Recuperatorio") == 0)
        {
            tipoStr += " ";
            tipoStr += to_string(ex.getNumeroParcial());
        }

        // ================================
        // Fecha
        // ================================
        Fecha f = ex.getFecha();
        string fechaStr =
            to_string(f.getDia()) + "/" +
            to_string(f.getMes()) + "/" +
            to_string(f.getAnio());

        // Guardamos el ID real en memoria dinámica
        opciones[cantidadOpciones] = ex.getIdExamen();
        cantidadOpciones++;

        // Mostrar fila
        cout << "| " << setw(6) << left << cantidadOpciones
             << " | " << setw(25) << left << alumnoStr
             << " | " << setw(34) << left << materiaStr
             << " | " << setw(11) << left << tipoStr
             << " | " << setw(11) << left << fechaStr
             << " |\n";
    }

    cout << "+--------+---------------------------+------------------------------------+-------------+-------------+\n";

    // ======================================================
    // SELECCIÓN POR OPCIÓN
    // ======================================================
    int opcion = Validacion::validarEntero("\nSeleccione opción: ");

    if (opcion < 1 || opcion > cantidadOpciones) {
        cout << "\nERROR: opción inválida.\n";
        delete[] opciones;
        pauseScreen();
        return;
    }

    int idExamen = opciones[opcion - 1];

    delete[] opciones; // liberar memoria

    // ======================================================
    // CORRECCIÓN
    // ======================================================
    int posEx = archEx.buscarRegistro(idExamen);

    if (posEx < 0) {
        cout << "\nERROR: examen no encontrado.\n";
        pauseScreen();
        return;
    }

    Examen ex = archEx.leerRegistro(posEx);

    int nota = Validacion::validarEnteroEnRango("Ingrese nota (0–10): ", 0, 10);

    ex.setNota(nota);
    ex.setCorregido(true);

    if (archEx.modificarRegistro(ex, posEx))
        cout << "\nExamen corregido correctamente.\n";
    else
        cout << "\nError al guardar la corrección.\n";

    pauseScreen();
}
