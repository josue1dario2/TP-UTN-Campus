#pragma once
#include "ArchivoCorrelativa.h"
#include "Correlativa.h"
#include <iostream>
#include <iomanip>

class ManagerCorrelativa {
private:
    ArchivoCorrelativa _archivo;

public:
    ManagerCorrelativa();

    bool tieneCorrelativas(int idMateria);
    bool existeCorrelativa(int idMateriaObj, int idMateriaReq);

    void listarTabla();
};
