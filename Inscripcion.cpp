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

void Inscripcion::cargar() {
    cout << "=== Cargar Inscripción ===\n";
    cout << "ID de Inscripción: ";
    cin >> _idInscripcion;

    cout << "Legajo del Alumno: ";
    cin >> _legajoAlumno;

    cout << "ID de Comisión: ";
    cin >> _idComision;

    cout << "Fecha de inscripción:\n";
    _fechaInscripcion.cargar();

    cout << "Estado (Regular / Libre / Aprobada / Baja): ";
    cin >> _estado;

    _eliminado = false;
}

void Inscripcion::mostrar() const {
    cout << "=== Datos de la Inscripción ===\n";
    cout << "ID Inscripción: " << _idInscripcion << "\n";
    cout << "Legajo Alumno: " << _legajoAlumno << "\n";
    cout << "ID Comisión: " << _idComision << "\n";
    cout << "Fecha de Inscripción: ";
    _fechaInscripcion.mostrar();
    cout << "Estado: " << _estado << "\n";
    cout << "Eliminado: " << (_eliminado ? "Sí" : "No") << "\n\n";
}
