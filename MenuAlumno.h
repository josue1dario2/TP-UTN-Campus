#pragma once

class MenuAlumno{
public:
    MenuAlumno();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    //PersonalManager _personalManager;
    int _cantidadOpciones;

};

