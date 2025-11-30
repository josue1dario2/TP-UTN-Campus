#include "Materia.h"
#include "Validacion.h"
#include "ArchivoMateria.h"
#include "ArchivoCarrera.h"
#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#include <iomanip>

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

    // === MOSTRAR CARRERAS ACTIVAS ANTES DE PEDIR EL ID ===
    ArchivoCarrera repoCarrera("Carreras.dat");
    int total = repoCarrera.contarRegistros();
    bool hayActivas = false;

    cout << "\n\tListado de Carreras ACTIVAS:\n";
    cout << "\t+-------+--------------------------------+------------+---------+\n";
    cout << "\t| ID    | Nombre                         | Duracion   | Borrado |\n";
    cout << "\t+-------+--------------------------------+------------+---------+\n";

    for (int i = 0; i < total; i++) {
        Carrera c = repoCarrera.leerRegistro(i);
        if (!c.getEliminado()) {
            hayActivas = true;
            cout << "\t| " << setw(5) << right << c.getIdCarrera()
                 << " | " << setw(30) << left  << c.getNombre()
                 << " | " << setw(10) << right << c.getDuracionCuatrimestres()
                 << " | " << setw(7)  << right << "No"
                 << " |\n";
        }
    }

    cout << "\t+-------+--------------------------------+------------+---------+\n";

    if (!hayActivas) {
        cout << "\n\tNo existen carreras activas. No se puede cargar la materia.\n";
        setIdMateria(0);
        return;
    }

    // === PEDIR ID DE CARRERA ===
    _idCarrera = Validacion::validarEnteroEnRango("\n\tID Carrera: ", 1, 10000);

    int posCarrera = repoCarrera.buscarPosicion(_idCarrera);
    if (posCarrera < 0) {
        cout << "\n\tERROR: La carrera no existe.\n";
        setIdMateria(0);
        return;
    }

    // === NOMBRE ===
    string nombre = Validacion::pedirEntradaCadena("\tNombre: ", 4, 50);
    strncpy(_nombre, nombre.c_str(), sizeof(_nombre));

    // Validar nombre repetido
    ArchivoMateria _archivoMateria;
    int existeNombre = _archivoMateria.buscarRegistro(_idCarrera, nombre, cargar);

    if (existeNombre >= 0) {
        cout << "\n\tEl nombre de materia ya existe para la carrera.\n";
        setIdMateria(0);
        return;
    }

    // === CUATRIMESTRE ===
    _cuatrimestre = Validacion::validarEnteroEnRango("\tCuatrimestre (1/2): ", 1, 2);

    // === ESTADO POR DEFECTO ===
    strcpy(_estado, "Activa");
    _eliminado = false;
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
