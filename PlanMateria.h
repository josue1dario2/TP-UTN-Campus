#pragma once
#include <string>

class PlanMateria
{
public:
    PlanMateria();
    PlanMateria(int idPlanMateria, int plan, int idMateria, int anio, int dictado, bool activo);

    int get_idPlanMateria() const;
    int get_plan() const;
    int get_idMateria() const;
    int get_anio() const;
    int get_dictado() const;
    bool get_activo() const;

    void set_idPlanMateria(int idPlanMateria);
    void set_plan(int plan);
    void set_idMateria(int idMateria);
    void set_anio(int anio);
    void set_dictado(int dictado);
    void set_activo(bool activo);

    void cargar();
    void mostrar() const;
    std::string toString() const;

private:
    int _idPlanMateria;
    int _plan;
    int _idMateria;
    int _anio;
    int _dictado;
    bool _activo;
};
