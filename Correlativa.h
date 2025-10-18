#pragma once
#include <iostream>

class Correlativa {
private:
    int  _idCorrelativa;
    int  _idCarrera;
    int  _idMateriaObjetivo;
    int  _idMateriaRequisito;
    int  _tipoCorrelativa;     // 1=Regularizada, 2=Aprobada, etc.
    bool _eliminado;

public:
    Correlativa();
    Correlativa(int idCorrelativa, int idCarrera, int idMateriaObjetivo,
                int idMateriaRequisito, int tipoCorrelativa, bool eliminado = false);

    void setIdCorrelativa(int idCorrelativa);
    void setIdCarrera(int idCarrera);
    void setIdMateriaObjetivo(int idMateriaObjetivo);
    void setIdMateriaRequisito(int idMateriaRequisito);
    void setTipoCorrelativa(int tipoCorrelativa);
    void setEliminado(bool eliminado);

    int  getIdCorrelativa() const;
    int  getIdCarrera() const;
    int  getIdMateriaObjetivo() const;
    int  getIdMateriaRequisito() const;
    int  getTipoCorrelativa() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;
};
