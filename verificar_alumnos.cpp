#include "ArchivoAlumno.h"
#include "Alumno.h"
#include <iostream>
using namespace std;

int main() {
    ArchivoAlumno arch("Alumnos.dat");

    cout << "\n=== VERIFICACIÓN DE ALUMNOS EN ARCHIVO ===\n\n";
    cout << "Total de registros: " << arch.contarRegistros() << "\n\n";

    for (int i = 0; i < arch.contarRegistros(); i++) {
        Alumno alu = arch.leerRegistro(i);
        cout << "Posición " << i << ":\n";
        alu.mostrar();
        cout << "\n";
    }

    cout << "\n=== PRUEBA DE BÚSQUEDA ===\n\n";

    int legajoBuscar = 1;
    int pos = arch.buscarRegistro(legajoBuscar);
    cout << "Búsqueda de legajo " << legajoBuscar << ": posición = " << pos << "\n";

    if (pos >= 0) {
        Alumno alu = arch.leerRegistro(pos);
        alu.mostrar();
    }

    return 0;
}
