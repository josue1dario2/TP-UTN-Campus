#pragma once
#include "Docente.h"
#include "ManagerDocente.h"
#include "ArchivoDocente.h"


class MenuABMDocentesAdmin {
public:
    MenuABMDocentesAdmin();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    void altaDocente();
    void modificarDocente();
    void bajaLogicaDocente();
    void activarDocente();
    void listarDocentes();
    void buscarDocente();
    int pedirLegajoDocente(const std::string& mensaje, ArchivoDocente _archivoDocentes);

private:
    int _cantidadOpciones;
    ManagerDocente _managerDocente;
    Docente _nuevoDocente;
    ArchivoDocente _archivoDocentes;

};
