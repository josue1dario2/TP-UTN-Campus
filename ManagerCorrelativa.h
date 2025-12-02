#pragma once
#include "ArchivoCorrelativa.h"
#include "ArchivoMateria.h"
#include "Correlativa.h"
#include "Materia.h"
#include <string>

class ManagerCorrelativa {
private:
    ArchivoCorrelativa _archivo;
    ArchivoMateria _archMat;

    bool existeMateria(int id);
    bool materiaEliminada(int id);

    bool existeCorrelativa(int idObj, int idReq);
    int  buscarPosCorrelativa(int idObj, int idReq);
    int  contarCorrelativas(int idObj);

    void listarMateriasActivas(const std::string& titulo);
    void listarCorrelativasDeMateria(int idObj);

    int pedirMateriaValida(const std::string& mensaje);
    int pedirCorrelativaValida(int idObj, const std::string& mensaje);

public:
    ManagerCorrelativa();

    void agregar();
    void listar();
    void modificar();
    void borrar();

    bool tieneCorrelativas(int idMateria);
};
