#include "ArchivoAlumno.h"
#include "AlumnoAdmin.h"
#include "Alumno.h"
#include "Validacion.h"
#include "ManagerAlumno.h"
#include "utils.h"
#include <iostream>

using namespace std;

MenuABMAlumnosAdmin::MenuABMAlumnosAdmin()
    : _cantidadOpciones(6)
{
}

void MenuABMAlumnosAdmin::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMAlumnosAdmin::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRACIÓN DE ALUMNOS\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Alumno\n";
    cout << "\t2) Modificar Alumno\n";
    cout << "\t3) Baja Lógica de Alumno\n";
    cout << "\t4) Activar Alumno\n";
    cout << "\t5) Buscar Alumno por Legajo\n";
    cout << "\t6) Listar Alumnos\n";
    cout << "\t0) Volver\n";
}

void MenuABMAlumnosAdmin::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            _alumnoManager.registrarAlumno();
            break;
        case 2:
            _alumnoManager.modificarAlumno();
            break;
        case 3:
            bajaLogicaAlumno();
            break;
        case 4:
            activarAlumno();
            break;
        case 5:
            buscarAlumnoLegajo();
            break;

        case 6:
            listarAlumnos();
            break;

        case 0:
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}

void MenuABMAlumnosAdmin::listarAlumnos(){
    bool incluirBorrados = Validacion::desearAccionar("\n\t¿Incluir alumnos eliminados? (s/n): ");
    //cout << endl << incluirBorrados;
    _alumnoManager.listarAlumnos(incluirBorrados);

}

int MenuABMAlumnosAdmin::pedirLegajoAlumno(const std::string& mensaje, ArchivoAlumno _archivoAlumno){
    int legajo,pos;

    cout << "\n\t=== " << mensaje << " ===\n";
    //cout << "\n\t  Ingrese 0 para salir\n"<< endl;
    legajo = Validacion::validarEnteroEnRango("\tIngrese el numero de Legajo: ", 1000, 150000);
    pos = _archivoAlumno.buscarRegistro(legajo);
    return pos;
}

int MenuABMAlumnosAdmin::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";
    //if(cin.peek() == '\n') cin.ignore();
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);

    return opcion;
}


void MenuABMAlumnosAdmin::bajaLogicaAlumno(){
    int pos;
    //int legajo;
    clearScreen();
    string mensaje ="Baja Logica del alumno";
    ArchivoAlumno _archivoAlumno("Alumnos.dat");
    do {
        pos = pedirLegajoAlumno(mensaje, _archivoAlumno);
        if (pos <0) {
            cout << "\n\t No se encontró ese legajo.\n\t";
            if (Validacion::desearAccionar("Desea salir? s/n? ")){
                return;
            }
            pauseScreen();
            clearScreen();
        }

    } while (pos <= 0);

    Alumno _alumnoBuscado =_archivoAlumno.leerRegistro(pos);
    cout << endl;
    _alumnoBuscado.mostrar();
    if (Validacion::desearAccionar("\n\t--Desea realizar la baja logica? s/n: ")){
        if (_archivoAlumno.bajaLogica(pos)){
                cout << "\tAlumno dado de baja correctamente.\n";
        }else {
            cout << "\tError al dar de baja.\n";
        }
    }
    pauseScreen();

    }

void MenuABMAlumnosAdmin::buscarAlumnoLegajo(){
    int pos;
    //int legajo;
    clearScreen();
    string mensaje ="Buscar alumno por legajo";

    ArchivoAlumno _archivoAlumno("Alumnos.dat");
    do {
        pos = pedirLegajoAlumno(mensaje, _archivoAlumno);
        if (pos <0) {
            cout << "\n\t No se encontró ese legajo.\n\t Vuelva a intentar\n";
            pauseScreen();
            clearScreen();
        }
        cout << pos << endl;

    } while (pos < 0);

    Alumno _alumnoBuscado =_archivoAlumno.leerRegistro(pos);
    cout << endl;
    _alumnoBuscado.mostrar();

    pauseScreen();
    }






void MenuABMAlumnosAdmin::activarAlumno()
{
    int pos;
    //int legajo;
    clearScreen();
    string mensaje ="Alta Logica del alumno";
    ArchivoAlumno _archivoAlumno("Alumnos.dat");
    do {
        pos = pedirLegajoAlumno(mensaje, _archivoAlumno);
        if (pos <0) {
            cout << "\n\t No se encontró ese legajo.\n\t";
            if (Validacion::desearAccionar("Desea salir? s/n? ")){
                return;
            }
            pauseScreen();
            clearScreen();
        }

    } while (pos < 0);

    Alumno _alumnoBuscado =_archivoAlumno.leerRegistro(pos);
    cout << endl;
    _alumnoBuscado.mostrar();
    if (Validacion::desearAccionar("\n\t--Desea realizar el alta logica? s/n: ")){
        if (_archivoAlumno.activarRegistro(pos)){
                cout << "\tAlumno Activado correctamente.\n";
        }else {
            cout << "\tError al dar de baja.\n";
        }
    }
    pauseScreen();

    }



