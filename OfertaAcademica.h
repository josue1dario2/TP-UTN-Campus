
#pragma once
#include <string>

class OfertaAcademica {
public:
    OfertaAcademica();
    OfertaAcademica(int idPlanMateria, int modalidad, const char* aula, bool activa);

    // Setters:
    void setIdPlanMateria(int idPlanMateria);
    void setModalidad(int modalidad);
    void setAula(const char* aula);
    void setActiva(bool activa);


    // Getters:

    int getIdPlanMateria() const;
    int getModalidad() const;
    const char* getAula() const;
    bool getActiva() const;


    // Método para cargar datos por consola
    void cargar();

    // Método para mostrar datos por consola
    void mostrar() const;
    std::string toString() const;




private:
    int _idPlanMateria;
    int _modalidad;
    char _aula[20];
    bool _activa;





};
