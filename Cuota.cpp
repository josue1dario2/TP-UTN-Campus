#include "Cuota.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include "Validacion.h"

using namespace std;

Cuota::Cuota() {
    _idCuota = 0;
    _idAlumno = 0;
    std::strcpy(_periodo, "");   // vacío
    _monto = 0.0f;
    _fechaVencimiento = Fecha(); // tu ctor default
    _estaPagada = false;
}

Cuota::Cuota(int idCuota, int idAlumno, const char* periodo,
             float monto, const Fecha& fechaVenc, bool estaPagada) {
    setIdCuota(idCuota);
    setIdAlumno(idAlumno);
    setPeriodo(periodo);
    setMonto(monto);
    setFechaVencimiento(fechaVenc);
    setEstaPagada(estaPagada);
}

void Cuota::setIdCuota(int v)        { _idCuota  = (v >= 0 ? v : 0); }
void Cuota::setIdAlumno(int v)       { _idAlumno = (v >= 0 ? v : 0); }

void Cuota::setPeriodo(const char* s) {
    if (s == nullptr) { _periodo[0] = '\0'; return; }
    std::strncpy(_periodo, s, sizeof(_periodo)-1);
    _periodo[sizeof(_periodo)-1] = '\0';
}

void Cuota::setMonto(float v) {
    if (v < 0.0f) v = 0.0f;
    _monto = v;
}

void Cuota::setFechaVencimiento(const Fecha& f) {
    _fechaVencimiento = f; // la validación la hace Fecha
}

void Cuota::setEstaPagada(bool v) {
    _estaPagada = v;
}

int         Cuota::getIdCuota()        const { return _idCuota; }
int         Cuota::getIdAlumno()       const { return _idAlumno; }
const char* Cuota::getPeriodo()        const { return _periodo; }
float       Cuota::getMonto()          const { return _monto; }
Fecha       Cuota::getFechaVencimiento() const { return _fechaVencimiento; }
bool        Cuota::getEstaPagada()     const { return _estaPagada; }

void Cuota::marcarPagada() { _estaPagada = true; }

void Cuota::cargar() {
    cout << "=== Cargar Cuota ===\n";

    _idCuota  = Validacion::validarEnteroNoNegativo("ID Cuota (>=0): ");
    _idAlumno = Validacion::validarEnteroNoNegativo("ID Alumno (>=0): ");

    // Periodo (texto corto) – ejemplo: "MAR-2025" o "2025-03"
    // Permitimos 1..19 caracteres, sin ciertos símbolos
    const string PROHIBIDOS = "°|¬!#$%&/()=?¡¨*[];:'~^`+";
    string per = Validacion::pedirEntradaCadena("Periodo (ej. MAR-2025 / 2025-03): ",
                                                1, 19, PROHIBIDOS);
    setPeriodo(per.c_str());

    // Monto (>=0) – pedimos como entero o flotante simple
    // Si querés estrictamente float con coma, podés usar string->stof con try/catch.
    cout << "Monto (>=0): ";
    float m;
    while (!(cin >> m) || m < 0.0f) {
        cout << "Invalido. Reingrese monto (>=0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    setMonto(m);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // limpiar \n que queda

    // Fecha de vencimiento
    cout << "Fecha de vencimiento:\n";
    _fechaVencimiento.cargar();

    // Estado de pago (bool)
    bool pagada = Validacion::validarBool("¿Esta pagada? (s/n): ");
    setEstaPagada(pagada);
}

void Cuota::mostrar() const {
    cout << toString() << endl;
}

std::string Cuota::toString() const {
    stringstream ss;
    ss << "Cuota #" << _idCuota
       << " | Alumno: " << _idAlumno
       << " | Periodo: " << _periodo
       << " | Monto: " << _monto
       << " | Venc.: " << _fechaVencimiento.toString()
       << " | Pagada: " << (_estaPagada ? "SI" : "NO");
    return ss.str();
}
