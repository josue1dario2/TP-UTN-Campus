#include "Materia.h"
#include "Validacion.h"
#include "ArchivoMateria.h"
#include <iostream>
#include <cstring>
#include <string>
#include <limits>

using namespace std;

Materia::Materia() {
    setIdMateria(0);
    setIdCarrera(0);
    setNombre("");
    setCuatrimestre(0);
    setEstado("");
    setEliminado(false);
}

Materia::Materia(int idMateria, int idCarrera, const char* nombre, int cuatrimestre, const char* estado, bool eliminado) {
    setIdMateria(idMateria);
    setIdCarrera(idCarrera);
    setNombre(nombre);
    setCuatrimestre(cuatrimestre);
    setEstado(estado);
    setEliminado(eliminado);
}

void Materia::setIdMateria(int idMateria) { _idMateria = idMateria; }
void Materia::setIdCarrera(int idCarrera) { _idCarrera = idCarrera; }

void Materia::setNombre(const char* nombre) {
    strncpy(_nombre, nombre, sizeof(_nombre));
    _nombre[sizeof(_nombre) - 1] = '\0';
}

void Materia::setCuatrimestre(int cuatrimestre) { _cuatrimestre = cuatrimestre; }

void Materia::setEstado(const char* estado) {
    strncpy(_estado, estado, sizeof(_estado));
    _estado[sizeof(_estado) - 1] = '\0';
}

void Materia::setEliminado(bool eliminado) { _eliminado = eliminado; }

int Materia::getIdMateria() const { return _idMateria; }
int Materia::getIdCarrera() const { return _idCarrera; }
const char* Materia::getNombre() const { return _nombre; }
int Materia::getCuatrimestre() const { return _cuatrimestre; }
const char* Materia::getEstado() const { return _estado; }
bool Materia::getEliminado() const { return _eliminado; }

void Materia::cargar(bool cargar) {

    cout << "\n\t=== Cargar Materia ===\n";
    _idCarrera= Validacion::validarEnteroEnRango("\n\tID Carrera: ",1,10000);

    string nombre =Validacion::pedirEntradaCadena("\tNombre: ",4,50);
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre));

    ArchivoMateria _archivoMateria;
    int existeNombre = _archivoMateria.buscarRegistro(_idCarrera, nombre,cargar);

    if (existeNombre >=0){
        cout << "\n\tEl nombre de materia ya existe para la carrera.";
        setIdMateria(0);
        return;
    }

    _cuatrimestre= Validacion::validarEnteroEnRango("\tCuatrimestre (1/2): ",1,2);

    int estadoMateria= Validacion::validarEnteroEnRango("\tEstado (1-Activa/2-Inactiva): ",1,2);
    strcpy(_estado, (estadoMateria == 1) ? "Activa" : "Inactiva");

    _eliminado = false;
    /*
    cout << "ID Carrera: ";
    cin >> _idCarrera;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nombre: ";
    cin.getline(_nombre, sizeof(_nombre));

    cout << "Cuatrimestre: ";
    cin >> _cuatrimestre;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Estado (Activa / Inactiva): ";
    cin.getline(_estado, sizeof(_estado));
    */

}

void Materia::mostrar() const {
    cout << "\n=== DATOS DE LA MATERIA ===\n";
    cout << "ID Materia     : " << _idMateria << "\n";
    cout << "ID Carrera     : " << _idCarrera << "\n";
    cout << "Nombre          : " << _nombre << "\n";
    cout << "Cuatrimestre    : " << _cuatrimestre << "\n";
    cout << "Estado          : " << _estado << "\n";
    cout << "Eliminado       : " << (_eliminado ? "Sí" : "No") << "\n";
    cout << "----------------------------\n";
}
