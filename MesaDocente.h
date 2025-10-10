#pragma once
#include <string>

class MesaDocente {
private:
    int  _idMesa{};
    int  _idDocente{};
    char _rol[20]{};

public:
    MesaDocente();

    MesaDocente(int idMesa, int idDocente, const std::string& rol);

    void setIdMesa(int idMesa);
    void setIdDocente(int idDocente);
    void setRol(const std::string& rol);

    int getIdMesa() const;
    int getIdDocente() const;
    const char* getRol() const;

    std::string toString() const;
    void mostrar() const;
};
