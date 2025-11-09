#pragma once
#include <string>

class Materia {
public:
    Materia();
    Materia(int idMateria, int idCarrera, const char* nombre, int cuatrimestre, const char* estado, bool eliminado = false);

    void setIdMateria(int idMateria);
    void setIdCarrera(int idCarrera);
    void setNombre(const char* nombre);
    void setCuatrimestre(int cuatrimestre);
    void setEstado(const char* estado);
    void setEliminado(bool eliminado);

    int getIdMateria() const;
    int getIdCarrera() const;
    const char* getNombre() const;
    int getCuatrimestre() const;
    const char* getEstado() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;

private:
    int  _idMateria;
    int  _idCarrera;
    char _nombre[50];
    int  _cuatrimestre;
    char _estado[20];
    bool _eliminado;
};
