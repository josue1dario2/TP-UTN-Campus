#include "ManagerReportes.h"
#include "Alumno.h"
#include "Materia.h"
#include "Comision.h"
#include "Docente.h"
#include "Examen.h"
#include "InscripcionComision.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

ManagerReportes::ManagerReportes()
    : _archivoAlumnos("Alumnos.dat"),
      _archivoMaterias("Materias.dat"),
      _archivoComisiones("Comisiones.dat"),
      _archivoInscripciones("InscripcionesComision.dat"),
      _archivoExamenes("Examenes.dat"),
      _archivoDocentes("Docentes.dat")
{}

// ========================================================================
// FUNCIONES AUXILIARES PRIVADAS
// ========================================================================

float ManagerReportes::calcularPromedioAlumno(int legajo) {
    int total = _archivoExamenes.contarRegistros();
    float suma = 0;
    int cant = 0;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamenes.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo &&
            strcmp(ex.getTipo(), "Final") == 0 &&
            ex.getNota() >= 4) {
            suma += ex.getNota();
            cant++;
        }
    }

    return (cant > 0) ? suma / cant : 0.0f;
}

int ManagerReportes::contarMateriasAprobadas(int legajo) {
    int total = _archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        // Buscar si tiene final aprobado
        int totalEx = _archivoExamenes.contarRegistros();
        for (int j = 0; j < totalEx; j++) {
            Examen ex = _archivoExamenes.leerRegistro(j);

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

int ManagerReportes::contarMateriasPromocionadas(int legajo) {
    int total = _archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        // Obtener una comisión de la materia para verificar promoción
        int totalCom = _archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                if (_managerExamen.estaPromocionado(legajo, com.getIdComision())) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int ManagerReportes::contarMateriasRegulares(int legajo) {
    int total = _archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        int totalCom = _archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                if (_managerExamen.estaRegular(legajo, com.getIdComision())) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int ManagerReportes::contarMateriasLibres(int legajo) {
    int total = _archivoMaterias.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        int totalCom = _archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                if (_managerExamen.estaLibre(legajo, com.getIdComision())) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int ManagerReportes::contarInscriptosEnComision(int idComision) {
    int total = _archivoInscripciones.contarRegistros();
    int count = 0;

    for (int i = 0; i < total; i++) {
        InscripcionComision insc = _archivoInscripciones.leerRegistro(i);

        if (insc.getIdComision() == idComision && insc.getEstado() == 0) {
            count++;
        }
    }

    return count;
}

// ========================================================================
// REPORTES DE ALTA PRIORIDAD
// ========================================================================

void ManagerReportes::reporteRendimientoAcademico(int legajo) {
    cout << "\n===============================================\n";
    cout << "  REPORTE DE RENDIMIENTO ACADEMICO\n";
    cout << "===============================================\n";

    // Buscar alumno
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos < 0) {
        cout << "\nERROR: Alumno no encontrado.\n";
        return;
    }

    Alumno alu = _archivoAlumnos.leerRegistro(pos);

    cout << "\nLegajo: " << alu.getLegajo() << endl;
    cout << "Nombre: " << alu.getNombre() << " " << alu.getApellido() << endl;
    cout << "-----------------------------------------------\n";

    // Calcular estadísticas
    float promedio = calcularPromedioAlumno(legajo);
    int aprobadas = contarMateriasAprobadas(legajo);
    int promocionadas = contarMateriasPromocionadas(legajo);
    int regulares = contarMateriasRegulares(legajo);
    int libres = contarMateriasLibres(legajo);
    int totalMaterias = _archivoMaterias.contarRegistros();
    int cursadas = promocionadas + regulares + libres;

    cout << fixed << setprecision(2);
    cout << "Promedio General: " << promedio << endl;
    cout << "-----------------------------------------------\n";
    cout << "Materias Cursadas: " << cursadas << "/" << totalMaterias << endl;
    cout << "Materias Aprobadas: " << aprobadas << " ("
         << (cursadas > 0 ? (aprobadas * 100 / cursadas) : 0) << "%)" << endl;
    cout << "-----------------------------------------------\n";
    cout << "Materias Promocionadas: " << promocionadas << endl;
    cout << "Materias Regularizadas: " << regulares << endl;
    cout << "Materias Libres: " << libres << endl;
    cout << "-----------------------------------------------\n";

    // Estado general
    if (libres > cursadas / 2) {
        cout << "Estado: EN RIESGO ACADEMICO\n";
    } else if (promedio >= 7) {
        cout << "Estado: EXCELENTE\n";
    } else if (promedio >= 6) {
        cout << "Estado: MUY BUENO\n";
    } else {
        cout << "Estado: REGULAR\n";
    }

    cout << "===============================================\n";
}

void ManagerReportes::listadoAlumnosPorComision(int idComision) {
    cout << "\n===============================================\n";
    cout << "  LISTADO DE ALUMNOS POR COMISION\n";
    cout << "===============================================\n";

    // Buscar comisión
    int posCom = _archivoComisiones.buscarRegistro(idComision);
    if (posCom < 0) {
        cout << "\nERROR: Comision no encontrada.\n";
        return;
    }

    Comision com = _archivoComisiones.leerRegistro(posCom);

    // Buscar materia
    int posMat = _archivoMaterias.buscarRegistro(com.getIdMateria());
    Materia mat = _archivoMaterias.leerRegistro(posMat);

    // Buscar docente
    int posDoc = _archivoDocentes.buscarRegistro(com.getLegajoDocente());
    Docente doc = _archivoDocentes.leerRegistro(posDoc);

    cout << "\nComision ID: " << com.getIdComision() << endl;
    cout << "Materia: " << mat.getNombre() << endl;
    cout << "Docente: " << doc.getNombre() << " " << doc.getApellido() << endl;
    cout << "Cuatrimestre: " << com.getCuatrimestre() << endl;
    cout << "-----------------------------------------------\n\n";

    // Listar alumnos
    int total = _archivoInscripciones.contarRegistros();
    int contador = 0;

    cout << left << setw(5) << "Nro"
         << setw(10) << "Legajo"
         << setw(30) << "Nombre"
         << setw(15) << "Estado" << endl;
    cout << "-----------------------------------------------\n";

    for (int i = 0; i < total; i++) {
        InscripcionComision insc = _archivoInscripciones.leerRegistro(i);

        if (insc.getIdComision() == idComision) {
            int posAlu = _archivoAlumnos.buscarRegistro(insc.getLegajoAlumno());
            if (posAlu >= 0) {
                Alumno alu = _archivoAlumnos.leerRegistro(posAlu);
                contador++;

                string estado;
                if (insc.getEstado() == 0) estado = "Activo";
                else if (insc.getEstado() == 1) estado = "Pendiente baja";
                else estado = "Baja";

                cout << left << setw(5) << contador
                     << setw(10) << alu.getLegajo()
                     << setw(30) << (string(alu.getNombre()) + " " + string(alu.getApellido()))
                     << setw(15) << estado << endl;
            }
        }
    }

    cout << "-----------------------------------------------\n";
    cout << "Total de alumnos: " << contador << endl;
    cout << "===============================================\n";
}

void ManagerReportes::estadisticasPorMateria(int idMateria) {
    cout << "\n===============================================\n";
    cout << "  ESTADISTICAS POR MATERIA\n";
    cout << "===============================================\n";

    // Buscar materia
    int posMat = _archivoMaterias.buscarRegistro(idMateria);
    if (posMat < 0) {
        cout << "\nERROR: Materia no encontrada.\n";
        return;
    }

    Materia mat = _archivoMaterias.leerRegistro(posMat);

    cout << "\nMateria: " << mat.getNombre() << endl;
    cout << "Cuatrimestre: " << mat.getCuatrimestre() << endl;
    cout << "-----------------------------------------------\n";

    // Contar alumnos por estado
    int totalInscriptos = 0;
    int promocionados = 0;
    int regulares = 0;
    int libres = 0;
    float sumaNotas = 0;
    int cantNotas = 0;

    // Obtener comisiones de esta materia
    int totalCom = _archivoComisiones.contarRegistros();

    for (int i = 0; i < totalCom; i++) {
        Comision com = _archivoComisiones.leerRegistro(i);

        if (com.getIdMateria() == idMateria) {
            // Buscar inscripciones en esta comisión
            int totalInsc = _archivoInscripciones.contarRegistros();

            for (int j = 0; j < totalInsc; j++) {
                InscripcionComision insc = _archivoInscripciones.leerRegistro(j);

                if (insc.getIdComision() == com.getIdComision() && insc.getEstado() == 0) {
                    totalInscriptos++;
                    int legajo = insc.getLegajoAlumno();

                    if (_managerExamen.estaPromocionado(legajo, com.getIdComision())) {
                        promocionados++;
                    } else if (_managerExamen.estaRegular(legajo, com.getIdComision())) {
                        regulares++;
                    } else {
                        libres++;
                    }

                    // Calcular promedio de parciales
                    float prom = _managerExamen.promedioConReglas(legajo, idMateria);
                    if (prom > 0) {
                        sumaNotas += prom;
                        cantNotas++;
                    }
                }
            }
        }
    }

    cout << fixed << setprecision(1);
    cout << "\nInscriptos: " << totalInscriptos << " alumnos" << endl;
    cout << "-----------------------------------------------\n";
    cout << "Promocionados: " << promocionados
         << " (" << (totalInscriptos > 0 ? (promocionados * 100 / totalInscriptos) : 0) << "%)" << endl;
    cout << "Regulares: " << regulares
         << " (" << (totalInscriptos > 0 ? (regulares * 100 / totalInscriptos) : 0) << "%)" << endl;
    cout << "Libres: " << libres
         << " (" << (totalInscriptos > 0 ? (libres * 100 / totalInscriptos) : 0) << "%)" << endl;
    cout << "-----------------------------------------------\n";

    float promedioMateria = (cantNotas > 0) ? sumaNotas / cantNotas : 0;
    int tasaAprobacion = (totalInscriptos > 0) ? ((promocionados + regulares) * 100 / totalInscriptos) : 0;

    cout << "Promedio de la materia: " << promedioMateria << endl;
    cout << "Tasa de aprobacion: " << tasaAprobacion << "%" << endl;
    cout << "===============================================\n";
}

void ManagerReportes::finalesPendientesPorAlumno(int legajo) {
    cout << "\n===============================================\n";
    cout << "  FINALES PENDIENTES\n";
    cout << "===============================================\n";

    // Buscar alumno
    int pos = _archivoAlumnos.buscarRegistro(legajo);
    if (pos < 0) {
        cout << "\nERROR: Alumno no encontrado.\n";
        return;
    }

    Alumno alu = _archivoAlumnos.leerRegistro(pos);

    cout << "\nLegajo: " << alu.getLegajo() << endl;
    cout << "Nombre: " << alu.getNombre() << " " << alu.getApellido() << endl;
    cout << "-----------------------------------------------\n\n";

    int contador = 0;
    int totalMat = _archivoMaterias.contarRegistros();

    for (int i = 0; i < totalMat; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        // Buscar una comisión de la materia
        int totalCom = _archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                // Verificar si está regular (sin final aprobado)
                if (_managerExamen.estaRegular(legajo, com.getIdComision())) {
                    // Verificar que no tenga final aprobado
                    int totalEx = _archivoExamenes.contarRegistros();
                    bool tieneFinalAprobado = false;

                    for (int k = 0; k < totalEx; k++) {
                        Examen ex = _archivoExamenes.leerRegistro(k);

                        if (ex.getLegajoAlumno() == legajo &&
                            ex.getIdMateria() == mat.getIdMateria() &&
                            strcmp(ex.getTipo(), "Final") == 0 &&
                            ex.getNota() >= 4) {
                            tieneFinalAprobado = true;
                            break;
                        }
                    }

                    if (!tieneFinalAprobado) {
                        contador++;
                        cout << contador << ". " << mat.getNombre() << endl;
                        cout << "   Condicion: REGULAR" << endl;
                        cout << "   Cuatrimestre: " << mat.getCuatrimestre() << endl;
                        cout << endl;
                    }
                }
                break;
            }
        }
    }

    cout << "-----------------------------------------------\n";
    cout << "Total de finales pendientes: " << contador << endl;
    cout << "===============================================\n";
}

void ManagerReportes::reporteComisionesPorCupo() {
    cout << "\n===============================================\n";
    cout << "  REPORTE DE COMISIONES POR CUPO\n";
    cout << "===============================================\n\n";

    int totalCom = _archivoComisiones.contarRegistros();

    cout << left << setw(8) << "ID"
         << setw(30) << "Materia"
         << setw(8) << "Cupo"
         << setw(10) << "Inscr."
         << setw(8) << "%"
         << setw(15) << "Estado" << endl;
    cout << "-----------------------------------------------------------------------\n";

    for (int i = 0; i < totalCom; i++) {
        Comision com = _archivoComisiones.leerRegistro(i);

        if (com.getEliminado()) continue;

        // Buscar materia
        int posMat = _archivoMaterias.buscarRegistro(com.getIdMateria());
        Materia mat = _archivoMaterias.leerRegistro(posMat);

        // Contar inscriptos
        int inscriptos = contarInscriptosEnComision(com.getIdComision());
        int cupo = 30; // Cupo estándar por comisión
        int porcentaje = (cupo > 0) ? (inscriptos * 100 / cupo) : 0;

        string estado;
        if (inscriptos >= cupo) estado = "LLENA";
        else if (porcentaje >= 80) estado = "Casi llena";
        else if (porcentaje >= 50) estado = "Media";
        else estado = "Disponible";

        cout << left << setw(8) << com.getIdComision()
             << setw(30) << mat.getNombre()
             << setw(8) << cupo
             << setw(10) << inscriptos
             << setw(8) << (to_string(porcentaje) + "%")
             << setw(15) << estado << endl;
    }

    cout << "===============================================\n";
}

// ========================================================================
// REPORTES DE MEDIA PRIORIDAD
// ========================================================================

void ManagerReportes::rankingAlumnosPorPromedio() {
    cout << "\n===============================================\n";
    cout << "  RANKING DE ALUMNOS POR PROMEDIO\n";
    cout << "===============================================\n\n";

    // Estructura para almacenar datos de alumnos
    struct AlumnoPromedio {
        int legajo;
        string nombre;
        float promedio;
    };

    vector<AlumnoPromedio> alumnos;

    // Recopilar datos
    int total = _archivoAlumnos.contarRegistros();
    for (int i = 0; i < total; i++) {
        Alumno alu = _archivoAlumnos.leerRegistro(i);

        if (alu.getEliminado()) continue;

        float prom = calcularPromedioAlumno(alu.getLegajo());
        if (prom > 0) {
            AlumnoPromedio ap;
            ap.legajo = alu.getLegajo();
            ap.nombre = string(alu.getNombre()) + " " + string(alu.getApellido());
            ap.promedio = prom;
            alumnos.push_back(ap);
        }
    }

    // Ordenar por promedio descendente
    sort(alumnos.begin(), alumnos.end(),
         [](const AlumnoPromedio& a, const AlumnoPromedio& b) {
             return a.promedio > b.promedio;
         });

    // Mostrar ranking
    cout << fixed << setprecision(2);
    cout << left << setw(5) << "Pos"
         << setw(10) << "Legajo"
         << setw(35) << "Nombre"
         << setw(10) << "Promedio" << endl;
    cout << "---------------------------------------------------------------\n";

    for (size_t i = 0; i < alumnos.size() && i < 20; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(10) << alumnos[i].legajo
             << setw(35) << alumnos[i].nombre
             << setw(10) << alumnos[i].promedio << endl;
    }

    cout << "---------------------------------------------------------------\n";
    cout << "Total de alumnos rankeados: " << alumnos.size() << endl;
    cout << "===============================================\n";
}

void ManagerReportes::calendarioFinales() {
    cout << "\n===============================================\n";
    cout << "  CALENDARIO DE FINALES\n";
    cout << "===============================================\n\n";

    int totalMat = _archivoMaterias.contarRegistros();

    cout << left << setw(8) << "ID Mat"
         << setw(35) << "Materia"
         << setw(12) << "Regulares"
         << setw(15) << "Promocionados" << endl;
    cout << "-----------------------------------------------------------------------\n";

    int totalRegulares = 0;
    int totalPromocionados = 0;

    for (int i = 0; i < totalMat; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        int regulares = 0;
        int promocionados = 0;

        // Contar alumnos por estado
        int totalAlu = _archivoAlumnos.contarRegistros();

        for (int j = 0; j < totalAlu; j++) {
            Alumno alu = _archivoAlumnos.leerRegistro(j);

            if (alu.getEliminado()) continue;

            // Buscar una comisión de la materia
            int totalCom = _archivoComisiones.contarRegistros();
            for (int k = 0; k < totalCom; k++) {
                Comision com = _archivoComisiones.leerRegistro(k);

                if (com.getIdMateria() == mat.getIdMateria()) {
                    if (_managerExamen.estaPromocionado(alu.getLegajo(), com.getIdComision())) {
                        promocionados++;
                    } else if (_managerExamen.estaRegular(alu.getLegajo(), com.getIdComision())) {
                        // Verificar que no tenga final aprobado
                        int totalEx = _archivoExamenes.contarRegistros();
                        bool tieneFinal = false;

                        for (int m = 0; m < totalEx; m++) {
                            Examen ex = _archivoExamenes.leerRegistro(m);

                            if (ex.getLegajoAlumno() == alu.getLegajo() &&
                                ex.getIdMateria() == mat.getIdMateria() &&
                                strcmp(ex.getTipo(), "Final") == 0 &&
                                ex.getNota() >= 4) {
                                tieneFinal = true;
                                break;
                            }
                        }

                        if (!tieneFinal) {
                            regulares++;
                        }
                    }
                    break;
                }
            }
        }

        if (regulares > 0 || promocionados > 0) {
            cout << left << setw(8) << mat.getIdMateria()
                 << setw(35) << mat.getNombre()
                 << setw(12) << regulares
                 << setw(15) << promocionados << endl;

            totalRegulares += regulares;
            totalPromocionados += promocionados;
        }
    }

    cout << "-----------------------------------------------------------------------\n";
    cout << "Total de finales a rendir: " << totalRegulares << endl;
    cout << "Total de alumnos promocionados: " << totalPromocionados << endl;
    cout << "===============================================\n";
}

void ManagerReportes::historialNotasPorMateria(int legajo, int idMateria) {
    cout << "\n===============================================\n";
    cout << "  HISTORIAL DE NOTAS POR MATERIA\n";
    cout << "===============================================\n";

    // Buscar alumno
    int posAlu = _archivoAlumnos.buscarRegistro(legajo);
    if (posAlu < 0) {
        cout << "\nERROR: Alumno no encontrado.\n";
        return;
    }

    Alumno alu = _archivoAlumnos.leerRegistro(posAlu);

    // Buscar materia
    int posMat = _archivoMaterias.buscarRegistro(idMateria);
    if (posMat < 0) {
        cout << "\nERROR: Materia no encontrada.\n";
        return;
    }

    Materia mat = _archivoMaterias.leerRegistro(posMat);

    cout << "\nAlumno: " << alu.getNombre() << " " << alu.getApellido() << " (Legajo: " << legajo << ")" << endl;
    cout << "Materia: " << mat.getNombre() << endl;
    cout << "-----------------------------------------------\n\n";

    // Buscar exámenes
    int total = _archivoExamenes.contarRegistros();
    bool encontro = false;

    int notaP1 = -1, notaP2 = -1;
    int recuP1 = -1, recuP2 = -1;
    int notaFinal = -1;

    for (int i = 0; i < total; i++) {
        Examen ex = _archivoExamenes.leerRegistro(i);

        if (ex.getLegajoAlumno() == legajo && ex.getIdMateria() == idMateria) {
            encontro = true;

            if (strcmp(ex.getTipo(), "Parcial") == 0) {
                if (ex.getNumeroParcial() == 1) notaP1 = ex.getNota();
                else if (ex.getNumeroParcial() == 2) notaP2 = ex.getNota();
            } else if (strcmp(ex.getTipo(), "Recuperatorio") == 0) {
                if (ex.getNumeroParcial() == 1) recuP1 = ex.getNota();
                else if (ex.getNumeroParcial() == 2) recuP2 = ex.getNota();
            } else if (strcmp(ex.getTipo(), "Final") == 0) {
                notaFinal = ex.getNota();
            }
        }
    }

    if (!encontro) {
        cout << "No hay exámenes registrados para esta materia.\n";
        return;
    }

    // Mostrar historial
    if (notaP1 >= 0) {
        cout << "Parcial 1: " << notaP1;
        if (notaP1 >= 4) cout << " (Aprobado)";
        else cout << " (Desaprobado)";
        cout << endl;
    }

    if (recuP1 >= 0) {
        cout << "Recuperatorio P1: " << recuP1;
        if (recuP1 >= 4) cout << " (Aprobado)";
        else cout << " (Desaprobado)";
        cout << endl;
    }

    if (notaP2 >= 0) {
        cout << "Parcial 2: " << notaP2;
        if (notaP2 >= 4) cout << " (Aprobado)";
        else cout << " (Desaprobado)";
        cout << endl;
    }

    if (recuP2 >= 0) {
        cout << "Recuperatorio P2: " << recuP2;
        if (recuP2 >= 4) cout << " (Aprobado)";
        else cout << " (Desaprobado)";
        cout << endl;
    }

    cout << "-----------------------------------------------\n";

    // Calcular condición
    int n1 = (recuP1 >= 0) ? recuP1 : notaP1;
    int n2 = (recuP2 >= 0) ? recuP2 : notaP2;

    if (n1 >= 0 && n2 >= 0) {
        float promedio = (n1 + n2) / 2.0f;
        cout << fixed << setprecision(1);
        cout << "Promedio: " << promedio << endl;

        if (recuP1 >= 0 || recuP2 >= 0) {
            cout << "Condicion: REGULAR (uso recuperatorio)" << endl;
        } else if (promedio >= 7) {
            cout << "Condicion: PROMOCIONADO" << endl;
        } else if (promedio >= 4) {
            cout << "Condicion: REGULAR" << endl;
        } else {
            cout << "Condicion: LIBRE" << endl;
        }
    }

    if (notaFinal >= 0) {
        cout << "\nFinal: " << notaFinal;
        if (notaFinal >= 4) cout << " (APROBADO)";
        else cout << " (Desaprobado)";
        cout << endl;
    } else {
        cout << "\nFinal: Pendiente" << endl;
    }

    cout << "===============================================\n";
}

void ManagerReportes::alumnosEnRiesgoAcademico() {
    cout << "\n===============================================\n";
    cout << "  ALUMNOS EN RIESGO ACADEMICO\n";
    cout << "===============================================\n\n";

    int total = _archivoAlumnos.contarRegistros();
    int contador = 0;

    for (int i = 0; i < total; i++) {
        Alumno alu = _archivoAlumnos.leerRegistro(i);

        if (alu.getEliminado()) continue;

        int libres = contarMateriasLibres(alu.getLegajo());
        float promedio = calcularPromedioAlumno(alu.getLegajo());
        int cursadas = contarMateriasPromocionadas(alu.getLegajo()) +
                      contarMateriasRegulares(alu.getLegajo()) +
                      libres;

        // Criterio de riesgo: más del 50% libres o promedio < 4
        if ((cursadas > 0 && libres > cursadas / 2) || promedio < 4) {
            contador++;
            cout << "-----------------------------------------------\n";
            cout << "Legajo: " << alu.getLegajo() << " - " << alu.getNombre() << " " << alu.getApellido() << endl;
            cout << "Materias libres: " << libres << "/" << cursadas;
            if (cursadas > 0) {
                cout << " (" << (libres * 100 / cursadas) << "%)";
            }
            cout << endl;
            cout << fixed << setprecision(2);
            cout << "Promedio: " << promedio << endl;
        }
    }

    cout << "===============================================\n";
    cout << "Total de alumnos en riesgo: " << contador << endl;
    cout << "===============================================\n";
}

void ManagerReportes::cargaHorariaDocentes() {
    cout << "\n===============================================\n";
    cout << "  CARGA HORARIA DE DOCENTES\n";
    cout << "===============================================\n\n";

    int totalDoc = _archivoDocentes.contarRegistros();

    cout << left << setw(10) << "Legajo"
         << setw(30) << "Nombre"
         << setw(15) << "Comisiones"
         << setw(10) << "Alumnos" << endl;
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < totalDoc; i++) {
        Docente doc = _archivoDocentes.leerRegistro(i);

        if (doc.getEliminado()) continue;

        // Contar comisiones y alumnos
        int comisiones = 0;
        int totalAlumnos = 0;

        int totalCom = _archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getLegajoDocente() == doc.getLegajo() && !com.getEliminado()) {
                comisiones++;
                totalAlumnos += contarInscriptosEnComision(com.getIdComision());
            }
        }

        if (comisiones > 0) {
            cout << left << setw(10) << doc.getLegajo()
                 << setw(30) << (string(doc.getNombre()) + " " + string(doc.getApellido()))
                 << setw(15) << comisiones
                 << setw(10) << totalAlumnos << endl;
        }
    }

    cout << "===============================================\n";
}

