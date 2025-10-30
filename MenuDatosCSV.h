#pragma once

#include "Validacion.h"


class MenuDatosCSV {
public:
    MenuDatosCSV();
    void mostrar();

protected:
    void mostrarOpciones();
    void ejecutarOpcion(int opcion);
    int seleccionOpcion();

    //void realizarCopiaSeguridad();
    //void mostrarOpcionesSeguridad();
    //void restaurarCopiaSeguridad();
    //void exportarDatosCSV();


private:
    Validacion validar;
    // Manager
    int _cantidadOpciones;

};


