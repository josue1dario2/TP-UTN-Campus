#include "MenuAbmMaterias.h"

#include <iostream>
#include <cstdlib>
#include <cstdlib>
using namespace std;

void MenuABMMaterias::mostrarMenuABMMaterias() {

    int op;
    do {
        system("cls");
        cout << endl;
        cout << "\n\tABM MATERIAS\n";
        cout << "\t--------------------------------\n";
        cout << "\t1) Alta de Materia\n";
        cout << "\t2) Modificar Materia\n";
        cout << "\t3) Baja lógica de Materia\n";
        cout << "\t4) Listar Materias\n";
        cout << "\t5) Asignar/Modificar Docente Titular (opcional)\n";
        cout << "\t6) Configurar Correlativas (opcional)\n";
        cout << "\t0) Volver\n";
        cout << "\t--------------------------------\n";
        cout << "\tOpción: ";
        cin >> op;
    } while (op != 0);

}
