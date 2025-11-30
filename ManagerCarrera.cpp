#include "ManagerCarrera.h"
#include "Validacion.h"
#include "utils.h"
#include <iomanip>
using namespace std;


ManagerCarrera::ManagerCarrera()
{

}

Carrera ManagerCarrera::ingresarDatos(int idCarrera)
{
    const int minNombre = 2, maxNombre = 50;
    string nombre = Validacion::pedirEntradaCadena("\n\tNombre: ", minNombre, maxNombre);

    int duracion = Validacion::validarEnteroEnRango("\tDuración (1-4 cuatrimestres): ", 1, 4);

    Carrera nuevaCarrera(idCarrera, nombre.c_str(), duracion, false);
    return nuevaCarrera;
}



void ManagerCarrera::cargar()
{
    cout << "\n\t=== Cargar Carrera ===\n";

    int idCarrera = _repoCarrera.getNuevoID();
    Carrera nuevaCarrera = ingresarDatos(idCarrera);

    if (Validacion::desearAccionar("")) {
        if (_repoCarrera.agregarRegistro(nuevaCarrera) > 0)
            cout << "\n\tRegistro guardado correctamente.\n";
        else
            cout << "\n\tNo se pudo guardar el registro.\n";
    } else {
        cout << "\n\tOperación cancelada.\n";
    }
    cin.ignore(10000, '\n');
}


void ManagerCarrera::modificar()
{
    cout << "\n\t=== Modificar Carrera ===\n";

    int total = _repoCarrera.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay carreras registradas.\n";
        return;
    }

    // ================================
    // Mostrar solo carreras ACTIVAS
    // ================================
    bool hayActivas = false;

    for (int i = 0; i < total; i++) {
        Carrera c = _repoCarrera.leerRegistro(i);
        if (!c.getEliminado()) {
            hayActivas = true;
            break;
        }
    }

    if (!hayActivas) {
        cout << "\n\tNo hay carreras ACTIVAS para modificar.\n";
        return;
    }

    cout << "\n\tListado de carreras ACTIVAS:\n";
    mostrarEncabezado();

    for (int i = 0; i < total; i++) {
        Carrera c = _repoCarrera.leerRegistro(i);
        if (!c.getEliminado()) {
            mostrarRegistro(c);
        }
    }

    mostrarPie();

    // ================================
    // Pedir ID
    // ================================
    int idCarrera = Validacion::validarEnteroEnRango("\n\tID de Carrera a modificar: ", 1, 10000);

    int posicion = _repoCarrera.buscarPosicion(idCarrera);
    if (posicion < 0) {
        cout << "\n\tNo se encontró un registro con ese ID.\n";
        return;
    }

    Carrera original = _repoCarrera.leerRegistro(posicion);

    if (original.getEliminado()) {
        cout << "\n\tLa carrera está borrada y no puede modificarse.\n";
        return;
    }

    // ================================
    // Pedir nuevos datos (sin mostrar datos actuales)
    // ================================
    Carrera modificada = ingresarDatos(original.getIdCarrera());

    // ================================
    // Confirmar
    // ================================
    if (Validacion::desearAccionar("\n\t¿Desea guardar los cambios? (s/n): ")) {
        if (_repoCarrera.modificarRegistro(modificada, posicion))
            cout << "\n\tRegistro modificado correctamente.\n";
        else
            cout << "\n\tError al modificar el registro.\n";
    } else {
        cout << "\n\tOperación cancelada.\n";
    }

    cin.ignore(10000, '\n');
}



