#pragma once

#include "Validacion.h"
#include <string>

class MenuCopiaSeguridad {
public:
    MenuCopiaSeguridad();
    void mostrar(int eleccion);

protected:
    void mostrarOpciones(int eleccion);
    void ejecutarOpcion(int opcion, int eleccion);
    int seleccionOpcion(int eleccion);

private:
    Validacion validar;
    int _cantidadOpciones;

    // Métodos de copia y restauración
    void copiarArchivo(const std::string& nombreArchivo);
    void restaurarArchivo(const std::string& nombreArchivo);
    void copiarTodos();
    void restaurarTodos();
    std::string obtenerNombreArchivo(int opcion);
};


