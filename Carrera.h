#pragma once
#include <string>

class Carrera {
public:
    Carrera();
    Carrera(int, const char*, int, bool);
    int get_idCarrera() const;
    const char* get_nombre() const;
    int get_duracionCuatrimestres() const;
    bool get_eliminado() const;
    void set_idCarrera(int);
    void set_nombre(const char*);
    void set_duracionCuatrimestres(int);
    void set_eliminado(bool);
    void cargar();
    void mostrar() const;
    std::string toString() const;
private:
    int _idCarrera;
    char _nombre[50];
    int _duracionCuatrimestres;
    bool _eliminado;
};
