#include "MateriaManager.h"
#include "Validacion.h"
#include <iomanip>
#include <cstring>
using namespace std;

MateriaManager::MateriaManager() {
}

// Valida que la carrera exista y no esté eliminada
bool MateriaManager::validarCarreraExiste(int idCarrera) {
    int posicion = _repoCarrera.buscarPosicion(idCarrera);
    if (posicion < 0) {
        cout << "\n\tError: No existe una carrera con ID " << idCarrera << "\n";
        return false;
    }

    Carrera carrera = _repoCarrera.leerRegistro(posicion);
    if (carrera.getEliminado()) {
        cout << "\n\tError: La carrera con ID " << idCarrera << " está eliminada\n";
        return false;
    }

    return true;
}

// Valida que el código de materia sea único
bool MateriaManager::validarCodigoUnico(const char* codigo, int idMateriaActual) {
    int total = _repoMateria.contarRegistros();
    for (int i = 0; i < total; i++) {
        Materia mat = _repoMateria.leerRegistro(i);
        if (!mat.getEliminado() && strcmp(mat.getCodigo(), codigo) == 0) {
            if (idMateriaActual == -1 || mat.getIdMateria() != idMateriaActual) {
                cout << "\n\tError: Ya existe una materia con el código " << codigo << "\n";
                return false;
            }
        }
    }
    return true;
}

Materia MateriaManager::ingresarDatos(int idMateria) {
    int idCarrera;
    string codigo, nombre, estado;
    const int minNombre = 3, maxNombre = 50;
    int cuatrimestre;
    bool valido = false;

    // Validar ID de Carrera
    cin.ignore();
    do {
        idCarrera = Validacion::validarEnteroEnRango("\n\tID de Carrera: ", 1, 10000);
        valido = validarCarreraExiste(idCarrera);
    } while (!valido);

    // Validar Código único
        do {
        codigo = Validacion::pedirEntradaCadena("\tCódigo (ej: MAT101): ", 3, 10);
        valido = validarCodigoUnico(codigo.c_str(), idMateria);
    } while (!valido);


    // Nombre de la materia
    nombre = Validacion::pedirEntradaCadena("\tNombre de la materia: ", minNombre, maxNombre);

    // Ingreso cuatrimetre
    cuatrimestre = Validacion::validarEnteroEnRango("\tCuatrimestre sugerido: ", 1, 2);

    // Estado (Materia Activa/Inactiva)
    string mensaje="\tEstado (1= Activa/2= Inactiva): ";
    int valorEstado=  Validacion::validarEnteroEnRango(mensaje, 1, 2);
    estado = (valorEstado == 1) ? "Activa" : "Inactiva";

    Materia nuevaMateria(idMateria, idCarrera, codigo.c_str(), nombre.c_str(),
                         cuatrimestre, estado.c_str(), false);
    return nuevaMateria;
}

void MateriaManager::cargar() {
    cout << "\n\t=== Alta de Materia ===\n";
    cout << "\tPresione una tecla para continuar\n";

    int idMateria = _repoMateria.contarRegistros() + 1; // Generar nuevo ID
    Materia nuevaMateria = ingresarDatos(idMateria);

    if (Validacion::desearGuardar("")) {
        if (_repoMateria.agregarRegistro(nuevaMateria) > 0)
            cout << "\n\tMateria guardada correctamente.\n";
        else
            cout << "\n\tError al guardar la materia.\n";
    } else {
        cout << "\n\tOperación cancelada.\n";
    }
}

void MateriaManager::modificar() {
    //cin.ignore();
    cout << "\n\t=== Modificar Materia ===\n";
    int idMateria = Validacion::validarEnteroEnRango("\n\tID de Materia: ", 1, 10000);

    int posicion = _repoMateria.buscarRegistro(idMateria);
    if (posicion < 0) {
        cout << "\n\tNo se encontró la materia.\n";
        return;
    }

    Materia original = _repoMateria.leerRegistro(posicion);
    mostrar(original);
    cout << "\tToque una tecla para continuar";

    Materia modificada = ingresarDatos(original.getIdMateria());

    if (Validacion::desearGuardar("")) {
        if (_repoMateria.modificarRegistro(modificada, posicion))
            cout << "\n\tMateria modificada correctamente.\n";
        else
            cout << "\n\tError al modificar la materia.\n";
    } else {
        cout << "\n\tOperación cancelada.\n";
    }
}

void MateriaManager::cambiarEstado(bool activar) {
    string accion = activar ? "Activar" : "Borrar";
    cout << "\n\t=== " << accion << " Materia ===\n";

    int idMateria = Validacion::validarEnteroEnRango("\n\tID de Materia: ", 1, 10000);
    int posicion = _repoMateria.buscarRegistro(idMateria);

    if (posicion < 0) {
        cout << "\n\tNo se encontró la materia.\n";
        return;
    }

    Materia materia = _repoMateria.leerRegistro(posicion);
    mostrar(materia);

    bool estadoActual = materia.getEliminado();
    if ((activar && !estadoActual) || (!activar && estadoActual)) {
        cout << "\n\tLa materia ya está en ese estado.\n";
        return;
    }

    if (Validacion::desearGuardar("\n\t¿Confirmar operación? (s/n): ")) {
        bool exito = activar ? _repoMateria.activarRegistro(posicion)
                             : _repoMateria.bajaLogica(posicion);
        if (exito)
            cout << "\n\tOperación realizada correctamente.\n";
        else
            cout << "\n\tError al realizar la operación.\n";
    } else {
        cout << "\n\tOperación cancelada.\n";
    }
}

void MateriaManager::borrar() {
    cambiarEstado(false);
}

void MateriaManager::activar() {
    cambiarEstado(true);
}

void MateriaManager::listar() {
    bool incluirBorrados = Validacion::desearGuardar("\n\t¿Incluir materias eliminadas? (s/n): ");

    int total = _repoMateria.contarRegistros();
    if (total <= 0) {
        cout << "\n\tNo hay materias para mostrar.\n";
        return;
    }

    mostrarEncabezado();
    for (int i = 0; i < total; i++) {
        Materia mat = _repoMateria.leerRegistro(i);
        if (!incluirBorrados && mat.getEliminado()) continue;
        mostrarRegistro(mat);
    }
    mostrarPie();
}

void MateriaManager::mostrarEncabezado() const {
    cout << "\t+-----+----------+----------+--------------------------------+------------+----------+---------+" << endl;
    cout << "\t| ID  | Carrera  | Código   | Nombre                         | Cuatr.     | Estado   | Borrado |" << endl;
    cout << "\t+-----+----------+----------+--------------------------------+------------+----------+---------+" << endl;
}

void MateriaManager::mostrarRegistro(const Materia& mat) const {
    cout << "\t| " << setw(3)  << right << mat.getIdMateria()
         << " | " << setw(8)  << right << mat.getIdCarrera()
         << " | " << setw(8)  << left  << mat.getCodigo()
         << " | " << setw(30) << left  << mat.getNombre()
         << " | " << setw(10) << right << mat.getCuatrimestreSugerido()
         << " | " << setw(8)  << left  << mat.getEstado()
         << " | " << setw(7)  << right << (mat.getEliminado() ? "Si" : "No")
         << " |" << endl;
}

void MateriaManager::mostrarPie() const {
    cout << "\t+-----+----------+----------+--------------------------------+------------+----------+---------+" << endl;
}

void MateriaManager::mostrar(Materia materia) const {

    mostrarEncabezado();
    mostrarRegistro(materia);
    mostrarPie();
    cout << endl;

}
