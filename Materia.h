#pragma once
#include <string>

class Materia {
public:
    Materia();
    Materia(int idMateria, int idCarrera, const char* codigo, const char* nombre, int cuatrimestreSugerido, bool eliminado);

    // Setters
    void setIdMateria(int idMateria);
    void setIdCarrera(int idMateria);
    void setCodigo(const char* codigo);
    void setNombre(const char* nombre);
    void setCuatrimestreSugerido(int cuatrimestreSugerido);
    void setEliminado(bool eliminado);

    // Getters
    int getIdMateria() const;
    int getIdCarrera() const;
    const char* getCodigo() const;
    const char* getNombre() const;
    int getCuatrimestreSugerido() const;
    bool getEliminado() const;

    // Método para cargar datos por consola
    void cargar();

    // Método para mostrar datos por consola
    void mostrar() const;
    std::string toString() const;

private:
    int _IdMateria;
    int _idCarrera;
    char _codigo[10];
    char _nombre[50];
    int _cuatrimestreSugerido;
    bool _eliminado;
};
