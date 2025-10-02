#pragma once
#include <string>

class Comision {
public:
    Comision();
    Comision(int idComision, int idCursada, const char* codigo, int turno, int modalidad, const char* aula, int cupo);

    // Setters:
    void setIdComision(int id);
    void setIdCursada(int id);
    void setCodigo(const char* cod);
    void setTurno(int t);
    void setModalidad(int m);
    void setAula(const char* a);
    void setCupo(int c);

    // Getters:
    int getIdComision() const;
    int getIdCursada() const;
    const char* getCodigo() const;
    int getTurno() const;
    int getModalidad() const;
    const char* getAula() const;
    int getCupo() const;

    // Método para cargar datos por consola
    void cargar();

    // Método para mostrar datos por consola
    void mostrar() const;
    std::string toString() const;


private:
    int _idComision;
    int _idCursada;
    char _codigo[20];
    int _turno;
    int _modalidad;
    char _aula[20];
    int _cupo;
};
