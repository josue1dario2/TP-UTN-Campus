#include "Carrera.h"
using std::cin; using std::cout;

Carrera::Carrera() : _idCarrera(0), _duracionCuatrimestres(0), _eliminado(false) {
    strcpy(_nombre, "");
}

Carrera::Carrera(int idCarrera, const char* nombre, int duracionCuatrimestres, bool eliminado)
    : _idCarrera(idCarrera), _duracionCuatrimestres(duracionCuatrimestres), _eliminado(eliminado) {
    setNombre(nombre);
}

int Carrera::getIdCarrera() const { return _idCarrera; }
void Carrera::setIdCarrera(int idCarrera) { _idCarrera = idCarrera; }

const char* Carrera::getNombre() const { return _nombre; }
void Carrera::setNombre(const char* nombre) {
    std::strncpy(_nombre, nombre, sizeof(_nombre));
    _nombre[sizeof(_nombre)-1] = '\0';
}

int Carrera::getDuracionCuatrimestres() const { return _duracionCuatrimestres; }
void Carrera::setDuracionCuatrimestres(int duracion) { _duracionCuatrimestres = duracion; }

bool Carrera::getEliminado() const { return _eliminado; }
void Carrera::setEliminado(bool eliminado) { _eliminado = eliminado; }

std::string Carrera::toString() const {
    return "Carrera ID: " + std::to_string(_idCarrera) +
           "\nNombre: " + std::string(_nombre) +
           "\nDuración (cuatrimestres): " + std::to_string(_duracionCuatrimestres) +
           "\nEliminado: " + std::string(_eliminado ? "Sí" : "No");
}

void Carrera::cargar() {
    cout << "ID Carrera: ";
    cin >> _idCarrera; cin.ignore(10000, '\n');

    cout << "Nombre: ";
    cin.getline(_nombre, sizeof(_nombre));

    cout << "Duración en cuatrimestres: ";
    cin >> _duracionCuatrimestres; cin.ignore(10000, '\n');

    _eliminado = (false);
}

void Carrera::mostrar() const {
    cout << toString() << "\n";
}
