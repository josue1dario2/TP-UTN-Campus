#ifndef DOCENTEMATERIA_H
#define DOCENTEMATERIA_H

class DocenteMateria {
private:
    int idDocente;
    int idPlanMateria;
    char rol[20];

public:
    DocenteMateria();

    DocenteMateria(int idDocente, int idPlanMateria, const char* rol);

    // Getters
    int getIdDocente() const;
    int getIdPlanMateria() const;
    const char* getRol() const;

    // Setters
    void setIdDocente(int id);
    void setIdPlanMateria(int id);
    void setRol(const char* nuevoRol);
};

#endif