#pragma once
#include <string>

class Materia {
public:
    Materia();
    Materia(int idMateria, int idCarrera, const char* nombre, int cuatrimestreSugerido,const char* estado, bool eliminado);

    void setIdMateria(int idMateria);
    void setIdCarrera(int idMateria);
    void setNombre(const char* nombre);
    void setCuatrimestreSugerido(int cuatrimestreSugerido);
    void setEstado(const char* estado);
    void setEliminado(bool eliminado);

    int getIdMateria() const;
    int getIdCarrera() const;
    const char* getNombre() const;
    int getCuatrimestreSugerido() const;
    const char* getEstado() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;

private:
    int _idMateria;
    int _idCarrera;
    char _nombre[50];
    int _cuatrimestreSugerido;
    char _estado[20];
    bool _eliminado;
};

