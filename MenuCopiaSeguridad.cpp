#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include "MenuCopiaSeguridad.h"
#include "utils.h"
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

MenuCopiaSeguridad::MenuCopiaSeguridad()
{
    _cantidadOpciones=11;
}

void MenuCopiaSeguridad::mostrar(int eleccion)
{
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion(eleccion);
        clearScreen();
        if (opcion != 0) {
            ejecutarOpcion(opcion, eleccion);
            pauseScreen();
        }
    } while (opcion != 0);
}

void MenuCopiaSeguridad::mostrarOpciones(int eleccion)
{
    clearScreen();
    cout << endl;
    if (eleccion == 1) {
        cout << "\t=== REALIZAR COPIA DE SEGURIDAD ===\n";
    } else if (eleccion == 2) {
        cout << "\t=== RESTAURAR COPIA DE SEGURIDAD ===\n";
    }
    cout << "\t--------------------------------------\n";
    cout << "\t 1 - ALUMNOS\n";
    cout << "\t 2 - DOCENTES\n";
    cout << "\t 3 - CARRERAS\n";
    cout << "\t 4 - MATERIAS\n";
    cout << "\t 5 - COMISIONES\n";
    cout << "\t 6 - INSCRIPCIONES\n";
    cout << "\t 7 - MESAS DE EXAMEN\n";
    cout << "\t 8 - EVALUACIONES (EXAMENES)\n";
    cout << "\t 9 - CALIFICACIONES (EXAMENES)\n";
    cout << "\t10 - CORRELATIVAS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t11 - TODOS LOS ARCHIVOS\n";
    cout << "\t--------------------------------------\n";
    cout << "\t0 - Volver\n";
}

void MenuCopiaSeguridad::ejecutarOpcion(int opcion, int eleccion)
{
    if (opcion == 11) {
        // Todos los archivos
        if (eleccion == 1) {
            copiarTodos();
        } else if (eleccion == 2) {
            restaurarTodos();
        }
        return;
    }

    string nombreArchivo = obtenerNombreArchivo(opcion);

    if (nombreArchivo.empty()) {
        cout << "\n\tOpción inválida.\n";
        return;
    }

    if (eleccion == 1) {
        // Realizar copia de seguridad
        copiarArchivo(nombreArchivo);
    } else if (eleccion == 2) {
        // Restaurar copia de seguridad
        restaurarArchivo(nombreArchivo);
    }
}

int MenuCopiaSeguridad::seleccionOpcion(int eleccion)
{
    int opcion;
    mostrarOpciones(eleccion);
    string mensaje="\t--------------------------------------\n";
    mensaje+="\tOpción: ";
    opcion = validar.validarEnteroEnRango(mensaje,0,_cantidadOpciones);
    return opcion;
}

// ========================================================
// MÉTODOS AUXILIARES
// ========================================================

string MenuCopiaSeguridad::obtenerNombreArchivo(int opcion) {
    switch (opcion) {
        case 1: return "Alumnos.dat";
        case 2: return "Docentes.dat";
        case 3: return "Carreras.dat";
        case 4: return "Materias.dat";
        case 5: return "Comisiones.dat";
        case 6: return "InscripcionesComision.dat";
        case 7:
        case 8:
        case 9: return "Examenes.dat";  // 7, 8 y 9 usan el mismo archivo
        case 10: return "Correlativas.dat";
        default: return "";
    }
}

void MenuCopiaSeguridad::copiarArchivo(const string& nombreArchivo) {
    try {
        // Crear carpeta backup si no existe
        if (!fs::exists("backup")) {
            fs::create_directory("backup");
        }

        string origen = nombreArchivo;
        string destino = "backup/" + nombreArchivo + ".bak";

        // Verificar si existe el archivo origen
        if (!fs::exists(origen)) {
            cout << "\n\tADVERTENCIA: El archivo '" << nombreArchivo << "' no existe.\n";
            return;
        }

        // Copiar archivo
        fs::copy_file(origen, destino, fs::copy_options::overwrite_existing);

        cout << "\n\tEXITO: Copia de seguridad realizada correctamente.\n";
        cout << "\tArchivo: " << nombreArchivo << "\n";
        cout << "\tBackup: " << destino << "\n";

    } catch (const fs::filesystem_error& e) {
        cout << "\n\tERROR: No se pudo realizar la copia de seguridad.\n";
        cout << "\tDetalles: " << e.what() << "\n";
    }
}