// ========================================================================
// REPORTES DE BAJA PRIORIDAD (ANALÍTICOS)
// ========================================================================

void ManagerReportes::tasaAprobacionPorCuatrimestre() {
    cout << "\n===============================================\n";
    cout << "  TASA DE APROBACION POR CUATRIMESTRE\n";
    cout << "===============================================\n\n";

    // Nota: Este reporte necesitaría información de fechas y cuatrimestres
    // que no está completamente implementada en el sistema actual

    cout << "Este reporte requiere datos historicos por cuatrimestre." << endl;
    cout << "Actualmente el sistema no almacena suficiente informacion" << endl;
    cout << "temporal para generar este analisis completo." << endl;

    cout << "\n--- ESTADISTICAS GLOBALES ---\n\n";

    int totalAlumnos = 0;
    int promocionados = 0;
    int regulares = 0;
    int libres = 0;

    int total = _archivoAlumnos.contarRegistros();
    for (int i = 0; i < total; i++) {
        Alumno alu = _archivoAlumnos.leerRegistro(i);

        if (alu.getEliminado()) continue;

        int p = contarMateriasPromocionadas(alu.getLegajo());
        int r = contarMateriasRegulares(alu.getLegajo());
        int l = contarMateriasLibres(alu.getLegajo());

        if (p + r + l > 0) {
            totalAlumnos++;
            promocionados += p;
            regulares += r;
            libres += l;
        }
    }

    int totalMaterias = promocionados + regulares + libres;

    cout << fixed << setprecision(1);
    cout << "Promocionados: " << (totalMaterias > 0 ? (promocionados * 100.0 / totalMaterias) : 0) << "%" << endl;
    cout << "Regulares: " << (totalMaterias > 0 ? (regulares * 100.0 / totalMaterias) : 0) << "%" << endl;
    cout << "Libres: " << (totalMaterias > 0 ? (libres * 100.0 / totalMaterias) : 0) << "%" << endl;

    cout << "===============================================\n";
}

