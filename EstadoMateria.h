#pragma once
#include <string>

class EstadoMateria
{
private:
    int _idEstado;
    int _idAlumno;
    int _plan;
    int _idPlanMateria;
    int _estadoMateriaAlumno; // ej: 0 = sin cursar, 1 = cursando, 2 = regular, 3 = aprobada
    int _ultimaNota;

public:
    EstadoMateria();
    EstadoMateria(int idEstado, int idAlumno, int plan, int idPlanMateria, int estadoMateriaAlumno, int ultimaNota);

    void setIdEstado(int idEstado);
    void setIdAlumno(int idAlumno);
    void setPlan(int plan);
    void setIdPlanMateria(int idPlanMateria);
    void setEstadoMateriaAlumno(int estadoMateriaAlumno);
    void setUltimaNota(int ultimaNota);

    int getIdEstado() const;
    int getIdAlumno() const;
    int getPlan() const;
    int getIdPlanMateria() const;
    int getEstadoMateriaAlumno() const;
    int getUltimaNota() const;

    void cargar();
    void mostrar() const;
    std::string toString() const;
};
