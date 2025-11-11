#pragma once
#include "ArchivoCarrera.h"
#include "Carrera.h"
#include <iostream>

class ManagerCarrera
{
public:
    ManagerCarrera();

    // --- Métodos públicos de gestión ---
    void buscar();      ///< Buscar carrera por ID (implementación futura)
    void cargar();      ///< Cargar un nuevo registro de carrera
    void modificar();   ///< Modificar datos de una carrera existente
    void borrar();      ///< Realizar borrado lógico de un registro
    void activar();     ///< Reactivar un registro previamente borrado
    void listar();      ///< Listar todas las carreras (opcionalmente incluye borradas)

protected:
    void mostrar(Carrera _carrera) const; ///< Muestra los datos completos de una carrera
    Carrera _carrera;                     ///< Objeto temporal para manipular registros

private:
    ArchivoCarrera _repoCarrera; ///< Repositorio que maneja el archivo binario de carreras

    // --- Métodos auxiliares de presentación ---
    void mostrarEncabezado();                     ///< Muestra encabezado de tabla
    void mostrarPie();                            ///< Muestra pie de tabla
    void mostrarRegistro(const Carrera& _carrera);///< Muestra un registro formateado
    Carrera ingresarDatos(int _idCarrera);        ///< Solicita y valida datos de entrada
    void cambiarEstado(bool activar); ///< Cambia el estado lógico de un registro (borrar/activar)
};
