#pragma once
#include "Fecha.h"
#include <string>

class Inscripcion
{
private:
    int _idInscripcion;
    int _idAlumno;
    int _idComision;
    Fecha _fechaInscripcion;
    char _estado[20];
    int _notaCursada;
    int _intentosFinal;

public:
    Inscripcion();
    Inscripcion(int idInscripcion, int idAlumno, int idComision,
                const Fecha &fechaInscripcion, int opcionEstado,
                int notaCursada, int intentosFinal);

    void setIdInscripcion(int v);
    void setIdAlumno(int v);
    void setIdComision(int v);
    void setFechaInscripcion(const Fecha &f);
    void setEstadoPorOpcion(int opcion);
    void setNotaCursada(int nota);
    void setIntentosFinal(int intentos);

    int getIdInscripcion() const;
    int getIdAlumno() const;
    int getIdComision() const;
    Fecha getFechaInscripcion() const;
    const char *getEstado() const;
    int getNotaCursada() const;
    int getIntentosFinal() const;

    bool puedeInscribirseAFinal() const;
    bool inscribirAFinal();

    void cargar();
    void mostrar() const;
    std::string toString() const;
};
