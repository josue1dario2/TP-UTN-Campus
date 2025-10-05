#include "Horario.h"
#include <cstring>

Horario::Horario() {
    idHorario = 0;
    idComision = 0;
    diaSemana = 1;
    horaInicio[0] = '\0';
    horaFin[0] = '\0';
}

Horario::Horario(int idHorario, int idComision, int diaSemana, const char* horaInicio, const char* horaFin) {
    this->idHorario = idHorario;
    this->idComision = idComision;
    this->diaSemana = diaSemana;
    setHoraInicio(horaInicio);
    setHoraFin(horaFin);
}

// Getters
int Horario::getIdHorario() const {
    return idHorario;
}

int Horario::getIdComision() const {
    return idComision;
}

int Horario::getDiaSemana() const {
    return diaSemana;
}

const char* Horario::getHoraInicio() const {
    return horaInicio;
}

const char* Horario::getHoraFin() const {
    return horaFin;
}

// Setters
void Horario::setIdHorario(int id) {
    idHorario = id;
}

void Horario::setIdComision(int id) {
    idComision = id;
}

void Horario::setDiaSemana(int dia) {
    diaSemana = dia;
}

void Horario::setHoraInicio(const char* hora) {
    strncpy(horaInicio, hora, sizeof(horaInicio) - 1);
    horaInicio[sizeof(horaInicio) - 1] = '\0';
}

void Horario::setHoraFin(const char* hora) {
    strncpy(horaFin, hora, sizeof(horaFin) - 1);
    horaFin[sizeof(horaFin) - 1] = '\0';
}