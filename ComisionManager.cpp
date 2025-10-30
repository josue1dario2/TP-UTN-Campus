#include "ComisionManager.h"
#include <iomanip>

ComisionManager::ComisionManager() : _archivo("Comisiones.dat") {}

void ComisionManager::mostrarTodasLasComisiones() {
    int total = _archivo.contarRegistros();
    if (total == 0) {
        std::cout << "No hay comisiones registradas.\n";
        return;
    }

    std::cout << "\n\tLISTADO DE COMISIONES\n";
    std::cout << "\t---------------------------------------\n";

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado()) {
            std::cout << "ID Comision: " << c.getIdComision() << std::endl;
            std::cout << "ID Materia: " << c.getIdMateria() << std::endl;
            std::cout << "Turno: " << c.getTurno() << std::endl;
            std::cout << "Modalidad: " << c.getModalidad() << std::endl;
            std::cout << "Cuatrimestre: " << c.getCuatrimestre() << std::endl;
            std::cout << "Año: " << c.getAnio() << std::endl;
            std::cout << "-----------------------------\n";
        }
    }
}

void ComisionManager::mostrarComisionesPorMateria(int idMateria) {
    int total = _archivo.contarRegistros();
    bool encontrado = false;

    std::cout << "\n\tCOMISIONES DE LA MATERIA " << idMateria << "\n";
    std::cout << "\t---------------------------------------\n";

    for (int i = 0; i < total; i++) {
        Comision c = _archivo.leerRegistro(i);
        if (!c.getEliminado() && c.getIdMateria() == idMateria) {
            encontrado = true;
            std::cout << "ID Comision: " << c.getIdComision() << std::endl;
            std::cout << "Turno: " << c.getTurno() << std::endl;
            std::cout << "Modalidad: " << c.getModalidad() << std::endl;
            std::cout << "Cuatrimestre: " << c.getCuatrimestre() << std::endl;
            std::cout << "Año: " << c.getAnio() << std::endl;
            std::cout << "-----------------------------\n";
        }
    }

    if (!encontrado)
        std::cout << "No hay comisiones registradas para esta materia.\n";
}
