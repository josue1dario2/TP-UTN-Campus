#pragma once
#include <string>

class Comision {
public:
    Comision();
    Comision(int idComision, int idCursada, const char* codigo, const char* turno, const char* modalidad, const char* aula, int cupo);

    void setIdComision(int id);
    void setIdCursada(int id);
    void setCodigo(const char* cod);
    void setTurno(const char* t);
    void setModalidad(const char* m);
    void setAula(const char* a);
    void setCupo(int c);

    int getIdComision() const;
    int getIdCursada() const;
    const char* getCodigo() const;
    const char* getTurno() const;
    const char* getModalidad() const;
    const char* getAula() const;
    int getCupo() const;
    bool getEliminado() const;

    void cargar();
    void mostrar() const;
    std::string toString() const;


private:
    int _idComision;
    int _idCursada;
    char _codigo[20];
    char _turno[10];          // "Mañana"/"Tarde"/"Noche"
    char _modalidad[10];      // "Presencial"/"Virtual"/"Híbrida"
    char _aula[20];
    int _cupo;
    bool _eliminado;
};
