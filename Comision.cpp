#include "Comision.h"
using std::cin; using std::cout;

Comision::Comision()
    : _idComision(0), _idMateria(0),
      _cuatrimestre(0), _eliminado(false) {
    strcpy(_turno, "");
    strcpy(_modalidad, "");
}

Comision::Comision(int idComision, int idMateria,
                   const char* turno, const char* modalidad,
                   int cuatrimestre, bool eliminado)
    : _idComision(idComision), _idMateria(idMateria),
      _cuatrimestre(cuatrimestre), _eliminado(eliminado) {
    setTurno(turno);
    setModalidad(modalidad);
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

bool Comision::getEliminado() const { return _eliminado; }
void Comision::setEliminado(bool v){ _eliminado = v; }

std::string Comision::toString() const {
    return "Comisión ID: " + std::to_string(_idComision) +
           "\nMateria ID: " + std::to_string(_idMateria) +
           "\nTurno: " + std::string(_turno) +
           "\nModalidad: " + std::string(_modalidad) +
           "\nCuatrimestre: " + std::to_string(_cuatrimestre) +
           "\nEliminado: " + std::string(_eliminado ? "Sí" : "No");
}

void Comision::cargar(){
    cout << "ID Comisión: ";
    cin >> _idComision; cin.ignore(10000,'\n');

    cout << "ID Materia: ";
    cin >> _idMateria; cin.ignore(10000,'\n');

    cout << "Turno (Manana/Tarde/Noche): ";
    cin.getline(_turno, sizeof(_turno));

    cout << "Modalidad (Presencial/Virtual/Hibrida): ";
    cin.getline(_modalidad, sizeof(_modalidad));

    cout << "Cuatrimestre (numero): ";
    cin >> _cuatrimestre; cin.ignore(10000,'\n');

    _eliminado = false;
}

void Comision::mostrar() const{
    cout << toString() << "\n";
}
