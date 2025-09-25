#include <iostream>
#include "Carrera.h"
//#include "Fecha.h"
using namespace std;

// --- Programa de prueba ---
int main() {
    Carrera c1;
    c1.cargar();
    cout << "\nMostrando datos de la carrera:\n";
    c1.mostrar();

    return 0;
}
