#pragma once
#include "ArchivoMateria.h"
#include "ArchivoCarrera.h"
#include "Materia.h"
#include <string>

class ManagerMateria {
private:
    ArchivoMateria _archivoMaterias{"Materias.dat"};
    ArchivoCarrera _archivoCarreras{"Carreras.dat"};

    // Helpers
    std::string nombreCarrera(int idCarrera);
    bool obtenerMateriaValida(int id, Materia& out);
    bool obtenerMateriaActiva(int id, Materia& out);

    void listar(bool activas, bool inactivas, const std::string& titulo);

public:
    // ABM
    void alta();
    void baja();
    void modificacion();
    void activar();

    // Listados
    void listarTodas();
    void listarMateriasActivas();
    void listarMateriasInactivas();

    // Correlativas
    void verCorrelativas();

    // Utilitarios
    int buscarPorId(int idMateria);
    int generarIdNuevo();
};
