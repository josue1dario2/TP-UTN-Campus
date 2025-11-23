#include "ManagerMateria.h"
#include "Validacion.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void ManagerMateria::alta() {
    Materia reg;

    reg.setIdMateria(generarIdNuevo());

    reg.cargar();
    int _idCarreraNuevo = reg.getIdCarrera();
    //reg.setEliminado(false);
    if (_archivoCarreras.existeCarrera(_idCarreraNuevo)) {
        if (_archivoMaterias.agregarRegistro(reg) == 1) {
            cout << "\n\tMateria guardada con éxito.\n";
        } else {
            cout << "\n\tError al guardar la materia.\n";
        }
    }
    else
    {
        cout << "\n\tEl ID de Carrera es incorrecto.";
    }
    return;

}

bool ManagerMateria::existeMateria(int idMateria){
    if (buscarPorId(idMateria)>=0) return true;
    return false;


}

void ManagerMateria::modificacion() {
    int id;
    cout << "\n\tIngrese el ID de la materia a modificar: ";
    cin >> id;


    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "\n\tMateria no encontrada.\n";
        return;
    }




    Materia _regActual = _archivoMaterias.leerRegistro(pos);
    cout << "\n\tDatos actuales:\n";

    _regActual.mostrar();

    cout << "\n\tIngrese los nuevos datos:\n";


    Materia _regMateriaNueva;
    _regMateriaNueva.cargar();

    _regMateriaNueva.setIdMateria(id);
    int _regIDCarrera_actual = _regMateriaNueva.getIdCarrera();


    int _IdCarreraNuevo = _regMateriaNueva.getIdCarrera();
    if (_archivoCarreras.existeCarrera(_IdCarreraNuevo)){
        if (Validacion::desearAccionar("")) {
            if (_archivoMaterias.modificarRegistro(_regMateriaNueva, pos)) {
                cout << "\n\tRegistro modificado correctamente.\n";
            }
            else
            {
            cout << "\n\tError al modificar.\n";
            }
        }
    }
    else {
        cout << "\n\tLa carrera no existe. Vuelva a intentar.\n";
    }
}

void ManagerMateria::listarTodas() {
    int cantidad = _archivoMaterias.contarRegistros();
    if (cantidad == 0) {
        cout << "No hay materias registradas.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        Materia reg = _archivoMaterias.leerRegistro(i);
        if (!reg.getEliminado()) {
            reg.mostrar();
            cout << "-------------------------------\n";
        }
    }
}

int ManagerMateria::buscarPorId(int idMateria) {
    return _archivoMaterias.buscarRegistro(idMateria);
}

int ManagerMateria::generarIdNuevo() {
    return _archivoMaterias.contarRegistros() + 1;
}

void ManagerMateria::listar()
{
    bool incluirBorrados = Validacion::desearAccionar("\n\t¿Desea incluir los registros borrados? (s/n): ");

    int total = _archivoMaterias.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay registros para mostrar.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; ++i) {
        Materia _materia = _archivoMaterias.leerRegistro(i);
        if (!incluirBorrados && _materia.getEliminado()) continue;
        mostrarRegistro(_materia);
    }
    mostrarPie();
    cin.ignore(10000, '\n');
}
void ManagerMateria::borrar(){
    cambiarEstado(false);
}
void ManagerMateria::activar(){
    cambiarEstado(true);
}

void ManagerMateria::cambiarEstado(bool activar)
{
    int _idMateria;
    string mensaje, accion, resultado;
    int posicion = 0;

    accion = activar ? "Activación" : "Borrado";
    resultado = activar ? "activado" : "borrado";


    cout << "\n\t=== Modificar Estado de Materia ===\n";
    cout << "\n\t=== " << accion << " de registro ===\n";
    cout << "\n\tID de Materia: ";

    _idMateria = Validacion::validarEnteroEnRango(" ", 0, 10000);
    posicion = _archivoMaterias.buscarPosicion(_idMateria);


    if (posicion < 0) {
        cout << "\n\tNo se encontró un registro con ese ID.\n";
        return;
    }

    Materia _materia = _archivoMaterias.leerRegistro(posicion);
    //   Carrera _carrera = _repoCarrera.leerRegistro(posicion);
    bool estadoActual =  _materia.getEliminado();
    _materia.mostrar();


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
    if (!Validacion::desearAccionar(mensaje)) {
        cout << "\n\tOperación cancelada.\n";
        return;
    }

    bool exito = activar ? _archivoMaterias.activarRegistro(posicion)
                         : _archivoMaterias.bajaLogica(posicion);

    if (exito)
        cout << "\n\tRegistro " << resultado << " correctamente.\n";
    else
        cout << "\n\tNo se pudo modificar el registro.\n";
    cin.ignore(10000, '\n');
}



void ManagerMateria::mostrar(Materia _materia) const
{
    cout << "\n\t=== Datos de la Carrera ===";
    cout << "\n\tID Materia: " << _materia.getIdMateria();
    cout << "\n\tID Carrera: " << _materia.getIdCarrera();
    cout << "\n\tNombre: " << _materia.getNombre();
    cout << "\n\tCuatrimetre: " << _materia.getCuatrimestre();
    cout << "\n\tEstado: " << _materia.getEstado();
    cout << "\n\tEliminado: " << (_materia.getEliminado() ? "Si" : "No") << "\n";
}


void ManagerMateria::mostrarEncabezado(){
    cout << "\t+---------+------------+----------------------+------------+---------+---------+" << endl;
    cout << "\t| ID Mat. | ID Carr. | Nombre                 | Cuatrim.   | Estado  | Borrado |" << endl;
    cout << "\t+---------+------------+----------------------+------------+---------+---------+" << endl;
}

void ManagerMateria::mostrarRegistro(const Materia& _materia) {
    cout << "\t| " << setw(7)  << left << _materia.getIdMateria()
         << " | " << setw(8)  << left << _materia.getIdCarrera()
         << " | " << setw(22) << left  << _materia.getNombre()
         << " | " << setw(10) << left << _materia.getCuatrimestre()
         << " | " << setw(7)  << left << _materia.getEstado()
         << " | " << setw(7)  << internal << (_materia.getEliminado() ? "Si" : "No")
         << " |" << endl;

}



void ManagerMateria::mostrarPie(){
    cout << "\t+---------+------------+----------------------+------------+---------+---------+" << endl;
}
