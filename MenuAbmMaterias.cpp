#include "MenuAbmMaterias.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void MenuABMMaterias::mostrarMenuABMMaterias() {
    ManagerMateria manager;
    int op;

    do {
        system("cls");
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
  
        system("cls");

        switch (op) {
            case 1:
                manager.alta();
                break;
            case 2:
                manager.modificacion();
                break;
            case 3:
                manager.baja();
                break;
            case 4:
                manager.listarTodas();
                break;
            case 5:
                cout << "Funcionalidad opcional (Docente Titular)\n";
                break;
            case 6:
                cout << "Funcionalidad opcional (Correlativas)\n";
                break;
        }

        if (op != 0) system("pause");
    } while (op != 0);
}
