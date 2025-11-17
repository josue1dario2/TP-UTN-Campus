#pragma once
#include "ArchivoMateria.h"
#include "ArchivoCarrera.h"
#include "Materia.h"
#include "Carrera.h"
#include <iostream>

class MateriaManager {
public:

    MateriaManager();

    void cargar();
    void modificar();
    void borrar();
    void activar();
    void listar();

protected:
    void mostrar(Materia materia) const;
    Materia _materia;

private:

    ArchivoMateria _repoMateria;
    ArchivoCarrera _repoCarrera; // Para validar la existencia de carreras

    void mostrarEncabezado() const; //mod
    void mostrarPie()const; //mod
    void mostrarRegistro(const Materia& materia) const; //mod
    Materia ingresarDatos(int idMateria);
    void cambiarEstado(bool activar);

    // Métodos de validación
    bool validarCarreraExiste(int idCarrera);
    bool validarCodigoUnico(const char* codigo, int idMateriaActual = -1);
    bool validarCuatrimestre(int cuatrimestre, int idCarrera);
};
