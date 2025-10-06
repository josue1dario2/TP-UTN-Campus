#include "Inscripcion.h"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace std;

Inscripcion::Inscripcion()
{
    _idInscripcion = 0;
    _idAlumno = 0;
    _idComision = 0;
    _fechaInscripcion = Fecha();
    strcpy(_estado, "ACTIVA");
    _notaCursada = 1;
    _intentosFinal = 0;
}

Inscripcion::Inscripcion(int idInscripcion, int idAlumno, int idComision,
                         const Fecha &fechaInscripcion, int opcionEstado,
                         int notaCursada, int intentosFinal)
{
    setIdInscripcion(idInscripcion);
    setIdAlumno(idAlumno);
    setIdComision(idComision);
    setFechaInscripcion(fechaInscripcion);
    setEstadoPorOpcion(opcionEstado);
    setNotaCursada(notaCursada);
    setIntentosFinal(intentosFinal);
}

void Inscripcion::setIdInscripcion(int v) { _idInscripcion = (v >= 0 ? v : 0); }
void Inscripcion::setIdAlumno(int v) { _idAlumno = (v >= 0 ? v : 0); }
void Inscripcion::setIdComision(int v) { _idComision = (v >= 0 ? v : 0); }
void Inscripcion::setFechaInscripcion(const Fecha &f) { _fechaInscripcion = f; }
void Inscripcion::setEstadoPorOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        strcpy(_estado, "ACTIVA");
        break;
    case 2:
        strcpy(_estado, "REGULAR");
        break;
    case 3:
        strcpy(_estado, "APROBADA");
        break;
    case 4:
        strcpy(_estado, "BAJA");
        break;
    case 5:
        strcpy(_estado, "LIBRE");
        break;
    default:
        strcpy(_estado, "ACTIVA");
        break;
    }
}

void Inscripcion::setNotaCursada(int nota)
{
    if (nota < 1)
        nota = 1;
    if (nota > 10)
        nota = 10;
    _notaCursada = nota;

    if (_notaCursada < 6)
        _intentosFinal = 0;
}

void Inscripcion::setIntentosFinal(int intentos)
{
    if (intentos < 0)
        intentos = 0;
    if (intentos > 3)
        intentos = 3;
    _intentosFinal = (_notaCursada >= 6) ? intentos : 0;
}

int Inscripcion::getIdInscripcion() const { return _idInscripcion; }
int Inscripcion::getIdAlumno() const { return _idAlumno; }
int Inscripcion::getIdComision() const { return _idComision; }
Fecha Inscripcion::getFechaInscripcion() const { return _fechaInscripcion; }
const char *Inscripcion::getEstado() const { return _estado; }
int Inscripcion::getNotaCursada() const { return _notaCursada; }
int Inscripcion::getIntentosFinal() const { return _intentosFinal; }

bool Inscripcion::puedeInscribirseAFinal() const
{
    return (_notaCursada >= 6) && (_intentosFinal < 3);
}

bool Inscripcion::inscribirAFinal()
{
    if (_notaCursada < 6)
    {
        cout << "No se pudo inscribir porque NO esta REGULAR (nota de cursada "
             << _notaCursada << ", necesita >= 6).\n";
        return false;
    }
    if (_intentosFinal >= 3)
    {
        cout << "No se pudo inscribir porque ya alcanzo el maximo de 3 intentos de final.\n";
        return false;
    }

    _intentosFinal++;
    cout << "Se inscribio correctamente al final. Intento "
         << _intentosFinal << " de 3.\n";
    return true;
}

void Inscripcion::cargar()
{
    cout << "=== Cargar Inscripcion ===\n";

    cout << "ID Inscripcion: ";
    cin >> _idInscripcion;
    while (_idInscripcion < 0)
    {
        cout << "Valor invalido. Reingrese (>=0): ";
        cin >> _idInscripcion;
    }

    cout << "ID Alumno: ";
    cin >> _idAlumno;
    while (_idAlumno < 0)
    {
        cout << "Valor invalido. Reingrese (>=0): ";
        cin >> _idAlumno;
    }

    cout << "ID Comision: ";
    cin >> _idComision;
    while (_idComision < 0)
    {
        cout << "Valor invalido. Reingrese (>=0): ";
        cin >> _idComision;
    }

    cout << "Fecha de Inscripcion:\n";
    _fechaInscripcion.cargar();

    int opEstado;
    cout << "Estado:\n";
    cout << "  1) ACTIVA\n";
    cout << "  2) REGULAR\n";
    cout << "  3) APROBADA\n";
    cout << "  4) BAJA\n";
    cout << "  5) LIBRE\n";
    cout << "Elegir opcion (1-5): ";
    cin >> opEstado;
    while (opEstado < 1 || opEstado > 5)
    {
        cout << "Opcion invalida. Reingrese (1-5): ";
        cin >> opEstado;
    }
    setEstadoPorOpcion(opEstado);

    cout << "Nota de cursada (1-10): ";
    cin >> _notaCursada;
    while (_notaCursada < 1 || _notaCursada > 10)
    {
        cout << "Invalida. Reingrese (1-10): ";
        cin >> _notaCursada;
    }

    if (_notaCursada >= 6)
    {
        cout << "Intentos de final ya realizados (0-3): ";
        cin >> _intentosFinal;
        while (_intentosFinal < 0 || _intentosFinal > 3)
        {
            cout << "Invalido. Reingrese (0-3): ";
            cin >> _intentosFinal;
        }
    }
    else
    {
        _intentosFinal = 0;
        cout << "Nota < 6 -> no habilita final. Intentos = 0.\n";
    }

    cout << "--- Intentando inscribir al final ---\n";
    inscribirAFinal();
}

void Inscripcion::mostrar() const
{
    cout << toString() << endl;
}

std::string Inscripcion::toString() const
{
    stringstream ss;
    ss << "Inscripcion #" << _idInscripcion
       << " | Alumno: " << _idAlumno
       << " | Comision: " << _idComision
       << " | Fecha: " << _fechaInscripcion.toString()
       << " | Estado: " << _estado
       << " | NotaCursada: " << _notaCursada
       << " | IntentosFinal: " << _intentosFinal
       << " | Puede rendir: " << (puedeInscribirseAFinal() ? "SI" : "NO");
    return ss.str();
}
