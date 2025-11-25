#pragma once
#include "ArchivoMateria.h"
#include "ArchivoCarrera.h"
#include "Materia.h"

class ManagerMateria {
private:
    ArchivoMateria _archivoMaterias;
    ArchivoCarrera _archivoCarreras;


public:
    void alta();
    void baja();
    void modificacion();
    void listarTodas();
    int buscarPorId(int idMateria);
    int generarIdNuevo();
    void activar();


};
