#include "ArchivoMateria.h"
#include "ArchivoCorrelativa.h"
#include "ArchivoCarrera.h"
#include "ArchivoAlumno.h"
#include "ArchivoDocente.h"
#include "Alumno.h"
#include "Docente.h"
#include "Fecha.h"
#include "Direccion.h"
#include <iostream>
#include <cstring>

using namespace std;

void inicializar() {
    cout << "\n=== INICIALIZADOR DE DATOS - TECNICATURA ===\n\n";

    // 1. Crear carrera
    ArchivoCarrera archCarrera("Carreras.dat");
    Carrera carrera(1, "Tecnicatura Universitaria en Programacion", 4, false);
    if (archCarrera.agregarRegistro(carrera)) {
        cout << "[OK] Carrera creada: Tecnicatura Universitaria en Programacion\n";
    }

    // 2. Crear todas las materias
    ArchivoMateria archMateria("Materias.dat");

    struct MateriaInfo {
        int id;
        const char* nombre;
        int cuatrimestre;
    };

    MateriaInfo materias[] = {
        // NIVEL I
        {1, "Programacion I", 1},
        {2, "Arquitectura y Sistemas Operativos", 1},
        {3, "Matematica", 1},
        {4, "Organizacion Empresarial", 1},
        {5, "Programacion II", 2},
        {6, "Probabilidad y Estadistica", 2},
        {7, "Base de Datos I", 2},
        {8, "Ingles I", 2},
        // NIVEL II
        {9, "Programacion III", 3},
        {10, "Base de Datos II", 3},
        {11, "Metodologia de Sistemas I", 3},
        {12, "Ingles II", 3},
        {13, "Programacion IV", 4},
        {14, "Metodologia de Sistemas II", 4},
        {15, "Introduccion al Analisis de Datos", 4},
        {16, "Legislacion", 4},
        {17, "Gestion de Desarrollo de Software", 4}
    };

    cout << "\nCreando materias...\n";
    for (int i = 0; i < 17; i++) {
        Materia mat(materias[i].id, 1, materias[i].nombre,
                    materias[i].cuatrimestre, "Activa", false);
        if (archMateria.agregarRegistro(mat)) {
            cout << "  [OK] " << materias[i].id << ". " << materias[i].nombre << "\n";
        }
    }

    // 3. Crear correlativas
    ArchivoCorrelativa archCorr("Correlativas.dat");

    struct CorrelativaInfo {
        int materiaObjetivo;
        int materiaRequisito;
    };

    CorrelativaInfo correlativas[] = {
        // Materia 5: Programación II
        {5, 1},  // req: Programación I
        {5, 2},  // req: Arquitectura y SO

        // Materia 6: Probabilidad y Estadística
        {6, 3},  // req: Matemática

        // Materia 7: Base de Datos I
        {7, 1},  // req: Programación I
        {7, 3},  // req: Matemática

        // Materia 9: Programación III
        {9, 5},  // req: Programación II
        {9, 7},  // req: Base de Datos I

        // Materia 10: Base de Datos II
        {10, 7}, // req: Base de Datos I

        // Materia 11: Metodología de Sistemas I
        {11, 5}, // req: Programación II
        {11, 7}, // req: Base de Datos I
        {11, 4}, // req: Organización Empresarial

        // Materia 12: Inglés II
        {12, 8}, // req: Inglés I

        // Materia 13: Programación IV
        {13, 9},  // req: Programación III
        {13, 10}, // req: Base de Datos II
        {13, 11}, // req: Metodología de Sistemas I

        // Materia 14: Metodología de Sistemas II
        {14, 11}, // req: Metodología de Sistemas I

        // Materia 15: Introducción al Análisis de Datos
        {15, 10}, // req: Base de Datos II
        {15, 6},  // req: Probabilidad y Estadística
        {15, 7},  // req: Base de Datos I

        // Materia 16: Legislación
        {16, 7},  // req: Base de Datos I
        {16, 4},  // req: Organización Empresarial

        // Materia 17: Gestión de Desarrollo de Software
        {17, 9},  // req: Programación III
        {17, 10}  // req: Base de Datos II
    };

    cout << "\nCreando correlativas...\n";
    int numCorrelativas = sizeof(correlativas) / sizeof(CorrelativaInfo);
    for (int i = 0; i < numCorrelativas; i++) {
        Correlativa corr(correlativas[i].materiaObjetivo,
                        correlativas[i].materiaRequisito);
        if (archCorr.agregarRegistro(corr)) {
            cout << "  [OK] Materia " << correlativas[i].materiaObjetivo
                 << " requiere Materia " << correlativas[i].materiaRequisito << "\n";
        }
    }

    // 4. Crear alumnos de prueba
    ArchivoAlumno archAlumno("Alumnos.dat");
    cout << "\nCreando alumnos de prueba...\n";

    Fecha fechaNac1(15, 3, 2000);
    Fecha fechaIng1(1, 3, 2023);
    Direccion dir1("Av. San Martin", "Mendoza", "Mendoza", 1234, 5500);

    Alumno alu1(1, 35556725, "Josue", "Solis", "5492613849535",
                "josue1dario@gmail.com", dir1, fechaNac1, fechaIng1, false);
    if (archAlumno.agregarRegistro(alu1)) {
        cout << "  [OK] Alumno creado: Josue Solis (Legajo: 1)\n";
    }

    Fecha fechaNac2(20, 7, 2001);
    Fecha fechaIng2(1, 3, 2023);
    Direccion dir2("Calle Belgrano", "Mendoza", "Mendoza", 567, 5500);

    Alumno alu2(1001, 40123456, "Juan", "Martinez", "2614567890",
                "juan.martinez@alumno.utn.edu.ar", dir2, fechaNac2, fechaIng2, false);
    if (archAlumno.agregarRegistro(alu2)) {
        cout << "  [OK] Alumno creado: Juan Martinez (Legajo: 1001)\n";
    }

    Fecha fechaNac3(10, 5, 2002);
    Fecha fechaIng3(1, 3, 2024);
    Direccion dir3("Calle Mitre", "Mendoza", "Mendoza", 890, 5500);

    Alumno alu3(1002, 41234567, "Maria", "Lopez", "2615678901",
                "maria.lopez@alumno.utn.edu.ar", dir3, fechaNac3, fechaIng3, false);
    if (archAlumno.agregarRegistro(alu3)) {
        cout << "  [OK] Alumno creado: Maria Lopez (Legajo: 1002)\n";
    }

    // 5. Crear docentes de prueba
    ArchivoDocente archDocente("Docentes.dat");
    cout << "\nCreando docentes de prueba...\n";

    Fecha fechaNacDoc1(10, 5, 1975);
    Fecha fechaIngDoc1(1, 3, 2010);
    Direccion dirDoc1("Av. Las Heras", "Mendoza", "Mendoza", 2345, 5500);

    Docente doc1(5001, 25123456, "Carlos", "Gomez", "2614111222",
                 "carlos.gomez@utn.edu.ar", dirDoc1, fechaNacDoc1, fechaIngDoc1, false);
    if (archDocente.agregarRegistro(doc1)) {
        cout << "  [OK] Docente creado: Carlos Gomez (Legajo: 5001)\n";
    }

    Fecha fechaNacDoc2(15, 8, 1980);
    Fecha fechaIngDoc2(1, 3, 2012);
    Direccion dirDoc2("Calle Godoy Cruz", "Mendoza", "Mendoza", 456, 5500);

    Docente doc2(5002, 28234567, "Ana", "Rodriguez", "2614222333",
                 "ana.rodriguez@utn.edu.ar", dirDoc2, fechaNacDoc2, fechaIngDoc2, false);
    if (archDocente.agregarRegistro(doc2)) {
        cout << "  [OK] Docente creado: Ana Rodriguez (Legajo: 5002)\n";
    }

    cout << "\n=========================================\n";
    cout << "INICIALIZACION COMPLETADA\n";
    cout << "=========================================\n";
    cout << "- Carrera: 1\n";
    cout << "- Materias: 17\n";
    cout << "- Correlativas: " << numCorrelativas << "\n";
    cout << "- Alumnos: 3\n";
    cout << "- Docentes: 2\n";
    cout << "=========================================\n";
    cout << "\nLEGAJOS CREADOS:\n";
    cout << "Alumnos:\n";
    cout << "  - Legajo 1: Josue Solis\n";
    cout << "  - Legajo 1001: Juan Martinez\n";
    cout << "  - Legajo 1002: Maria Lopez\n";
    cout << "\nDocentes:\n";
    cout << "  - Legajo 5001: Carlos Gomez\n";
    cout << "  - Legajo 5002: Ana Rodriguez\n";
    cout << "=========================================\n\n";

    return;
}
