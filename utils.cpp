#include <iostream>
#include <cstdlib>
#include <cstring>
#include <limits>
#include "utils.h"
#include "Validacion.h"
#include "ArchivoExamen.h"
#include "ArchivoMateria.h"
#include "ArchivoComision.h"
#include "ArchivoInscripcionComision.h"
#include "ManagerExamen.h"
#include "Examen.h"
#include "Materia.h"
#include "Comision.h"
#include "InscripcionComision.h"
using namespace std;

std::string cargarCadena()
{
  std::string texto;

  if(std::cin.peek() == '\n')
  {
    std::cin.ignore();
  }

  std::getline(std::cin, texto);

  return texto;
}

int buscarMaximo(int vec[], int cant){
  int indexMax = 0;
  
  for(int i=1; i<cant; i++){
    if(vec[i] > vec[indexMax]){
      indexMax = i;    
    }  
  }
  
  return indexMax;
}

void clearScreen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pauseScreen()
{
#ifdef _WIN32
  system("pause");
#else
  cout << "Presione ENTER para continuar...";
  if (cin.peek() == '\n') cin.ignore();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif
}

// ========================================================================
// FUNCIONES AUXILIARES PARA REPORTES Y ESTADÍSTICAS
// ========================================================================

float calcularPromedioAlumno(int legajo) {
    ArchivoExamen archivoExamenes("Examenes.dat");
    int total = archivoExamenes.contarRegistros();
    float suma = 0;
    int cant = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = archivoExamenes.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            ex.getNota() >= 4) {
            suma += ex.getNota();
            cant++;
        }
    }

    return (cant > 0) ? suma / cant : 0.0f;
}

int contarMateriasAprobadas(int legajo) {
    ArchivoMateria archivoMaterias("Materias.dat");
    ArchivoExamen archivoExamenes("Examenes.dat");
    int total = archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        // Buscar si tiene final aprobado
        int totalEx = archivoExamenes.contarRegistros();
        for (int j = 0; j < totalEx; j++) {
            Examen ex = archivoExamenes.leerRegistro(j);

            if (ex.getLegajoAlumno() == legajo &&
                ex.getIdMateria() == mat.getIdMateria() &&
                strcmp(ex.getTipo(), "Final") == 0 &&
                ex.getNota() >= 4) {
                count++;
                break;
            }
        }
    }

    return count;
}

int contarMateriasPromocionadas(int legajo) {
    ArchivoMateria archivoMaterias("Materias.dat");
    ArchivoComision archivoComisiones("Comisiones.dat");
    ManagerExamen managerExamen;
    int total = archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        // Obtener una comisión de la materia para verificar promoción
        int totalCom = archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                if (managerExamen.estaPromocionado(legajo, com.getIdComision())) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int contarMateriasRegulares(int legajo) {
    ArchivoMateria archivoMaterias("Materias.dat");
    ArchivoComision archivoComisiones("Comisiones.dat");
    ManagerExamen managerExamen;
    int total = archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        int totalCom = archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                if (managerExamen.estaRegular(legajo, com.getIdComision())) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int contarMateriasLibres(int legajo) {
    ArchivoMateria archivoMaterias("Materias.dat");
    ArchivoComision archivoComisiones("Comisiones.dat");
    ManagerExamen managerExamen;
    int total = archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        int totalCom = archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                if (managerExamen.estaLibre(legajo, com.getIdComision())) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int contarInscriptosEnComision(int idComision) {
    ArchivoInscripcionComision archivoInscripciones("InscripcionesComision.dat");
    int total = archivoInscripciones.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        InscripcionComision insc = archivoInscripciones.leerRegistro(i);

        if (insc.getIdComision() == idComision && insc.getEstado() == 0) {
            count++;
        }
    }

    return count;
}

