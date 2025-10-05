#include "DocenteMateria.h"
#include <cstring>

DocenteMateria::DocenteMateria() {
    idDocente = 0;
    idPlanMateria = 0;
    rol[0] = '\0';
}

DocenteMateria::DocenteMateria(int idDocente, int idPlanMateria, const char* rol) {
    this->idDocente = idDocente;
    this->idPlanMateria = idPlanMateria;
    setRol(rol);
}

// Getters
int DocenteMateria::getIdDocente() const {
    return idDocente;
}

int DocenteMateria::getIdPlanMateria() const {
    return idPlanMateria;
}

const char* DocenteMateria::getRol() const {
    return rol;
}

// Setters
void DocenteMateria::setIdDocente(int id) {
    idDocente = id;
}

void DocenteMateria::setIdPlanMateria(int id) {
    idPlanMateria = id;
}

void DocenteMateria::setRol(const char* nuevoRol) {
    strncpy(rol, nuevoRol, sizeof(rol) - 1);
    rol[sizeof(rol) - 1] = '\0'; 
}