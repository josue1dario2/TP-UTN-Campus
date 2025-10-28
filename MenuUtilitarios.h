#pragma once

#include "Validacion.h"


class MenuUtilitarios {
public:
    MenuUtilitarios();
    void mostrar();

protected:
    void mostrarOpciones();
    void realizarCopiaSeguridad();
    void mostrarOpcionesSeguridad();
    void ejecutarOpcion(int opcion);
    void restaurarCopiaSeguridad();
    void exportarDatosCSV();
    int seleccionOpcion();

private:
    Validacion validar;
    // Manager
    int _cantidadOpciones;
    int _cantidadOpcionesSeguridad;
};


