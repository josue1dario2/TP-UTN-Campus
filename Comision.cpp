#include "Comision.h"
#include "Validacion.h"
#include <string>
#include <cstring>

using std::cin; using std::cout; using std::string;

Comision::Comision() {
    _idComision = 0;
    _idMateria = 0;
    strcpy(_turno, "");
    strcpy(_modalidad, "");
    _cuatrimestre = 0;
    _anio = 0;
    _legajoDocente = 0;
    _eliminado = false;
}

Comision::Comision(int idComision, int idMateria,
                   const char* turno, const char* modalidad,
                   int cuatrimestre, int anio, int legajoDocente, bool eliminado) {
    _idComision = idComision;
    _idMateria = idMateria;
    strcpy(_turno, turno);
    strcpy(_modalidad, modalidad);
    _cuatrimestre = cuatrimestre;
    _anio = anio;
    _legajoDocente = legajoDocente;
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

int Comision::getLegajoDocente() const { return _legajoDocente; }
void Comision::setLegajoDocente(int legajo) { _legajoDocente = legajo; }

bool Comision::getEliminado() const { return _eliminado; }
void Comision::setEliminado(bool v){ _eliminado = v; }

void Comision::cargar() {
    cout << "=== Cargar Comision ===\n";

    _idComision= Validacion::validarEnteroEnRango("\n\tID Comision: ",1,10000);

    _idMateria= Validacion::validarEnteroEnRango("\n\tID Materia: ",1,10000);

    string turno="";
    int _elecTurno = Validacion::validarEnteroEnRango("\tTurno (1 para Mañana/2 para Tarde/3 para Noche): ",1,3);

    switch (_elecTurno){
        case 1:
                turno = "Manana";
                break;
            case 2:
                turno = "Tarde";
                break;
            case 3:
                turno = "Noche";
                break;
    }

    string modalidad="";
    int _elecModalidad = Validacion::validarEnteroEnRango("\tModalidad (1 para Presencial/2 para Virtual/ 3 para Híbrida): ",1,3);

    switch (_elecModalidad){
        case 1:
                modalidad = "Presenc.";
                break;
            case 2:
                modalidad = "Virtual";
                break;
            case 3:
                modalidad = "Híbrida";
                break;
    }


    _cuatrimestre= Validacion::validarEnteroEnRango("\tCuatrimestre (1/2): ",1,2);

    _anio = Validacion::validarEnteroEnRango("\tAño de cursada: ",2000,2040);

    _legajoDocente = Validacion::validarEnteroEnRango("\n\tNum. de legajo: ", 10000, 99999);

    _eliminado = false;

    /*
    out << "ID Comision: ";
    cin >> _idComision;

    cout << "ID Materia: ";
    cin >> _idMateria;
    cin.ignore(); // limpiar salto de línea pendiente

    cout << "Turno (Maniana/Tarde/Noche): ";
    cin.getline(_turno, 10);

    cout << "Modalidad (Presencial/Virtual/Hibrida): ";
    cin.getline(_modalidad, 10);

    cout << "Cuatrimestre: ";
    cin >> _cuatrimestre;

    cout << "Año de cursada: ";
    cin >> _anio;

    cout << "Legajo del Docente: ";
    cin >> _legajoDocente;

    */
}

void Comision::mostrar() const {
    cout << "=== Datos de la Comision ===\n";
    cout << "ID Comision: " << _idComision << "\n";
    cout << "ID Materia: " << _idMateria << "\n";
    cout << "Turno: " << _turno << "\n";
    cout << "Modalidad: " << _modalidad << "\n";
    cout << "Cuatrimestre: " << _cuatrimestre << "\n";
    cout << "Año: " << _anio << "\n";
    cout << "Legajo Docente: " << _legajoDocente << "\n";
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << "\n\n";
}
