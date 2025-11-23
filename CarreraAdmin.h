#pragma once
#include "ManagerCarrera.h"

class MenuABMCarrerasAdmin {
public:
    MenuABMCarrerasAdmin();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    void altaCarrera();
    void modificarCarrera();
    void bajaLogicaCarrera();
    void activarCarrera();
    void listarCarreras();

private:
    int _cantidadOpciones;
    ManagerCarrera _carreraManager;
};