void ManagerCarrera::cambiarEstado(bool activar)
{
    cout << "\n\t=== " << (activar ? "Activar Carrera" : "Borrar Carrera") << " ===\n";

    int total = _repoCarrera.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay carreras registradas.\n";
        return;
    }

    // =====================================================
    // LISTAR SEGUN ACCION (sin mostrar tabla vacía)
    // =====================================================
    bool hay = false;
    for (int i = 0; i < total; i++) {
        Carrera c = _repoCarrera.leerRegistro(i);

        if (activar && c.getEliminado()) { hay = true; break; }   // activar → existen inactivas
        if (!activar && !c.getEliminado()) { hay = true; break; } // borrar → existen activas
    }

    if (!hay) {
        if (activar)
            cout << "\n\tNo hay carreras inactivas para activar.\n";
        else
            cout << "\n\tNo hay carreras activas para borrar.\n";
        return;
    }

    // =====================================================
    // Mostrar solo si hay carreras válidas
    // =====================================================
    cout << "\n\tListado de carreras "
         << (activar ? "ELIMINADAS" : "ACTIVAS") << ":\n";

    cout << "\t+-------+--------------------------------+------------+---------+\n";
    cout << "\t| ID    | Nombre                         | Duración   | Borrado |\n";
    cout << "\t+-------+--------------------------------+------------+---------+\n";

    for (int i = 0; i < total; i++) {
        Carrera c = _repoCarrera.leerRegistro(i);

        if (activar && !c.getEliminado()) continue;   // activar → mostrar solo borradas
        if (!activar && c.getEliminado()) continue;   // borrar → mostrar solo activas

        cout << "\t| " << setw(5)  << right << c.getIdCarrera()
             << " | " << setw(30) << left << quitarAcentos(c.getNombre())
             << " | " << setw(10) << right << c.getDuracionCuatrimestres()
             << " | " << setw(7)  << right << (c.getEliminado() ? "Si" : "No")
             << " |\n";
    }

    cout << "\t+-------+--------------------------------+------------+---------+\n";

    // =====================================================
    // PEDIR ID
    // =====================================================
    int id = Validacion::validarEnteroEnRango("\n\tID de Carrera: ", 1, 99999);

    int pos = _repoCarrera.buscarPosicion(id);
    if (pos < 0) {
        cout << "\n\tERROR: No existe una carrera con ese ID.\n";
        return;
    }

    Carrera reg = _repoCarrera.leerRegistro(pos);

    if (activar && !reg.getEliminado()) {
        cout << "\n\tLa carrera ya está ACTIVA.\n";
        return;
    }
    if (!activar && reg.getEliminado()) {
        cout << "\n\tLa carrera ya está BORRADA.\n";
        return;
    }

    // =====================================================
    // CONFIRMAR (sin mostrar datos)
    // =====================================================
    string mensaje = "\n\t¿Desea "
                     + string(activar ? "activar" : "borrar")
                     + " la carrera? (s/n): ";

    if (!Validacion::desearAccionar(mensaje)) {
        cout << "\n\tOperación cancelada.\n";
        return;
    }

    // =====================================================
    // APLICAR CAMBIO
    // =====================================================
    reg.setEliminado(!activar);

    if (_repoCarrera.modificarRegistro(reg, pos))
        cout << "\n\tRegistro " << (activar ? "activado" : "borrado") << " correctamente.\n";
    else
        cout << "\n\tERROR al modificar el registro.\n";
}



void ManagerCarrera::activar(){
    cambiarEstado(true);
}


void ManagerCarrera::borrar() {
    cambiarEstado(false);
}

void ManagerCarrera::listar()
{
    bool incluirBorrados = Validacion::desearAccionar("\n\t¿Desea incluir los registros borrados? (s/n): ");

    int total = _repoCarrera.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay registros para mostrar.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; ++i) {
        Carrera carrera = _repoCarrera.leerRegistro(i);
        if (!incluirBorrados && carrera.getEliminado()) continue;
        mostrarRegistro(carrera);
    }
    mostrarPie();
    cin.ignore(10000, '\n');
}



void ManagerCarrera::mostrar(Carrera _carrera) const
{
    cout << "\n\t=== Datos de la Carrera ===";
    cout << "\n\tID Carrera: " << _carrera.getIdCarrera();
    cout << "\n\tNombre: " << _carrera.getNombre();
    string cuatrimestres = (_carrera.getDuracionCuatrimestres() > 1 ? "cuatrimestres":"cuatrimestre");
    cout << "\n\tDuración: " << _carrera.getDuracionCuatrimestres() << cuatrimestres;
    cout << "\n\tEliminado: " << (_carrera.getEliminado() ? "Si" : "No") << "\n";
}


void ManagerCarrera::mostrarEncabezado(){
    cout << "\t+-------+--------------------------------+------------+---------+" << endl;
    cout << "\t| ID    | Nombre                         | Duración   | Borrado |" << endl;
    cout << "\t+-------+--------------------------------+------------+---------+" << endl;
}

void ManagerCarrera::mostrarRegistro(const Carrera& carrera) {
    cout << "\t| " << setw(5)  << right << carrera.getIdCarrera()
         << " | " << setw(30) << left  << carrera.getNombre()
         << " | " << setw(10) << right << carrera.getDuracionCuatrimestres()
         << " | " << setw(7)  << right << (carrera.getEliminado() ? "Si" : "No")
         << " |" << endl;
}



void ManagerCarrera::mostrarPie(){
    cout << "\t+-------+--------------------------------+------------+---------+" << endl;
}

