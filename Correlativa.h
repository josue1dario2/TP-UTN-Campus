#pragma once
#include <string>

class Correlativa {
public:
    Correlativa();
    Correlativa(int idCarrera, int idMateriaObjetivo, int idMateriaRequisito,
                int tipo, bool eliminado = false);

    int  getIdCarrera() const;          void setIdCarrera(int idCarrera);
    int  getIdMateriaObjetivo() const;  void setIdMateriaObjetivo(int idMateriaObjetivo);
    int  getIdMateriaRequisito() const; void setIdMateriaRequisito(int idMateriaRequisito);
    int  getTipo() const;               void setTipo(int tipo); // 1=Regularizada, 2=Aprobada
    bool getEliminado() const;          void setEliminado(bool eliminado);

    void cargar();
    void mostrar() const;

private:
    int  _idCarrera;
    int  _idMateriaObjetivo;
    int  _idMateriaRequisito;
    int  _tipo;      // 1=Regularizada, 2=Aprobada
    bool _eliminado;
};
