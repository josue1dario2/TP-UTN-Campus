#include "DocenteAdmin.h"
#include "Docente.h"
#include "Validacion.h"
#include "utils.h"
#include <iostream>

using namespace std;

MenuABMDocentesAdmin::MenuABMDocentesAdmin()
    : _cantidadOpciones(6)
{
}

void MenuABMDocentesAdmin::mostrar() {
    int opcion;
    do {
        clearScreen();
        opcion = seleccionOpcion();
        clearScreen();
        ejecutarOpcion(opcion);
        pauseScreen();
    } while (opcion != 0);
}

void MenuABMDocentesAdmin::mostrarOpciones()
{
    cout << endl;
    cout << "\n\tMENÚ ADMINISTRACIÓN DE DOCENTES\n";
    cout << "\t--------------------------------\n";
    cout << "\t1) Alta de Docente\n";
    cout << "\t2) Modificar Docente\n";
    cout << "\t3) Baja Lógica de Docente\n";
    cout << "\t4) Activar Docente\n";
    cout << "\t5) Buscar Docente\n";
    cout << "\t6) Listar Docentes\n";
    cout << "\t0) Volver\n";
}

void MenuABMDocentesAdmin::ejecutarOpcion(int opcion)
{
    switch (opcion) {
        case 1:
            altaDocente();
            break;
        case 2:
            modificarDocente();
            break;
        case 3:
            bajaLogicaDocente();
            break;
        case 4:
            activarDocente();
            break;
        case 5:
            buscarDocente();
            break;
        case 6:
            listarDocentes();
            break;
        case 0:
            break;
        default:
            cout << "Opción inválida.\n";
            break;
    }
}

int MenuABMDocentesAdmin::seleccionOpcion()
{
    int opcion;
    mostrarOpciones();
    cout << "\t--------------------------------\n";
    cout << "\tOpción: ";
    //if(cin.peek() == '\n') cin.ignore();
    opcion = Validacion::validarEnteroEnRango("", 0, _cantidadOpciones);

    return opcion;
}

void MenuABMDocentesAdmin::altaDocente()
{
    Docente _nuevoDocente;
    _nuevoDocente.cargar();

    int resultadoLegajo = _archivoDocentes.buscarRegistro(_nuevoDocente.getLegajo());
    int resultadoDni = _archivoDocentes.buscarRegistroPorDni(_nuevoDocente.getDni());

    if (resultadoLegajo == -1 || resultadoDni == -1) {
        cout << "\n\tError al acceder al archivo de docentes.\n";
        return;
    }

    if (_nuevoDocente.getFechaNacimiento() >= _nuevoDocente.getFechaIngreso()){
        cout << "\n\tHay un problema con las fechas.";
        return;
    }

    if (resultadoLegajo >= 0 || resultadoDni >= 0) { // encontrado en posición válida
        string mensaje ="\n\tYa existe un docente con ese ";
        if (resultadoLegajo >= 0 && resultadoDni >= 0) {
            cout << mensaje << "legajo/dni.\n";
            return;
        }
        string resultado = (resultadoLegajo >= 0) ? "legajo.\n" : "dni.\n";
        cout << mensaje << resultado;
        return;
    }

    // resultado == -2, no existe, se puede agregar
    if (_archivoDocentes.agregarRegistro(_nuevoDocente)) {
        cout << "\n\tDocente registrado correctamente.\n";
    } else {
        cout << "\n\tError al guardar el docente.\n";
    }

}

void MenuABMDocentesAdmin::modificarDocente()
{
    cout << "\n\t=== MODIFICAR DOCENTE ===\n";
    cout << "\n\tSeleccione modo de búsqueda:\n";
    cout << "\t1) Por Legajo\n";
    cout << "\t2) Por DNI\n";
    cout << "\t0) Cancelar\n";
    int modo = Validacion::validarEnteroEnRango("\n\tOpción: ", 0, 2);
    if (modo !=0) {

        int pos = -1;
        int legajo = 0;
        int dni = 0;

        if (modo == 1) {
            legajo = Validacion::validarEnteroEnRango("\tIngrese Legajo: ", 1, 100000000);
            pos = _archivoDocentes.buscarRegistro(legajo);
            if (pos < 0) { // -1 error / -2 no encontrado
                cout << "\tNo se encontró un docente con ese legajo.\n";
                return;
            }
        } else {
            dni = Validacion::validarEnteroEnRango("\tIngrese DNI: ", 1, 100000000);
            pos = _archivoDocentes.buscarRegistroPorDni(dni);
            if (pos < 0) {
                cout << "\tNo se encontró un docente con ese DNI.\n";
                return;
            }
        }

        Docente original = _archivoDocentes.leerRegistro(pos);
        cout << "\n\tRegistro actual:\n\n";
        original.mostrar();
        if (Validacion::desearAccionar("\tDesea modificar los datos de este docente? s/n ")){

            cout << "\tIngrese nuevos datos (se solicitarán todos los campos)\n";
            Docente actualizado;
            actualizado.cargar();

            int posNuevoLegajo = _archivoDocentes.buscarRegistro(actualizado.getLegajo());
            if (posNuevoLegajo >= 0 && posNuevoLegajo != pos) {
                cout << "\n\tEl legajo ingresado ya está asignado a otro docente. Operación cancelada.\n";
                return;
            }
            int posNuevoDNI = _archivoDocentes.buscarRegistroPorDni(actualizado.getDni());
            if (posNuevoDNI >= 0 && posNuevoDNI != pos) {
                cout << "\n\tEl DNI ingresado ya está asignado a otro docente. Operación cancelada.\n";
                return;
            }

            if (actualizado.getFechaNacimiento() >= actualizado.getFechaIngreso()){
                cout << "\n\tHay un problema con las fechas.";
                return;

            }



            actualizado.setEliminado(original.getEliminado());
            if (Validacion::desearAccionar("")){
                if (_archivoDocentes.modificarRegistro(actualizado, pos)) {
                cout << "\n\tDocente modificado correctamente.\n";
                } else {
                cout << "\n\tError al modificar el docente.\n";
                }
            }

        }
    }
}



