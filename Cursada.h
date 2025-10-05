#pragma once
#include "OfertaAcademica.h"
#include <string>

class Cursada : public OfertaAcademica {
public:
    Cursada();
    Cursada(int idCursada, const char* cicloLectivo,
            int idPlanMateria, int modalidad, const char* aula, bool activa);

    // Setters
    void setIdCursada(int idCursada);
    void setCicloLectivo(const char* cicloLectivo);

    // Getters
    int getIdCursada() const;
    const char* getCicloLectivo() const;

    // Métodos
    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int _idCursada;
    char _cicloLectivo[20];
};
