#ifndef HORARIO_H
#define HORARIO_H

class Horario {
private:
    int idHorario;
    int idComision;
    int diaSemana;
    char horaInicio[6];
    char horaFin[6];

public:
    Horario();

    Horario(int idHorario, int idComision, int diaSemana, const char* horaInicio, const char* horaFin);

    // Getters
    int getIdHorario() const;
    int getIdComision() const;
    int getDiaSemana() const;
    const char* getHoraInicio() const;
    const char* getHoraFin() const;

    // Setters
    void setIdHorario(int id);
    void setIdComision(int id);
    void setDiaSemana(int dia);
    void setHoraInicio(const char* hora);
    void setHoraFin(const char* hora);
};

#endif