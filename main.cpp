#include <iostream>
using namespace std;

#include "Alumno_menu.h"
#include "Profesor_menu.h"
#include "Tesoreria_menu.h"

void menuPrincipal();

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    int op;
    do {
        cout << "\n===== SISTEMA ACADEMICO =====\n";
        cout << "1) Alumno\n";
        cout << "2) Profesor\n";
        cout << "3) Tesoreria\n";
        cout << "0) Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
            case 1:
                menuAlumno();
                break;
            case 2:
                menuProfesor();
                break;
            case 3:
                menuTesoreria();
                break;
            case 0:
                cout << "Chau!\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
        }
    } while (op != 0);
}
