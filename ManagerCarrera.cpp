#include "ManagerCarrera.h"
#include "Validacion.h"
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

    if (Validacion::desearGuardar("")) {
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
    int idCarrera = Validacion::validarEnteroEnRango("\n\tID de Carrera: ", 0, 10000);

    int posicion = _repoCarrera.buscarPosicion(idCarrera);
    if (posicion < 0) {
        cout << "\n\tNo se encontró el registro.\n";
        return;
    }

    Carrera original = _repoCarrera.leerRegistro(posicion);
    original.mostrar();

    Carrera modificada = ingresarDatos(original.getIdCarrera());

    if (Validacion::desearGuardar("")) {
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
    int _idCarrera;
    string mensaje, accion, resultado;
    int posicion = 0;

    accion = activar ? "Activación" : "Borrado";
    resultado = activar ? "activado" : "borrado";

    cout << "\n\t=== Modificar Estado de Carrera ===\n";
    cout << "\n\t=== " << accion << " de registro ===\n";
    cout << "\n\tID de Carrera: ";

    _idCarrera = Validacion::validarEnteroEnRango(" ", 0, 10000);
    posicion = _repoCarrera.buscarPosicion(_idCarrera);

    if (posicion < 0) {
        cout << "\n\tNo se encontró un registro con ese ID.\n";
        return;
    }

    Carrera _carrera = _repoCarrera.leerRegistro(posicion);
    bool estadoActual = _carrera.getEliminado();
    _carrera.mostrar();

    // Dependiendo de la acción, revisamos el estado actual
    if (activar && estadoActual == false) {
        cout << "\n\tEl registro ya estaba activo.\n";
        return;
    }
    if (!activar && estadoActual == true) {
        cout << "\n\tEl registro ya estaba borrado.\n";
        return;
    }

    mensaje = "\n\tDesea " + string(activar ? "activar" : "borrar") + " el registro? s/n ";
    if (!Validacion::desearGuardar(mensaje)) {
        cout << "\n\tOperación cancelada.\n";
        return;
    }

    bool exito = activar ? _repoCarrera.activarRegistro(posicion)
                         : _repoCarrera.bajaLogica(posicion);

    if (exito)
        cout << "\n\tRegistro " << resultado << " correctamente.\n";
    else
        cout << "\n\tNo se pudo modificar el registro.\n";
    cin.ignore(10000, '\n');
}




void ManagerCarrera::activar(){
    cambiarEstado(true);
}



void ManagerCarrera::borrar()
{
    cambiarEstado(false);
}

void ManagerCarrera::listar()
{
    bool incluirBorrados = Validacion::desearGuardar("\n\t¿Desea incluir los registros borrados? (s/n): ");

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