int MenuABMDocentesAdmin::pedirLegajoDocente(const string& mensaje, ArchivoDocente _archivoDocentes){
    int legajo,pos;
    cout << "\n\t=== " << mensaje << " ===\n";
    //cout << "\n\t  Ingrese 0 para salir\n"<< endl;
    legajo = Validacion::validarEnteroEnRango("\tIngrese el numero de Legajo: ", 1000, 150000);
    pos = _archivoDocentes.buscarRegistro(legajo);
    return pos;
}


void MenuABMDocentesAdmin::bajaLogicaDocente()
{
    int pos;
    clearScreen();
    string mensaje ="Baja Logica de docente";

    ArchivoDocente _archivoDocentes;

    do {
        pos = pedirLegajoDocente(mensaje, _archivoDocentes);
        if (pos <0) {
            cout << "\n\t No se encontró ese legajo.\n\t";
            if (Validacion::desearAccionar("Desea salir? s/n? ")){
                return;
            }
            pauseScreen();
            clearScreen();
        }

    } while (pos < 0);

    Docente _docenteBuscado = _archivoDocentes.leerRegistro(pos);

    cout << endl;
    _docenteBuscado.mostrar();
    if (Validacion::desearAccionar("\n\t--Desea realizar la baja logica? s/n: ")){
        if (_archivoDocentes.bajaLogica(pos)){
                cout << "\tDocente dado de baja correctamente.\n";
        }else {
            cout << "\tError al dar de baja.\n";
        }
    }
    pauseScreen();

}

void MenuABMDocentesAdmin::activarDocente()
{
    int pos;
    clearScreen();
    string mensaje ="Alta Logica de docente";

    ArchivoDocente _archivoDocentes;

    do {
        pos = pedirLegajoDocente(mensaje, _archivoDocentes);
        if (pos <0) {
            cout << "\n\t No se encontró ese legajo.\n\t";
            if (Validacion::desearAccionar("Desea salir? s/n? ")){
                return;
            }
            pauseScreen();
            clearScreen();
        }

    } while (pos < 0);

    Docente _docenteBuscado = _archivoDocentes.leerRegistro(pos);

    cout << endl;
    _docenteBuscado.mostrar();
    if (Validacion::desearAccionar("\n\t--Desea activar el docente? s/n: ")){
        if (_archivoDocentes.activarRegistro(pos)){

                cout << "\tDocente activado correctamente.\n";
        }else {
            cout << "\tError al activar docente.\n";
        }
    }
    pauseScreen();
}


void MenuABMDocentesAdmin::buscarDocente()
{
    cout << "\n\t=== BUSCAR DOCENTE ===\n";
    cout << "\n\tSeleccione modo de búsqueda:\n";
    cout << "\t1) Por Legajo\n";
    cout << "\t2) Por DNI\n";
    cout << "\t0) Cancelar\n";
    int modo = Validacion::validarEnteroEnRango("\n\tOpción: ", 0, 2);
    if (!modo ==0) {

        int pos = -1;
        int legajo = 0;
        int dni = 0;

        if (modo == 1) {
            legajo = Validacion::validarEnteroEnRango("\tIngrese Legajo: ", 1, 100000000);
            pos = _archivoDocentes.buscarRegistro(legajo);
            if (pos < 0) { // -1 error / -2 no encontrado
                cout << "\tNo se encontró un docente con ese legajo.\n";
                return;
            }
        } else {
            dni = Validacion::validarEnteroEnRango("\tIngrese DNI: ", 1, 100000000);
            pos = _archivoDocentes.buscarRegistroPorDni(dni);
            if (pos < 0) {
                cout << "\tNo se encontró un docente con ese DNI.\n";
                return;
            }
        }

        Docente original = _archivoDocentes.leerRegistro(pos);
        cout << "\n\tRegistro actual:\n";
        original.mostrar();
    }

}
void MenuABMDocentesAdmin::listarDocentes()
{
    bool incluirBorrados = Validacion::desearAccionar("\n\t¿Incluir alumnos eliminados? (s/n): ");
    _managerDocente.listarDocentes(incluirBorrados);

}
