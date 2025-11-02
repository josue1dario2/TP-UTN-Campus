#pragma once
#include <string>
#include <cstring>
#include <iostream>

class Carrera {
public:
    Carrera();
    Carrera(int idCarrera, const char* nombre, int duracionCuatrimestres, bool eliminado = false);

    int getIdCarrera() const;
    void setIdCarrera(int idCarrera);

    const char* getNombre() const;
    void setNombre(const char* nombre);

    int getDuracionCuatrimestres() const;
    void setDuracionCuatrimestres(int duracion);

    bool getEliminado() const;
    void setEliminado(bool eliminado);
    /*
    void cargar();
    */
    void mostrar() const;

private:
    int  _idCarrera;
    char _nombre[50];
    int  _duracionCuatrimestres;
    bool _eliminado;
};
