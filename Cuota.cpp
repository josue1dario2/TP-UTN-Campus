
#include <limits>
#include <iostream>

#include "Cuota.h"
#include "Validacion.h"
using namespace std;

Cuota::Cuota() {
    setIdCuota(0);
    setMonto(0.0);
    setFechaVencimiento(Fecha());
    setPagada(false);
}

Cuota::Cuota(int idCuota, double monto, const Fecha& fechaVencimiento, bool pagada) {
    setIdCuota(idCuota);
    setMonto(monto);
    setFechaVencimiento(fechaVencimiento);
    setPagada(pagada);
}

// Setters
void Cuota::setIdCuota(int idCuota) { _idCuota = idCuota; }
void Cuota::setMonto(double monto) { _monto = monto; }
void Cuota::setFechaVencimiento(const Fecha& fechaVencimiento) { _fechaVencimiento = fechaVencimiento; }
void Cuota::setPagada(bool pagada) { _pagada = pagada; }

// Getters
int Cuota::getIdCuota() const { return _idCuota; }
double Cuota::getMonto() const { return _monto; }
Fecha Cuota::getFechaVencimiento() const { return _fechaVencimiento; }
bool Cuota::getPagada() const { return _pagada; }

// Métodos
void Cuota::cargar() {
    _idCuota = Validacion::validarEntero("Ingrese ID de la cuota: ");
    cout << "Ingrese monto de la cuota: ";
    cin >> _monto;
    cout << "Ingrese fecha de vencimiento:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    _fechaVencimiento.cargar();
    _pagada = Validacion::validarBool("¿Pagada? (1=si, 0=no): ");
}

void Cuota::mostrar() const {
    cout << toString() << endl;
}

std::string Cuota::toString() const {
    std::string s = "ID Cuota: " + std::to_string(_idCuota) + "\n";
    s += "Monto: $" + std::to_string(_monto) + "\n";
    s += "Fecha de vencimiento: " + _fechaVencimiento.toString() + "\n";
    s += "Pagada: " + std::string(_pagada ? "Sí" : "No") + "\n";
    return s;
}
