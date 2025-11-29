#include "ManagerMateria.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void ManagerMateria::alta() {
    Materia reg;

    reg.setIdMateria(generarIdNuevo());

    reg.cargar();

    //if (reg.getIdMateria()==0) {return;}
    int _idCarreraNuevo = reg.getIdCarrera();
    if (_archivoCarreras.existeCarrera(_idCarreraNuevo)) {
        if (_archivoMaterias.agregarRegistro(reg) == 1) {
            cout << "\n\tMateria guardada con éxito.\n";
        } else {
            cout << "\n\tError al guardar la materia.\n";
        }
    } else {
        cout << "\n\tEl ID de Carrera no existe.\n";
    }




    return;
    /*
    if (_archivoCarreras.existeCarrera(_idCarreraNuevo)) {
        if (_archivoMaterias.agregarRegistro(reg) == 1) {
            cout << "\n\tMateria guardada con éxito.\n";
        } else {
            cout << "\n\tError al guardar la materia.\n";
        }
    }
    else
    {
        cout << "\n\tEl ID de Materia es incorrecto.";
    }
    */
}

void ManagerMateria::activar() {
    int id = Validacion::validarEnteroEnRango("\tIngrese el ID de la materia a activar: ", 1,10000);


    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }
    if (Validacion::desearAccionar("Desea activar la materia? s/n: ")){
        if (_archivoMaterias.activarRegistro(pos)){
            cout << "Materia activada correctamente.\n";
        }
        else{
            cout << "No se pudo activar.\n";
        }
    }
}

void ManagerMateria::baja() {
    int id;
    cout << "Ingrese el ID de la materia a eliminar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    if (Validacion::desearAccionar("Desea borrar la materia? s/n: ")){
        if (_archivoMaterias.bajaLogica(pos)) {
            cout << "Materia dada de baja correctamente.\n";
        }
        else {
            cout << "No se pudo eliminar.\n";
        }
    }
}




void ManagerMateria::modificacion() {
    int id;
    cout << "Ingrese el ID de la materia a modificar: ";
    cin >> id;

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Materia no encontrada.\n";
        return;
    }

    Materia reg = _archivoMaterias.leerRegistro(pos);

    cout << "\n=== DATOS ACTUALES ===\n";
    reg.mostrar();

    cout << "\n=== INGRESE NUEVOS DATOS ===\n";

    Materia _nuevaMateria;
    _nuevaMateria.cargar();

    if (Validacion::desearAccionar("\tDesea guardar los datos? s/n: ")){
        if (_archivoMaterias.modificarRegistro(reg, pos))
            cout << "Registro modificado correctamente.\n";
        else
            cout << "Error al modificar.\n";
    }



}

void ManagerMateria::listarTodas() {
    bool incluirBorrados = Validacion::desearAccionar("\n\t¿Desea incluir los registros borrados? (s/n): ");

    int cantidad = _archivoMaterias.contarRegistros();
    if (cantidad == 0) {
        cout << "\n\tNo hay materias registradas.\n";
        return;
    }

    cout << "\n\t=== LISTADO DE MATERIAS ===\n";

    cout << left << setfill(' ');

    // ------- ENCABEZADO -------
    cout << setw(10) << "Carrera"
         << setw(5)  << "Id"
         << setw(38) << "Nombre"
         << setw(15) << "Cuatrimestre"
         << setw(10) << "Estado"
         << setw(10) << "Eliminado"
         << "\n";

    cout << string(88, '-') << "\n";

    // ------- FILAS -------
    int contadorMostrados = 0;
    for (int i = 0; i < cantidad; i++) {
        Materia reg = _archivoMaterias.leerRegistro(i);

        // Si no se desea incluir borrados y el registro está eliminado, saltar
        if (!incluirBorrados && reg.getEliminado()) continue;

        cout << setw(10) << reg.getIdCarrera()
             << setw(5)  << reg.getIdMateria()
             << setw(38) << quitarAcentos(reg.getNombre())
             << setw(15) << reg.getCuatrimestre()
             << setw(10) << reg.getEstado()
             << setw(10) << (reg.getEliminado() ? "Si" : "No")
             << "\n";

        contadorMostrados++;
    }

    cout << string(88, '-') << "\n";

    if (contadorMostrados == 0) {
        cout << "\n\tNo hay materias para mostrar con los filtros aplicados.\n";
    }

    cin.ignore(10000, '\n');
}

int ManagerMateria::buscarPorId(int idMateria) {
    return _archivoMaterias.buscarRegistro(idMateria);
}

int ManagerMateria::generarIdNuevo() {
    int cant = _archivoMaterias.contarRegistros();
    int maxID = 0;

    for (int i = 0; i < cant; i++) {
        Materia reg = _archivoMaterias.leerRegistro(i);
        if (reg.getIdMateria() > maxID)
            maxID = reg.getIdMateria();
    }

    return maxID + 1;
}


