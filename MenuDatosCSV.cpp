#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "MenuDatosCSV.h"
#include "utils.h"
#include <cstdlib>

using namespace std;

MenuDatosCSV::MenuDatosCSV()
{
    _cantidadOpciones=11;

}

void MenuDatosCSV::mostrar()
{
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuDatosCSV::mostrarOpciones()
{
    clearScreen();
    cout << endl;
    cout << "\n\tEXPORTAR DATOS A ARCHIVO CSV\n";
    cout << "\t--------------------------------------\n";
    cout << "\t 1 - ALUMNOS\n";
    cout << "\t 2 - DOCENTES\n";
    cout << "\t 3 - CARRERAS\n";
    cout << "\t 4 - MATERIAS\n";
    cout << "\t 5 - COMISIONES\n";
    cout << "\t 6 - INSCRIPCIONES\n";
    cout << "\t 7 - MESAS DE EXAMEN\n";
    cout << "\t 8 - EVALUACIONES\n";
    cout << "\t 9 - CALIFICACIONES\n";
    cout << "\t10 - CORRELATIVAS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t11 - TODOS LOS ARCHIVOS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t0 - Volver\n";

}

void MenuDatosCSV::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            exportarAlumnos();
            break;
        case 2:
            exportarDocentes();
            break;
        case 3:
            exportarCarreras();
            break;
        case 4:
            exportarMaterias();
            break;
        case 5:
            exportarComisiones();
            break;
        case 6:
            exportarInscripciones();
            break;
        case 7:
            exportarMesasExamen();
            break;
        case 8:
            exportarEvaluaciones();
            break;
        case 9:
            exportarCalificaciones();
            break;
        case 10:
            exportarCorrelativas();
            break;
        case 11:
            exportarTodos();
            break;
        case 0:
            // Volver
            break;
        default:
            cout << "\n\tOpción inválida.\n";
            break;
    }
}

int MenuDatosCSV::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    string mensaje="\t--------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);
    return opcion;

}





// ========================================================
// MÉTODOS DE EXPORTACIÓN A CSV
// ========================================================

