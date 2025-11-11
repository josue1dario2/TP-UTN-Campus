#pragma once

class MenuABMComisiones{
public:
    MenuABMComisiones();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    int _cantidadOpciones;
};


