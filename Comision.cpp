#include "Comision.h"
using std::cin; using std::cout;

Comision::Comision() {
    _idComision = 0;
    _idMateria = 0;
    strcpy(_turno, "");
    strcpy(_modalidad, "");
    _cuatrimestre = 0;
    _anio = 0;
    _eliminado = false;
}

Comision::Comision(int idComision, int idMateria,
                   const char* turno, const char* modalidad,
                   int cuatrimestre, int anio, bool eliminado) {
    _idComision = idComision;
    _idMateria = idMateria;
    strcpy(_turno, turno);
    strcpy(_modalidad, modalidad);
    _cuatrimestre = cuatrimestre;
    _anio = anio;
    _eliminado = eliminado;
}

int Comision::getIdComision() const { return _idComision; }
void Comision::setIdComision(int v){ _idComision = v; }

int Comision::getIdMateria() const { return _idMateria; }
void Comision::setIdMateria(int v){ _idMateria = v; }

const char* Comision::getTurno() const { return _turno; }
void Comision::setTurno(const char* v){
    std::strncpy(_turno, v, sizeof(_turno));
    _turno[sizeof(_turno)-1] = '\0';
}

const char* Comision::getModalidad() const { return _modalidad; }
void Comision::setModalidad(const char* v){
    std::strncpy(_modalidad, v, sizeof(_modalidad));
    _modalidad[sizeof(_modalidad)-1] = '\0';
}

int Comision::getCuatrimestre() const { return _cuatrimestre; }
void Comision::setCuatrimestre(int v){ _cuatrimestre = v; }

int Comision::getAnio() const { return _anio; }
void Comision::setAnio(int anio) { _anio = anio; }

bool Comision::getEliminado() const { return _eliminado; }
void Comision::setEliminado(bool v){ _eliminado = v; }

void Comision::cargar() {
    cout << "=== Cargar Comision ===\n";
    cout << "ID Comision: ";
    cin >> _idComision;

    cout << "ID Materia: ";
    cin >> _idMateria;

    cout << "Turno (Maniana/Tarde/Noche): ";
    cin >> _turno;

    cout << "Modalidad (Presencial/Virtual/Hibrida): ";
    cin >> _modalidad;

    cout << "Cuatrimestre: ";
    cin >> _cuatrimestre;

    cout << "Año de cursada: ";
    cin >> _anio;

    _eliminado = false;
}

void Comision::mostrar() const {
    cout << "=== Datos de la Comision ===\n";
    cout << "ID Comision: " << _idComision << "\n";
    cout << "ID Materia: " << _idMateria << "\n";
    cout << "Turno: " << _turno << "\n";
    cout << "Modalidad: " << _modalidad << "\n";
    cout << "Cuatrimestre: " << _cuatrimestre << "\n";
    cout << "Año: " << _anio << "\n";
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << "\n\n";
}