void ManagerReportes::materiasConMayorIndiceLibre() {
    cout << "\n===============================================\n";
    cout << "  MATERIAS CON MAYOR INDICE DE LIBRE\n";
    cout << "===============================================\n\n";

    struct MateriaEstadistica {
        int idMateria;
        string nombre;
        int totalAlumnos;
        int libres;
        float porcentaje;
    };

    vector<MateriaEstadistica> materias;

    int totalMat = _archivoMaterias.contarRegistros();

    for (int i = 0; i < totalMat; i++) {
        Materia mat = _archivoMaterias.leerRegistro(i);

        if (mat.getEliminado()) continue;

        int totalAlumnos = 0;
        int libres = 0;

        // Buscar comisiones de esta materia
        int totalCom = _archivoComisiones.contarRegistros();

        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getIdMateria() == mat.getIdMateria()) {
                // Contar inscriptos
                int totalInsc = _archivoInscripciones.contarRegistros();

                for (int k = 0; k < totalInsc; k++) {
                    InscripcionComision insc = _archivoInscripciones.leerRegistro(k);

                    if (insc.getIdComision() == com.getIdComision() && insc.getEstado() == 0) {
                        totalAlumnos++;
                        if (_managerExamen.estaLibre(insc.getLegajoAlumno(), com.getIdComision())) {
                            libres++;
                        }
                    }
                }
            }
        }

        if (totalAlumnos > 0) {
            MateriaEstadistica me;
            me.idMateria = mat.getIdMateria();
            me.nombre = string(mat.getNombre());
            me.totalAlumnos = totalAlumnos;
            me.libres = libres;
            me.porcentaje = (libres * 100.0f / totalAlumnos);
            materias.push_back(me);
        }
    }

    // Ordenar por porcentaje de libres descendente
    sort(materias.begin(), materias.end(),
         [](const MateriaEstadistica& a, const MateriaEstadistica& b) {
             return a.porcentaje > b.porcentaje;
         });

    // Mostrar top 10
    cout << fixed << setprecision(1);
    cout << left << setw(8) << "Pos"
         << setw(35) << "Materia"
         << setw(12) << "Libres"
         << setw(12) << "Total"
         << setw(10) << "%" << endl;
    cout << "-----------------------------------------------------------------------\n";

    for (size_t i = 0; i < materias.size() && i < 10; i++) {
        cout << left << setw(8) << (i + 1)
             << setw(35) << materias[i].nombre
             << setw(12) << materias[i].libres
             << setw(12) << materias[i].totalAlumnos
             << setw(10) << materias[i].porcentaje << "%" << endl;
    }

    cout << "===============================================\n";
}