void MenuDatosCSV::exportarAlumnos() {
    ArchivoAlumno archivo("Alumnos.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay alumnos para exportar.\n";
        return;
    }
    
    ofstream file("alumnos.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "Legajo,DNI,Nombre,Apellido,Telefono,Email,FechaIngreso,Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        Alumno alu = archivo.leerRegistro(i);
        if (!alu.getEliminado()) {
            Fecha f = alu.getFechaIngreso();
            file << alu.getLegajo() << ","
                 << alu.getDni() << ","
                 << alu.getNombre() << ","
                 << alu.getApellido() << ","
                 << alu.getTelefono() << ","
                 << alu.getEmail() << ","
                 << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ","
                 << "Activo\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'alumnos.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarDocentes() {
    ArchivoDocente archivo("Docentes.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay docentes para exportar.\n";
        return;
    }
    
    ofstream file("docentes.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "Legajo,DNI,Nombre,Apellido,Telefono,Email,FechaIngreso,Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        Docente doc = archivo.leerRegistro(i);
        if (!doc.getEliminado()) {
            Fecha f = doc.getFechaIngreso();
            file << doc.getLegajo() << ","
                 << doc.getDni() << ","
                 << doc.getNombre() << ","
                 << doc.getApellido() << ","
                 << doc.getTelefono() << ","
                 << doc.getEmail() << ","
                 << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ","
                 << "Activo\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'docentes.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarCarreras() {
    ArchivoCarrera archivo("Carreras.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay carreras para exportar.\n";
        return;
    }
    
    ofstream file("carreras.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "ID,Nombre,Duracion(Cuatrimestres),Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        Carrera car = archivo.leerRegistro(i);
        if (!car.getEliminado()) {
            file << car.getIdCarrera() << ","
                 << car.getNombre() << ","
                 << car.getDuracionCuatrimestres() << ","
                 << "Activa\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'carreras.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarMaterias() {
    ArchivoMateria archivo("Materias.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay materias para exportar.\n";
        return;
    }
    
    ofstream file("materias.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "ID,Nombre,Cuatrimestre,Estado\n";

    // Datos
    for (int i = 0; i < total; i++) {
        Materia mat = archivo.leerRegistro(i);
        if (!mat.getEliminado()) {
            file << mat.getIdMateria() << ","
                 << mat.getNombre() << ","
                 << mat.getCuatrimestre() << ","
                 << "Activa\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'materias.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarComisiones() {
    ArchivoComision archivo("Comisiones.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay comisiones para exportar.\n";
        return;
    }
    
    ofstream file("comisiones.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "IDComision,IDMateria,LegajoDocente,Turno,Modalidad,Cuatrimestre,Anio,Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        Comision com = archivo.leerRegistro(i);
        if (!com.getEliminado()) {
            file << com.getIdComision() << ","
                 << com.getIdMateria() << ","
                 << com.getLegajoDocente() << ","
                 << com.getTurno() << ","
                 << com.getModalidad() << ","
                 << com.getCuatrimestre() << ","
                 << com.getAnio() << ","
                 << "Activa\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'comisiones.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarInscripciones() {
    ArchivoInscripcionComision archivo("InscripcionesComision.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay inscripciones para exportar.\n";
        return;
    }
    
    ofstream file("inscripciones.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "LegajoAlumno,IDComision,Fecha,Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        InscripcionComision ins = archivo.leerRegistro(i);
        Fecha f = ins.getFecha();
        string estado;
        switch (ins.getEstado()) {
            case 0: estado = "Activa"; break;
            case 1: estado = "Pendiente de baja"; break;
            case 2: estado = "Baja"; break;
            default: estado = "Desconocido"; break;
        }
        
        file << ins.getLegajoAlumno() << ","
             << ins.getIdComision() << ","
             << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ","
             << estado << "\n";
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'inscripciones.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarMesasExamen() {
    ArchivoExamen archivo("Examenes.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay exámenes para exportar.\n";
        return;
    }
    
    ofstream file("mesas_examen.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "IDExamen,IDMateria,LegajoAlumno,Tipo,NumeroParcial,Fecha,Nota,Corregido\n";
    
    // Datos
    int contador = 0;
    for (int i = 0; i < total; i++) {
        Examen ex = archivo.leerRegistro(i);
        if (!ex.getEliminado() && strcmp(ex.getTipo(), "Final") == 0) {
            Fecha f = ex.getFecha();
            file << ex.getIdExamen() << ","
                 << ex.getIdMateria() << ","
                 << ex.getLegajoAlumno() << ","
                 << ex.getTipo() << ","
                 << ex.getNumeroParcial() << ","
                 << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ","
                 << ex.getNota() << ","
                 << (ex.getCorregido() ? "Si" : "No") << "\n";
            contador++;
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'mesas_examen.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << contador << "\n";
}

void MenuDatosCSV::exportarEvaluaciones() {
    ArchivoExamen archivo("Examenes.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay evaluaciones para exportar.\n";
        return;
    }
    
    ofstream file("evaluaciones.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "IDExamen,IDMateria,LegajoAlumno,Tipo,NumeroParcial,Fecha,Nota,Corregido\n";
    
    // Datos
    int contador = 0;
    for (int i = 0; i < total; i++) {
        Examen ex = archivo.leerRegistro(i);
        if (!ex.getEliminado() && (strcmp(ex.getTipo(), "Parcial") == 0 || 
                                     strcmp(ex.getTipo(), "Recuperatorio") == 0)) {
            Fecha f = ex.getFecha();
            file << ex.getIdExamen() << ","
                 << ex.getIdMateria() << ","
                 << ex.getLegajoAlumno() << ","
                 << ex.getTipo() << ","
                 << ex.getNumeroParcial() << ","
                 << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ","
                 << ex.getNota() << ","
                 << (ex.getCorregido() ? "Si" : "No") << "\n";
            contador++;
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'evaluaciones.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << contador << "\n";
}

void MenuDatosCSV::exportarCalificaciones() {
    ArchivoExamen archivo("Examenes.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay calificaciones para exportar.\n";
        return;
    }
    
    ofstream file("calificaciones.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "IDExamen,IDMateria,LegajoAlumno,Tipo,Nota,Fecha,Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        Examen ex = archivo.leerRegistro(i);
        if (!ex.getEliminado() && ex.getCorregido()) {
            Fecha f = ex.getFecha();
            file << ex.getIdExamen() << ","
                 << ex.getIdMateria() << ","
                 << ex.getLegajoAlumno() << ","
                 << ex.getTipo() << ","
                 << ex.getNota() << ","
                 << f.getDia() << "/" << f.getMes() << "/" << f.getAnio() << ","
                 << (ex.getNota() >= 4 ? "Aprobado" : "Desaprobado") << "\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'calificaciones.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarCorrelativas() {
    ArchivoCorrelativa archivo("Correlativas.dat");
    int total = archivo.contarRegistros();
    
    if (total == 0) {
        cout << "\n\tNo hay correlativas para exportar.\n";
        return;
    }
    
    ofstream file("correlativas.csv");
    if (!file.is_open()) {
        cout << "\n\tError al crear el archivo CSV.\n";
        return;
    }
    
    // Encabezado
    file << "IDMateriaObjetivo,IDMateriaRequisito,Estado\n";
    
    // Datos
    for (int i = 0; i < total; i++) {
        Correlativa cor = archivo.leerRegistro(i);
        if (!cor.getEliminado()) {
            file << cor.getIdMateriaObjetivo() << ","
                 << cor.getIdMateriaRequisito() << ","
                 << "Activa\n";
        }
    }
    
    file.close();
    cout << "\n\tEXITO: Archivo 'correlativas.csv' generado correctamente.\n";
    cout << "\tTotal de registros exportados: " << total << "\n";
}

void MenuDatosCSV::exportarTodos() {
    cout << "\n\t=== EXPORTANDO TODOS LOS ARCHIVOS ===\n\n";
    
    exportarAlumnos();
    cout << endl;
    
    exportarDocentes();
    cout << endl;
    
    exportarCarreras();
    cout << endl;
    
    exportarMaterias();
    cout << endl;
    
    exportarComisiones();
    cout << endl;
    
    exportarInscripciones();
    cout << endl;
    
    exportarMesasExamen();
    cout << endl;
    
    exportarEvaluaciones();
    cout << endl;
    
    exportarCalificaciones();
    cout << endl;
    
    exportarCorrelativas();
    
    cout << "\n\t=========================================\n";
    cout << "\tEXPORTACION COMPLETA FINALIZADA\n";
    cout << "\t=========================================\n";
}
