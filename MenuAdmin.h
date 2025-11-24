#pragma once

#include "MenuAbmCarrera.h"
#include "MenuAbmComision.h"
#include "MenuAbmMateria.h"
#include "MenuAbmCorrelativa.h"
#include "ManagerAlumno.h"
#include "ManagerDocente.h"

class MenuAdministrador {
public:
    MenuAdministrador();
    void mostrar();

protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

private:
    int _cantidadOpciones;

    MenuAbmCarrera menuCarrera;
    MenuAbmComision menuComision;
    MenuAbmMateria menuMateria;
    MenuAbmCorrelativa menuCorrelativa;

    ManagerAlumno _managerAlumno;
    ManagerDocente _managerDocente;
};
