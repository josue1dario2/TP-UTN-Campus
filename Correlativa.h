#pragma once
#include <string>

class Correlativa {
public:
    Correlativa();
    Correlativa(int idMateriaObjetivo, int idMateriaRequisito,bool eliminado = false);

    int  getIdMateriaObjetivo() const;  void setIdMateriaObjetivo(int idMateriaObjetivo);
    int  getIdMateriaRequisito() const; void setIdMateriaRequisito(int idMateriaRequisito);
    bool getEliminado() const;          void setEliminado(bool eliminado);

    void cargar();
    void mostrar() const;

private:
    int  _idMateriaObjetivo;
    int  _idMateriaRequisito;
    bool _eliminado;
};
