#pragma once

#include "Validacion.h"


class MenuCopiaSeguridad {
public:
    MenuCopiaSeguridad();
    void mostrar(int eleccion);

protected:
    void mostrarOpciones(int eleccion);
    //void realizarCopiaSeguridad();
    //void mostrarOpcionesSeguridad();
    void ejecutarOpcion(int opcion, int eleccion);
    //void restaurarCopiaSeguridad();
    //void exportarDatosCSV();
    int seleccionOpcion(int eleccion);

private:
    Validacion validar;
    // Manager
    int _cantidadOpciones;

};