void ManagerReportes::tiempoPromedioCarrera() {
    cout << "\n===============================================\n";
    cout << "  TIEMPO PROMEDIO DE CARRERA\n";
    cout << "===============================================\n\n";

    cout << "Este reporte requiere datos de fecha de ingreso y egreso" << endl;
    cout << "de los alumnos que no estan completamente implementados" << endl;
    cout << "en el sistema actual." << endl;

    cout << "\n--- ANALISIS DE AVANCE ---\n\n";

    int totalMaterias = _archivoMaterias.contarRegistros();
    int totalAlumnos = 0;
    int sumaAprobadas = 0;

    int total = _archivoAlumnos.contarRegistros();
    for (int i = 0; i < total; i++) {
        Alumno alu = _archivoAlumnos.leerRegistro(i);

        if (alu.getEliminado()) continue;

        int aprobadas = contarMateriasAprobadas(alu.getLegajo());
        if (aprobadas > 0) {
            totalAlumnos++;
            sumaAprobadas += aprobadas;
        }
    }

    cout << fixed << setprecision(1);
    cout << "Total de materias en el plan: " << totalMaterias << endl;
    cout << "Promedio de materias aprobadas por alumno: "
         << (totalAlumnos > 0 ? (sumaAprobadas * 1.0 / totalAlumnos) : 0) << endl;
    cout << "Porcentaje de avance promedio: "
         << (totalAlumnos > 0 && totalMaterias > 0 ?
             (sumaAprobadas * 100.0 / (totalAlumnos * totalMaterias)) : 0) << "%" << endl;

    cout << "===============================================\n";
}
