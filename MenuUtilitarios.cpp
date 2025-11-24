#include <iostream>
#include <limits>
#include <filesystem>
#include "MenuUtilitarios.h"
#include "MenuDatosCSV.h"
#include "Validacion.h"
#include "utils.h"

using namespace std;
namespace fs = std::filesystem;

// =====================================================
//     MENU PRINCIPAL
// =====================================================
void MenuUtilitarios::mostrarMenuPrincipal() {
    int opcion;
    do {
        clearScreen();
        cout << "\n\tMENÚ UTILITARIOS\n";
        cout << "\t---------------------------\n";
        cout << "\t1 - Realizar copia de seguridad\n";
        cout << "\t2 - Restaurar copia de seguridad\n";
        cout << "\t3 - Exportar datos (CSV)\n";
        cout << "\t---------------------------\n";
        cout << "\t0 - Volver\n";
        opcion = Validacion::validarEnteroEnRango("\tSeleccione una opcion: ", 0, 3);

        clearScreen();
        switch (opcion) {
            case 1: realizarCopiaSeguridad(); break;
            case 2: restaurarCopiaSeguridad(); break;
            case 3: exportarDatosCSV(); break;
            case 0: cout << "Volviendo al menú anterior...\n"; break;
            default: cout << "Opción inválida. Intente nuevamente.\n"; break;
        }

        if (opcion != 0) pauseScreen();
    } while (opcion != 0);
}


// =====================================================
//     COPIA DE SEGURIDAD REAL
// =====================================================
void MenuUtilitarios::realizarCopiaSeguridad() {
    cout << "Realizando copia de seguridad REAL...\n";

    fs::path source = fs::current_path();
    fs::path backup = source / "backup";

    // Crear carpeta backup si no existe
    if (!fs::exists(backup)) {
        fs::create_directory(backup);
        cout << "Carpeta /backup creada.\n";
    }

    int copiados = 0;

    // Copiar todos los .dat
    for (const auto& file : fs::directory_iterator(source)) {
        if (file.path().extension() == ".dat") {

            fs::path destino = backup / file.path().filename();

            try {
                fs::copy_file(file.path(), destino, fs::copy_options::overwrite_existing);
                cout << "[OK] Copiado: " << file.path().filename() << endl;
                copiados++;
            }
            catch (fs::filesystem_error& e) {
                cout << "Error copiando " << file.path().filename()
                     << ": " << e.what() << endl;
            }
        }
    }

    if (copiados == 0) cout << "No se encontraron archivos .dat para copiar.\n";
    else cout << "\nBackup completo. Archivos copiados: " << copiados << endl;
}


// =====================================================
//     RESTAURAR BACKUP REAL
// =====================================================
void MenuUtilitarios::restaurarCopiaSeguridad() {
    cout << "Restaurando copia de seguridad REAL...\n";

    fs::path source = fs::current_path() / "backup";
    fs::path destino = fs::current_path();

    if (!fs::exists(source)) {
        cout << "No existe carpeta /backup. Primero cree un respaldo.\n";
        return;
    }

    int restaurados = 0;

    for (const auto& file : fs::directory_iterator(source)) {
        if (file.path().extension() == ".dat") {

            fs::path destinoFinal = destino / file.path().filename();

            try {
                fs::copy_file(file.path(), destinoFinal, fs::copy_options::overwrite_existing);
                cout << "[OK] Restaurado: " << file.path().filename() << endl;
                restaurados++;
            }
            catch (fs::filesystem_error& e) {
                cout << "Error restaurando " << file.path().filename()
                     << ": " << e.what() << endl;
            }
        }
    }

    if (restaurados == 0) cout << "No se encontraron .dat en /backup.\n";
    else cout << "\nRestauración completa. Archivos restaurados: " << restaurados << endl;
}


// =====================================================
//     EXPORTAR CSV
// =====================================================
void MenuUtilitarios::exportarDatosCSV() {
    MenuDatosCSV menu;
    menu.mostrar();
}
