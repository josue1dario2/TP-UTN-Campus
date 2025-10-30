#pragma once

class MenuDocente{
public:
    MenuDocente();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    //PersonalManager _personalManager;
    int _cantidadOpciones;
    void mostrarSubmenuNotas();
    int seleccionarSubopcionNotas();
};


