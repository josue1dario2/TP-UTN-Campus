#include "MesaDocente.h"
#include <cstring>
#include <iostream>

MesaDocente::MesaDocente() {
    _rol[0] = '\0';
}

MesaDocente::MesaDocente(int idMesa, int idDocente, const std::string& rol) {
    _idMesa = idMesa;
    _idDocente = idDocente;
    setRol(rol);
}

void MesaDocente::setIdMesa(int idMesa) { _idMesa = idMesa; }
void MesaDocente::setIdDocente(int idDocente) { _idDocente = idDocente; }

void MesaDocente::setRol(const std::string& rol) {
    std::strncpy(_rol, rol.c_str(), sizeof(_rol) - 1);
    _rol[sizeof(_rol) - 1] = '\0';
}

int MesaDocente::getIdMesa() const { return _idMesa; }
int MesaDocente::getIdDocente() const { return _idDocente; }
const char* MesaDocente::getRol() const { return _rol; }

std::string MesaDocente::toString() const {
    return "MesaDocente{ idMesa=" + std::to_string(_idMesa) +
           ", idDocente=" + std::to_string(_idDocente) +
           ", rol=" + _rol + " }";
}

void MesaDocente::mostrar() const {
    std::cout << toString() << std::endl;
}
