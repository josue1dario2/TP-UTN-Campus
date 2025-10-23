#include "Inscripcion.h"
using std::cin; using std::cout;

Inscripcion::Inscripcion()
    : _idInscripcion(0), _legajoAlumno(0), _idComision(0),
      _fechaInscripcion(), _eliminado(false) {
    std::strcpy(_estado, "Regular");
}

Inscripcion::Inscripcion(int idInscripcion, int legajoAlumno, int idComision,
                         Fecha fechaInscripcion, const char* estado, bool eliminado)
    : _idInscripcion(idInscripcion), _legajoAlumno(legajoAlumno),
      _idComision(idComision), _fechaInscripcion(fechaInscripcion),
      _eliminado(eliminado) {
    setEstado(estado);
}

int  Inscripcion::getIdInscripcion() const { return _idInscripcion; }
void Inscripcion::setIdInscripcion(int v){ _idInscripcion = v; }

int  Inscripcion::getLegajoAlumno() const { return _legajoAlumno; }
void Inscripcion::setLegajoAlumno(int v){ _legajoAlumno = v; }

int  Inscripcion::getIdComision() const { return _idComision; }
void Inscripcion::setIdComision(int v){ _idComision = v; }

Fecha Inscripcion::getFechaInscripcion() const { return _fechaInscripcion; }
void  Inscripcion::setFechaInscripcion(Fecha f){ _fechaInscripcion = f; }

const char* Inscripcion::getEstado() const { return _estado; }
void        Inscripcion::setEstado(const char* v){
    std::strncpy(_estado, v, sizeof(_estado));
    _estado[sizeof(_estado)-1] = '\0';
}

bool Inscripcion::getEliminado() const { return _eliminado; }
void Inscripcion::setEliminado(bool v){ _eliminado = v; }

std::string Inscripcion::toString() const {
    return "Inscripción ID: " + std::to_string(_idInscripcion) +
           "\nLegajo Alumno: " + std::to_string(_legajoAlumno) +
           "\nComisión ID: " + std::to_string(_idComision) +
           "\nFecha Inscripción: " + _fechaInscripcion.toString() +
           "\nEstado: " + std::string(_estado) +
           "\nEliminado: " + std::string(_eliminado ? "Sí" : "No");
}

void Inscripcion::cargar(){
    cout << "ID Inscripción: ";
    cin >> _idInscripcion; cin.ignore(10000,'\n');

    cout << "Legajo Alumno: ";
    cin >> _legajoAlumno; cin.ignore(10000,'\n');

    cout << "ID Comisión: ";
    cin >> _idComision; cin.ignore(10000,'\n');

    cout << "[Fecha de inscripción]\n";
    _fechaInscripcion.cargar();

    cout << "Estado (Regular/Libre/Aprobada/Baja): ";
    cin.getline(_estado, sizeof(_estado));

    _eliminado = false;
}

void Inscripcion::mostrar() const{
    cout << toString() << "\n";
}
