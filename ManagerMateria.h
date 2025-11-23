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
    void modificacion();
    void listarTodas();
    void listar();
    void borrar();
    void activar();
    void cambiarEstado(bool activar);
    bool existeMateria(int idMateria);

private:
    int generarIdNuevo();
    int buscarPorId(int idMateria);
    void mostrarEncabezado();
    void mostrarPie();
    void mostrar(Materia _materia) const;
    void mostrarRegistro(const Materia& _materia);

};
