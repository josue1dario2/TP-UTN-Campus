#pragma once

class MenuABMComisionesAdmin {
public:
    MenuABMComisionesAdmin();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    void altaComision();
    void modificarComision();
    void bajaLogicaComision();
    void activarComision();
    void listarComisiones();

private:
    int _cantidadOpciones;
};
