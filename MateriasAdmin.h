#pragma once
#include "ManagerMateria.h"

class MenuABMMateriasAdmin {
public:
    MenuABMMateriasAdmin();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    void altaMateria();
    void modificarMateria();
    void bajaLogicaMateria();
    void activarMateria();
    void listarMaterias();

private:
    int _cantidadOpciones;
    ManagerMateria _managerMateria;

};
