#pragma once
#include <iostream>

class Correlativa 
{
public:
    // Constructor por defecto
    Correlativa();

    // Constructor con parámetros
    Correlativa(int idCorrelativa, int plan, int idObjetivo, int idReq, int tipo);

    // Setters
    void setIdCorrelativa(int id);
    void setPlan(int plan);
    void setIdPlanMateriaObjetivo(int idObjetivo);
    void setIdPlanMateriaReq(int idReq);
    void setTipoCorrelativa(int tipo);

    // Getters
    int getIdCorrelativa() const;
    int getPlan() const;
    int getIdPlanMateriaObjetivo() const;
    int getIdPlanMateriaReq() const;
    int getTipoCorrelativa() const;

    // Métodos
    void mostrar() const;
    void cargar();

private:
int _idCorrelativa;
int _plan;
int _idPlanMateriaObjetivo;
int _idPlanMateriaReq;
int _tipoCorrelativa;

};