void MenuCopiaSeguridad::restaurarArchivo(const string& nombreArchivo) {
    try {
        string origen = "backup/" + nombreArchivo + ".bak";
        string destino = nombreArchivo;

        // Verificar si existe el backup
        if (!fs::exists(origen)) {
            cout << "\n\tADVERTENCIA: No existe una copia de seguridad para '" << nombreArchivo << "'.\n";
            cout << "\tRuta esperada: " << origen << "\n";
            return;
        }

        // Confirmar restauración
        cout << "\n\t*** ADVERTENCIA: Esta accion reemplazara el archivo actual. ***\n";
        cout << "\tDesea continuar? (1=Si / 0=No): ";
        int confirmar;
        cin >> confirmar;

        if (confirmar != 1) {
            cout << "\n\tOperacion cancelada.\n";
            return;
        }

        // Restaurar archivo
        fs::copy_file(origen, destino, fs::copy_options::overwrite_existing);

        cout << "\n\tEXITO: Archivo restaurado correctamente.\n";
        cout << "\tArchivo: " << nombreArchivo << "\n";
        cout << "\tDesde: " << origen << "\n";

    } catch (const fs::filesystem_error& e) {
        cout << "\n\tERROR: No se pudo restaurar el archivo.\n";
        cout << "\tDetalles: " << e.what() << "\n";
    }
}

void MenuCopiaSeguridad::copiarTodos() {
    cout << "\n\t=== COPIANDO TODOS LOS ARCHIVOS ===\n\n";

    string archivos[] = {
        "Alumnos.dat",
        "Docentes.dat",
        "Carreras.dat",
        "Materias.dat",
        "Comisiones.dat",
        "InscripcionesComision.dat",
        "Examenes.dat",
        "Correlativas.dat"
    };

    int total = 8;
    int exitosos = 0;
    int fallidos = 0;

    // Crear carpeta backup si no existe
    try {
        if (!fs::exists("backup")) {
            fs::create_directory("backup");
        }
    } catch (const fs::filesystem_error& e) {
        cout << "\tERROR: No se pudo crear carpeta backup: " << e.what() << "\n";
        return;
    }

    for (int i = 0; i < total; i++) {
        try {
            string origen = archivos[i];
            string destino = "backup/" + archivos[i] + ".bak";

            if (fs::exists(origen)) {
                fs::copy_file(origen, destino, fs::copy_options::overwrite_existing);
                cout << "\t[OK] " << archivos[i] << "\n";
                exitosos++;
            } else {
                cout << "\t[OMITIDO] " << archivos[i] << " (no existe)\n";
                fallidos++;
            }
        } catch (const fs::filesystem_error& e) {
            cout << "\t[ERROR] " << archivos[i] << " (fallo al copiar)\n";
            fallidos++;
        }
    }

    cout << "\n\t=========================================\n";
    cout << "\tArchivos copiados: " << exitosos << "/" << total << "\n";
    if (fallidos > 0) {
        cout << "\tArchivos con problemas: " << fallidos << "\n";
    }
    cout << "\t=========================================\n";
}

void MenuCopiaSeguridad::restaurarTodos() {
    cout << "\n\t=== RESTAURANDO TODOS LOS ARCHIVOS ===\n";

    // Confirmar restauración
    cout << "\n\t*** ADVERTENCIA: Esta accion reemplazara TODOS los archivos actuales. ***\n";
    cout << "\tDesea continuar? (1=Si / 0=No): ";
    int confirmar;
    cin >> confirmar;

    if (confirmar != 1) {
        cout << "\n\tOperacion cancelada.\n";
        return;
    }

    cout << "\n";

    string archivos[] = {
        "Alumnos.dat",
        "Docentes.dat",
        "Carreras.dat",
        "Materias.dat",
        "Comisiones.dat",
        "InscripcionesComision.dat",
        "Examenes.dat",
        "Correlativas.dat"
    };

    int total = 8;
    int exitosos = 0;
    int fallidos = 0;

    for (int i = 0; i < total; i++) {
        try {
            string origen = "backup/" + archivos[i] + ".bak";
            string destino = archivos[i];

            if (fs::exists(origen)) {
                fs::copy_file(origen, destino, fs::copy_options::overwrite_existing);
                cout << "\t[OK] " << archivos[i] << "\n";
                exitosos++;
            } else {
                cout << "\t[OMITIDO] " << archivos[i] << " (backup no existe)\n";
                fallidos++;
            }
        } catch (const fs::filesystem_error& e) {
            cout << "\t[ERROR] " << archivos[i] << " (fallo al restaurar)\n";
            fallidos++;
        }
    }

    cout << "\n\t=========================================\n";
    cout << "\tArchivos restaurados: " << exitosos << "/" << total << "\n";
    if (fallidos > 0) {
        cout << "\tArchivos con problemas: " << fallidos << "\n";
    }
    cout << "\t=========================================\n";
}
