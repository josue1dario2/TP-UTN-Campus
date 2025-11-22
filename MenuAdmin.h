#pragma once

#include "MenuAbmCarreras.h"
#include "MenuAbmComisiones.h"
#include "MenuAbmMaterias.h"
#include "ManagerAlumno.h"

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

    MenuABMCarreras menuCarreras;
    MenuABMComisiones menuComisiones;
    MenuABMMaterias menuMaterias;

    // Para aprobar / rechazar solicitudes de baja
    ManagerAlumno _managerAlumno;
};
