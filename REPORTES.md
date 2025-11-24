# 📊 Sistema de Reportes - ManagerReportes

Este documento explica cómo utilizar el sistema de reportes implementado en `ManagerReportes`.

---

## 📋 Tabla de Contenidos

1. [Cómo Usar los Reportes](#cómo-usar-los-reportes)
2. [Reportes de Alta Prioridad](#reportes-de-alta-prioridad)
3. [Reportes de Media Prioridad](#reportes-de-media-prioridad)
4. [Reportes de Baja Prioridad](#reportes-de-baja-prioridad)

---

## 🚀 Cómo Usar los Reportes

### Incluir en tu código

```cpp
#include "ManagerReportes.h"

// Crear instancia
ManagerReportes reportes;

// Llamar a los reportes
reportes.reporteRendimientoAcademico(1001);
```

### Ejemplo completo

```cpp
#include "ManagerReportes.h"
#include <iostream>

int main() {
    ManagerReportes reportes;

    // Generar reporte de un alumno específico
    reportes.reporteRendimientoAcademico(1001);

    // Listar alumnos de una comisión
    reportes.listadoAlumnosPorComision(101);

    // Ver estadísticas de una materia
    reportes.estadisticasPorMateria(5);

    return 0;
}
```

---

## 📈 Reportes de Alta Prioridad

### 1. Reporte de Rendimiento Académico por Alumno

**Método:** `reporteRendimientoAcademico(int legajo)`

**Descripción:** Muestra un resumen completo del rendimiento académico de un alumno.

**Ejemplo:**
```cpp
reportes.reporteRendimientoAcademico(1001);
```

**Salida:**
```
===============================================
  REPORTE DE RENDIMIENTO ACADEMICO
===============================================

Legajo: 1001
Nombre: Juan Pérez
-----------------------------------------------
Promedio General: 7.50
-----------------------------------------------
Materias Cursadas: 12/17
Materias Aprobadas: 8 (67%)
-----------------------------------------------
Materias Promocionadas: 5
Materias Regularizadas: 3
Materias Libres: 4
-----------------------------------------------
Estado: MUY BUENO
===============================================
```

---

### 2. Listado de Alumnos por Comisión

**Método:** `listadoAlumnosPorComision(int idComision)`

**Descripción:** Lista todos los alumnos inscriptos en una comisión específica.

**Ejemplo:**
```cpp
reportes.listadoAlumnosPorComision(101);
```

**Salida:**
```
===============================================
  LISTADO DE ALUMNOS POR COMISION
===============================================

Comision ID: 101
Materia: Programación II
Docente: Ing. Juan Pérez
Cuatrimestre: 2
-----------------------------------------------

Nro   Legajo    Nombre                        Estado
-----------------------------------------------
1     1001      Juan Martínez                 Activo
2     1002      María López                   Activo
3     1003      Pedro García                  Pendiente baja
-----------------------------------------------
Total de alumnos: 28
===============================================
```

---

### 3. Estadísticas por Materia

**Método:** `estadisticasPorMateria(int idMateria)`

**Descripción:** Muestra estadísticas completas de rendimiento en una materia.

**Ejemplo:**
```cpp
reportes.estadisticasPorMateria(5);
```

**Salida:**
```
===============================================
  ESTADISTICAS POR MATERIA
===============================================

Materia: Programación II
Cuatrimestre: 2
-----------------------------------------------

Inscriptos: 45 alumnos
-----------------------------------------------
Promocionados: 12 (27%)
Regulares: 18 (40%)
Libres: 15 (33%)
-----------------------------------------------
Promedio de la materia: 5.8
Tasa de aprobacion: 67%
===============================================
```

---

### 4. Finales Pendientes por Alumno

**Método:** `finalesPendientesPorAlumno(int legajo)`

**Descripción:** Lista todas las materias con final pendiente para un alumno.

**Ejemplo:**
```cpp
reportes.finalesPendientesPorAlumno(1001);
```

**Salida:**
```
===============================================
  FINALES PENDIENTES
===============================================

Legajo: 1001
Nombre: Juan Pérez
-----------------------------------------------

1. Programación II
   Condicion: REGULAR
   Cuatrimestre: 2

2. Base de Datos I
   Condicion: REGULAR
   Cuatrimestre: 2

-----------------------------------------------
Total de finales pendientes: 2
===============================================
```

---

### 5. Reporte de Comisiones por Cupo

**Método:** `reporteComisionesPorCupo()`

**Descripción:** Muestra el estado de ocupación de todas las comisiones.

**Ejemplo:**
```cpp
reportes.reporteComisionesPorCupo();
```

**Salida:**
```
===============================================
  REPORTE DE COMISIONES POR CUPO
===============================================

ID      Materia                       Cupo    Inscr.    %       Estado
-----------------------------------------------------------------------
101     Programación II               30      28        93%     Casi llena
102     Programación II               30      12        40%     Disponible
103     Base de Datos I               30      30        100%    LLENA
===============================================
```

**Nota:** El cupo estándar es de 30 alumnos por comisión.

---

## 📊 Reportes de Media Prioridad

### 6. Ranking de Alumnos por Promedio

**Método:** `rankingAlumnosPorPromedio()`

**Descripción:** Muestra el top 20 de alumnos ordenados por promedio general.

**Ejemplo:**
```cpp
reportes.rankingAlumnosPorPromedio();
```

**Salida:**
```
===============================================
  RANKING DE ALUMNOS POR PROMEDIO
===============================================

Pos   Legajo    Nombre                           Promedio
---------------------------------------------------------------
1     1005      María López                      9.20
2     1002      Pedro García                     8.70
3     1001      Juan Pérez                       7.50
...
---------------------------------------------------------------
Total de alumnos rankeados: 45
===============================================
```

---

### 7. Calendario de Finales

**Método:** `calendarioFinales()`

**Descripción:** Muestra cuántos alumnos regulares y promocionados hay por materia.

**Ejemplo:**
```cpp
reportes.calendarioFinales();
```

**Salida:**
```
===============================================
  CALENDARIO DE FINALES
===============================================

ID Mat  Materia                            Regulares   Promocionados
-----------------------------------------------------------------------
1       Programación I                     15          8
2       Programación II                    23          5
5       Base de Datos I                    18          10
-----------------------------------------------------------------------
Total de finales a rendir: 56
Total de alumnos promocionados: 23
===============================================
```

---

### 8. Historial de Notas por Materia

**Método:** `historialNotasPorMateria(int legajo, int idMateria)`

**Descripción:** Muestra el historial completo de notas de un alumno en una materia específica.

**Ejemplo:**
```cpp
reportes.historialNotasPorMateria(1001, 5);
```

**Salida:**
```
===============================================
  HISTORIAL DE NOTAS POR MATERIA
===============================================

Alumno: Juan Pérez (Legajo: 1001)
Materia: Programación II
-----------------------------------------------

Parcial 1: 3 (Desaprobado)
Recuperatorio P1: 7 (Aprobado)
Parcial 2: 8 (Aprobado)
-----------------------------------------------
Promedio: 7.5
Condicion: REGULAR (uso recuperatorio)

Final: Pendiente
===============================================
```

---

### 9. Alumnos en Riesgo Académico

**Método:** `alumnosEnRiesgoAcademico()`

**Descripción:** Lista alumnos con bajo rendimiento que necesitan apoyo.

**Criterios de Riesgo:**
- Más del 50% de materias libres
- Promedio menor a 4

**Ejemplo:**
```cpp
reportes.alumnosEnRiesgoAcademico();
```

**Salida:**
```
===============================================
  ALUMNOS EN RIESGO ACADEMICO
===============================================

-----------------------------------------------
Legajo: 1010 - Ana Martínez
Materias libres: 5/8 (62%)
Promedio: 3.20
-----------------------------------------------
Legajo: 1015 - Carlos Gómez
Materias libres: 6/10 (60%)
Promedio: 3.80
===============================================
Total de alumnos en riesgo: 2
===============================================
```

---

### 10. Carga Horaria de Docentes

**Método:** `cargaHorariaDocentes()`

**Descripción:** Muestra la cantidad de comisiones y alumnos asignados a cada docente.

**Ejemplo:**
```cpp
reportes.cargaHorariaDocentes();
```

**Salida:**
```
===============================================
  CARGA HORARIA DE DOCENTES
===============================================

Legajo    Nombre                        Comisiones  Alumnos
---------------------------------------------------------------
5001      Ing. Juan Pérez               2           56
5002      Lic. María González           3           78
5003      Dr. Pedro López               1           28
===============================================
```

---

## 📉 Reportes de Baja Prioridad (Analíticos)

### 11. Tasa de Aprobación por Cuatrimestre

**Método:** `tasaAprobacionPorCuatrimestre()`

**Descripción:** Analiza la tasa global de aprobación.

**Nota:** Este reporte muestra estadísticas globales ya que el sistema actual no almacena información temporal detallada por cuatrimestre.

**Ejemplo:**
```cpp
reportes.tasaAprobacionPorCuatrimestre();
```

**Salida:**
```
===============================================
  TASA DE APROBACION POR CUATRIMESTRE
===============================================

Este reporte requiere datos historicos por cuatrimestre.
Actualmente el sistema no almacena suficiente informacion
temporal para generar este analisis completo.

--- ESTADISTICAS GLOBALES ---

Promocionados: 25.5%
Regulares: 42.3%
Libres: 32.2%
===============================================
```

---

### 12. Materias con Mayor Índice de Libre

**Método:** `materiasConMayorIndiceLibre()`

**Descripción:** Identifica las materias con mayor porcentaje de alumnos libres (top 10).

**Ejemplo:**
```cpp
reportes.materiasConMayorIndiceLibre();
```

**Salida:**
```
===============================================
  MATERIAS CON MAYOR INDICE DE LIBRE
===============================================

Pos     Materia                            Libres      Total       %
-----------------------------------------------------------------------
1       Matemática                         25          45          55.0%
2       Base de Datos II                   21          44          48.0%
3       Programación IV                    18          43          42.0%
...
===============================================
```

**Utilidad:** Permite identificar materias problemáticas que requieren intervención pedagógica.

---

### 13. Tiempo Promedio de Carrera

**Método:** `tiempoPromedioCarrera()`

**Descripción:** Analiza el avance promedio de los alumnos en la carrera.

**Nota:** Este reporte muestra análisis de avance ya que el sistema actual no almacena fechas de ingreso/egreso.

**Ejemplo:**
```cpp
reportes.tiempoPromedioCarrera();
```

**Salida:**
```
===============================================
  TIEMPO PROMEDIO DE CARRERA
===============================================

Este reporte requiere datos de fecha de ingreso y egreso
de los alumnos que no estan completamente implementados
en el sistema actual.

--- ANALISIS DE AVANCE ---

Total de materias en el plan: 17
Promedio de materias aprobadas por alumno: 8.5
Porcentaje de avance promedio: 50.0%
===============================================
```

---

## 💡 Casos de Uso Comunes

### Caso 1: Seguimiento Individual de Alumno

```cpp
ManagerReportes reportes;

// Ver rendimiento general
reportes.reporteRendimientoAcademico(1001);

// Ver finales pendientes
reportes.finalesPendientesPorAlumno(1001);

// Ver historial en una materia específica
reportes.historialNotasPorMateria(1001, 5);
```

### Caso 2: Análisis de Materia

```cpp
ManagerReportes reportes;

// Ver estadísticas generales
reportes.estadisticasPorMateria(5);

// Ver inscriptos en comisiones
reportes.listadoAlumnosPorComision(101);
reportes.listadoAlumnosPorComision(102);
```

### Caso 3: Gestión Institucional

```cpp
ManagerReportes reportes;

// Ver ranking de alumnos
reportes.rankingAlumnosPorPromedio();

// Identificar alumnos en riesgo
reportes.alumnosEnRiesgoAcademico();

// Análisis de materias problemáticas
reportes.materiasConMayorIndiceLibre();

// Distribución de carga docente
reportes.cargaHorariaDocentes();
```

### Caso 4: Planificación de Finales

```cpp
ManagerReportes reportes;

// Ver calendario general
reportes.calendarioFinales();

// Verificar finales pendientes de alumnos específicos
reportes.finalesPendientesPorAlumno(1001);
reportes.finalesPendientesPorAlumno(1002);
```

---

## 🔧 Notas Técnicas

### Dependencias

Los reportes utilizan las siguientes clases:
- `ArchivoAlumno`
- `ArchivoMateria`
- `ArchivoComision`
- `ArchivoInscripcionComision`
- `ArchivoExamen`
- `ArchivoDocente`
- `ManagerExamen`

### Archivos de Datos Requeridos

Asegúrate de tener los siguientes archivos `.dat`:
- `Alumnos.dat`
- `Materias.dat`
- `Comisiones.dat`
- `InscripcionesComision.dat`
- `Examenes.dat`
- `Docentes.dat`

### Inicializar Datos de Prueba

Si necesitas datos de prueba, ejecuta el inicializador:

```bash
./build/inicializar_datos
```

Esto creará la carrera, materias y correlativas del plan de estudios.

---

## 🚀 Próximas Mejoras

Los siguientes reportes pueden mejorarse con más información temporal:
- Tasa de aprobación histórica por cuatrimestre
- Tiempo real de carrera (ingreso hasta egreso)
- Tendencias de rendimiento a lo largo del tiempo

---

## 📞 Soporte

Para cualquier consulta sobre los reportes, consulta el código fuente en:
- `ManagerReportes.h`
- `ManagerReportes.cpp`
