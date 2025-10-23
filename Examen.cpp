#include "Examen.h"
#include <iostream>
using std::cin; using std::cout;

Examen::Examen()
    : _idExamen(0), _idComision(0), _legajoAlumno(0),
      _numero(0), _nota(-1), _corregido(false), _eliminado(false) {
    std::strcpy(_tipo, "");
    // _fecha por defecto
}

Examen::Examen(int idExamen, int idComision, int legajoAlumno,
               const char* tipo, int numero, Fecha fecha, bool eliminado)
    : _idExamen(idExamen), _idComision(idComision), _legajoAlumno(legajoAlumno),
      _numero(numero), _fecha(fecha), _nota(-1), _corregido(false), _eliminado(eliminado) {
    setTipo(tipo);
}

int  Examen::getIdExamen() const { return _idExamen; }
void Examen::setIdExamen(int v){ _idExamen = v; }

int  Examen::getIdComision() const { return _idComision; }
void Examen::setIdComision(int v){ _idComision = v; }

int  Examen::getLegajoAlumno() const { return _legajoAlumno; }
void Examen::setLegajoAlumno(int v){ _legajoAlumno = v; }

const char* Examen::getTipo() const { return _tipo; }
void Examen::setTipo(const char* v){
    std::strncpy(_tipo, v, sizeof(_tipo));
    _tipo[sizeof(_tipo)-1] = '\0';
}

int  Examen::getNumero() const { return _numero; }
void Examen::setNumero(int v){ _numero = v; }

Fecha Examen::getFecha() const { return _fecha; }
void  Examen::setFecha(Fecha f){ _fecha = f; }

int  Examen::getNota() const { return _nota; }
void Examen::setNota(int v){ _nota = v; }

bool Examen::getCorregido() const { return _corregido; }
void Examen::setCorregido(bool v){ _corregido = v; }

bool Examen::getEliminado() const { return _eliminado; }
void Examen::setEliminado(bool v){ _eliminado = v; }

void Examen::inscribir(){
    _nota = -1;
    _corregido = false;
}

void Examen::corregir(int nota){
    _nota = nota;
    _corregido = true;
}

std::string Examen::toString() const {
    return "Examen ID: " + std::to_string(_idExamen) +
           "\nComisión ID: " + std::to_string(_idComision) +
           "\nLegajo Alumno: " + std::to_string(_legajoAlumno) +
           "\nTipo: " + std::string(_tipo) +
           "\nNúmero: " + std::to_string(_numero) +
           "\nFecha: " + _fecha.toString() +
           "\nNota: " + (_nota >= 0 ? std::to_string(_nota) : std::string("Sin corregir")) +
           "\nCorregido: " + std::string(_corregido ? "Sí" : "No") +
           "\nEliminado: " + std::string(_eliminado ? "Sí" : "No");
}

void Examen::cargar(){
    cout << "ID Examen: ";
    cin >> _idExamen; cin.ignore(10000,'\n');

    cout << "ID Comisión: ";
    cin >> _idComision; cin.ignore(10000,'\n');

    cout << "Legajo Alumno: ";
    cin >> _legajoAlumno; cin.ignore(10000,'\n');

    cout << "Tipo (Parcial/Final): ";
    cin.getline(_tipo, sizeof(_tipo));

    if(std::string(_tipo) == "Parcial"){
        cout << "Número de Parcial (1-3): ";
        cin >> _numero; cin.ignore(10000,'\n');
    } else {
        _numero = 0; // Final
    }

    cout << "[Fecha del examen]\n";
    _fecha.cargar();

    inscribir();      // nota=-1, corregido=false
    _eliminado = false;
}

void Examen::mostrar() const {
    cout << toString() << "\n";
}
