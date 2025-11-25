# 🎓 Sistema de Gestión Universitaria - Campus UTN

Sistema completo de gestión académica para instituciones universitarias desarrollado en C++20. Permite administrar alumnos, docentes, materias, comisiones, exámenes y generar reportes estadísticos detallados.

---

## 📋 Tabla de Contenidos

- [Características Principales](#-características-principales)
- [Arquitectura del Sistema](#-arquitectura-del-sistema)
- [Reglas de Negocio](#-reglas-de-negocio)
- [Archivos de Datos (.dat)](#-archivos-de-datos-dat)
- [Módulos del Sistema](#-módulos-del-sistema)
- [Compilación y Ejecución](#-compilación-y-ejecución)
- [Uso del Sistema](#-uso-del-sistema)
- [Sistema de Reportes](#-sistema-de-reportes)
- [Estructura de Archivos](#-estructura-de-archivos)

---

## ✨ Características Principales

### 🎯 Gestión Completa
- **Alumnos**: Alta, baja, modificación y consulta
- **Docentes**: Administración de profesores y carga horaria
- **Materias**: Plan de estudios con correlativas
- **Comisiones**: Grupos de cursada con cupos
- **Exámenes**: Parciales, recuperatorios y finales
- **Inscripciones**: Control de inscripciones y bajas

### 📊 Sistema de Reportes (13 reportes)
- Rendimiento académico por alumno
- Estadísticas por materia
- Ranking de alumnos
- Finales pendientes
- Alumnos en riesgo
- Y 8 reportes más...

### 🔒 Control de Acceso
- Perfiles diferenciados: Alumno, Docente, Administrador
- Validación de credenciales con 3 intentos
- Permisos específicos por rol

### 💾 Persistencia de Datos
- Archivos binarios (.dat) para almacenamiento
- Backup y restauración completa
- Exportación a CSV
- Inicializador de datos de prueba

---

## 🏗️ Arquitectura del Sistema

### Patrón de Diseño

El sistema utiliza el patrón **Repository** con capas de abstracción:

```
┌─────────────────────────────────────┐
│         Capa de Presentación        │
│  (Menús: MenuAlumno, MenuAdmin...)  │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│       Capa de Lógica de Negocio     │
│  (Managers: ManagerAlumno, Manager  │
│   Examen, ManagerReportes...)       │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│      Capa de Acceso a Datos         │
│  (Archivos: ArchivoAlumno, Archivo  │
│   Examen, ArchivoMateria...)        │
└──────────────┬──────────────────────┘
               │
┌──────────────▼──────────────────────┐
│        Capa de Persistencia         │
│  (Archivos .dat en disco)           │
└─────────────────────────────────────┘
```

### Clases Principales

```cpp
// Entidades del Dominio
- Alumno, Docente, Persona (herencia)
- Materia, Comision, Carrera
- Examen, InscripcionComision
- Correlativa, Fecha, Direccion

// Archivos (Persistencia)
- ArchivoAlumno, ArchivoDocente
- ArchivoMateria, ArchivoComision
- ArchivoExamen, ArchivoInscripcionComision
- ArchivoCorrelativa, ArchivoCarrera

// Managers (Lógica de Negocio)
- ManagerAlumno, ManagerDocente
- ManagerExamen, ManagerReportes
- ManagerComision, ManagerMateria
- ManagerCorrelativa, ManagerInscripcionComision

// Menús (Presentación)
- MenuPrincipal, MenuAdmin
- MenuAlumno, MenuDocente
- MenuAbmExamen, MenuReportes
- MenuDatosCSV, MenuUtilitarios
```

---

## 📜 Reglas de Negocio

### 1. Sistema de Exámenes

#### 1.1 Parciales
- **Cantidad**: Se toman 2 parciales por materia
- **Aprobación**: Nota >= 4 (escala 0-10)
- **Validación**: Solo se pueden cargar si el alumno está inscrito en la comisión

#### 1.2 Recuperatorios
- **Disponibilidad**: Solo para parciales desaprobados (nota < 4)
- **Cantidad**: 1 recuperatorio por parcial
- **Regla Crítica**: El recuperatorio REEMPLAZA la nota del parcial original

#### 1.3 Condición Académica

##### **PROMOCIONADO**
```
Condiciones:
✅ Tener ambos parciales rendidos
✅ NO haber usado recuperatorio
✅ Promedio >= 7

Consecuencia:
→ Aprueba la materia sin rendir final
→ NO puede inscribirse a final (ya aprobó)
```

**Ejemplo:**
- Parcial 1: 8, Parcial 2: 7 → Promedio: 7.5 → **PROMOCIONADO** ✅

##### **REGULAR**
```
Condiciones:
✅ Tener ambos parciales rendidos
✅ Promedio >= 4
✅ NO estar promocionado

Casos:
1. Promedio >= 4 y < 7 sin recuperatorio
2. Cualquier promedio >= 4 CON recuperatorio

Consecuencia:
→ Debe rendir final para aprobar
→ Puede inscribirse a mesa de examen
```

**Ejemplos:**
- P1: 6, P2: 5 → Promedio: 5.5 → **REGULAR** ✅
- P1: 3, RecuP1: 9, P2: 8 → Promedio: 8.5 → **REGULAR** ✅ (usó recuperatorio)

##### **LIBRE**
```
Condiciones:
❌ No tiene ambos parciales rendidos
❌ O promedio < 4

Consecuencia:
→ NO puede rendir final
→ Debe volver a cursar la materia
```

**Ejemplos:**
- P1: 3, P2: 2 → Promedio: 2.5 → **LIBRE** ❌
- Solo rindió P1 → **LIBRE** ❌

### 2. Sistema de Finales

#### 2.1 Requisitos para Rendir Final
```
Validaciones obligatorias:
1. ✅ Estar inscrito en la comisión
2. ✅ Estar REGULAR (no libre, no promocionado)
3. ✅ Cumplir correlativas de la materia
4. ✅ No tener final aprobado anteriormente
```

#### 2.2 Casos Especiales
```
❌ Alumno PROMOCIONADO intenta rendir final
   → ERROR: "Está PROMOCIONADO. No necesita rendir final"

❌ Alumno LIBRE intenta rendir final
   → ERROR: "Está LIBRE. Debe cursar y regularizar primero"

❌ Alumno NO inscrito intenta rendir
   → ERROR: "NO está inscrito en esta comisión"
```

### 3. Sistema de Correlativas

#### 3.1 Reglas de Cursada
```
Para CURSAR una materia:
✅ Debe tener APROBADAS (final >= 4) las materias correlativas
✅ No puede estar ya aprobada
```

#### 3.2 Ejemplo del Plan de Estudios

```
Programación II (ID: 5)
  Requiere:
  - Programación I (ID: 1) → APROBADA
  - Arquitectura y Sistemas Operativos (ID: 2) → APROBADA

Base de Datos II (ID: 10)
  Requiere:
  - Base de Datos I (ID: 7) → APROBADA
```

### 4. Sistema de Inscripciones

#### 4.1 Inscripción a Comisión
```
Validaciones:
1. ✅ La comisión debe existir y estar activa
2. ✅ No estar ya inscrito en esa comisión
3. ✅ Cumplir correlativas para cursar
4. ✅ No tener la materia aprobada
5. ✅ Hay cupo disponible (máximo 30 alumnos)
```

#### 4.2 Estados de Inscripción
```
Estado 0: ACTIVA - Alumno inscrito y cursando
Estado 1: PENDIENTE DE BAJA - Solicitud enviada
Estado 2: BAJA APROBADA - Ya no está inscrito
```

### 5. Sistema de Promedios

#### 5.1 Promedio de Parciales
```cpp
// Con recuperatorio
Parcial 1: 3, Recuperatorio P1: 8
Parcial 2: 7

Nota Final P1 = 8 (el recuperatorio reemplaza)
Nota Final P2 = 7
Promedio = (8 + 7) / 2 = 7.5
```

#### 5.2 Promedio General del Alumno
```
Se calcula SOLO con finales aprobados (nota >= 4)

Finales aprobados:
- Programación I: 8
- Matemática: 7
- Base de Datos I: 9

Promedio General = (8 + 7 + 9) / 3 = 8.0
```

---

## 💾 Archivos de Datos (.dat)

### Estructura de Archivos Binarios

El sistema utiliza 8 archivos principales para persistencia:

| Archivo | Descripción | Estructura Principal |
|---------|-------------|---------------------|
| **Alumnos.dat** | Datos de alumnos | Legajo, Nombre, Apellido, DNI, Dirección, Teléfono, Email, FechaNac, Eliminado |
| **Docentes.dat** | Datos de docentes | Legajo, Nombre, Apellido, DNI, Especialidad, Eliminado |
| **Materias.dat** | Plan de estudios | ID, Nombre, Cuatrimestre, Eliminado |
| **Comisiones.dat** | Grupos de cursada | ID, IDMateria, LegajoDocente, Turno, Modalidad, Cuatrimestre, Año, Eliminado |
| **Examenes.dat** | Historial de exámenes | ID, IDMateria, LegajoAlumno, Tipo, NumeroParcial, Fecha, Nota, Corregido, Eliminado |
| **InscripcionesComision.dat** | Inscripciones | LegajoAlumno, IDComision, Fecha, Estado |
| **Correlativas.dat** | Prerrequisitos | IDMateriaObjetivo, IDMateriaRequisito, Eliminado |
| **Carreras.dat** | Carreras disponibles | ID, Nombre, DuracionCuatrimestres, Eliminado |

### Ejemplo de Estructura de Examen

```cpp
class Examen {
    int   _idExamen;           // 1001
    int   _idMateria;          // 5 (Programación II)
    int   _legajoAlumno;       // 1001
    char  _tipo[15];           // "Parcial", "Recuperatorio", "Final"
    int   _numeroParcial;      // 1 o 2 (para parciales/recuperatorios)
    Fecha _fecha;              // 15/11/2024
    int   _nota;               // 8
    bool  _corregido;          // true
    bool  _eliminado;          // false
};
```

### Inicialización de Datos

Para crear datos de prueba con el plan de estudios completo:

```bash
./build/inicializar_datos
```

Esto crea:
- 1 Carrera: Tecnicatura Universitaria en Programación
- 17 Materias organizadas en 4 cuatrimestres
- 23 Correlativas del plan de estudios

---

## 🎛️ Módulos del Sistema

### 1. Módulo de Alumnos (MenuAlumno)

**Funcionalidades:**
- Ver mi información personal
- Ver mis comisiones actuales
- Inscribirse a comisiones
- Solicitar baja de comisión
- Ver materias aprobadas
- Ver materias pendientes
- Ver historial de notas
- Ver finales pendientes
- Inscribirse a mesa de examen

### 2. Módulo de Docentes (MenuDocente)

**Funcionalidades:**
- Ver mis comisiones asignadas
- Cargar notas de parciales
- Cargar notas de recuperatorios
- Cargar notas de finales
- Ver listado de alumnos por comisión
- Generar actas de examen

### 3. Módulo de Administración (MenuAdmin)

**Funcionalidades:**
- ABM Alumnos
- ABM Docentes
- ABM Materias
- ABM Comisiones
- ABM Exámenes
- ABM Correlativas
- Gestionar solicitudes de baja
- Sistema de reportes (13 reportes)
- Exportar datos a CSV
- Backup y restauración

### 4. Módulo de Exámenes (MenuAbmExamen)

**Funcionalidades:**
- Cargar parcial (con validaciones)
- Cargar recuperatorio (solo si hay desaprobados)
- Cargar final (con todas las validaciones)
- Listar exámenes por alumno
- Recalcular condición académica
- Mostrar todos los exámenes

### 5. Módulo de Reportes (ManagerReportes)

**13 Reportes Implementados:**

#### Alta Prioridad (5)
1. Rendimiento académico por alumno
2. Listado de alumnos por comisión
3. Estadísticas por materia
4. Finales pendientes por alumno
5. Estado de comisiones por cupo

#### Media Prioridad (5)
6. Ranking de alumnos por promedio
7. Calendario de finales
8. Historial de notas por materia
9. Alumnos en riesgo académico
10. Carga horaria de docentes

#### Baja Prioridad - Analíticos (3)
11. Tasa de aprobación por cuatrimestre
12. Materias con mayor índice de libre
13. Tiempo promedio de carrera

---

## 🔧 Compilación y Ejecución

### Requisitos

- **C++20** o superior
- **CMake 3.16** o superior
- **Make** o equivalente
- **Linux/Unix** (también funciona en Windows con MinGW)

### Compilación

```bash
# 1. Crear directorio de compilación
mkdir build
cd build

# 2. Configurar con CMake
cmake ..

# 3. Compilar
make

# 4. Volver al directorio raíz
cd ..
```

### Ejecución

```bash
# Ejecutar el programa principal
./build/TP_UTN_Campus

# Ejecutar inicializador de datos (primera vez)
./build/inicializar_datos

# Ejecutar tests
./build/runTests
```

---

## 🎮 Uso del Sistema

### Primera Ejecución

1. **Inicializar datos de prueba:**
```bash
./build/inicializar_datos
```
Esto crea la carrera, materias y correlativas.

2. **Ejecutar el sistema:**
```bash
./build/TP_UTN_Campus
```

3. **Menú Principal:**
```
=== SISTEMA DE GESTIÓN UNIVERSITARIA ===

1. Acceso Alumno
2. Acceso Docente
3. Acceso Administrador
0. Salir

Opción:
```

### Credenciales por Defecto

Para probar el sistema, puedes crear usuarios manualmente o usar los que cargues.

#### Como Administrador
- Accede con código de administrador
- Puedes crear alumnos, docentes, materias, etc.

#### Como Alumno
- Ingresa con tu legajo
- Verifica que exista en Alumnos.dat

#### Como Docente
- Ingresa con tu legajo
- Verifica que exista en Docentes.dat

### Flujo de Uso Típico

#### 1. Administrador Crea Estructura
```
1. Crear materias del plan de estudios
2. Definir correlativas
3. Crear comisiones para cada materia
4. Asignar docentes a comisiones
5. Dar de alta alumnos
```

#### 2. Alumno Se Inscribe
```
1. Login con legajo
2. Ver materias disponibles
3. Verificar correlativas
4. Inscribirse a comisiones
5. Ver mi horario
```

#### 3. Docente Carga Notas
```
1. Login con legajo
2. Ver mis comisiones
3. Seleccionar comisión
4. Cargar parciales
5. Cargar recuperatorios si hay desaprobados
```

#### 4. Alumno Rinde Final
```
1. Verificar condición (debe estar REGULAR)
2. Inscribirse a mesa de examen
3. Docente carga nota de final
4. Sistema actualiza estado a APROBADO
```

---

## 📊 Sistema de Reportes

### Ejemplo de Uso

```cpp
#include "ManagerReportes.h"

int main() {
    ManagerReportes reportes;

    // Ver rendimiento de un alumno
    reportes.reporteRendimientoAcademico(1001);

    // Estadísticas de una materia
    reportes.estadisticasPorMateria(5);

    // Ranking general
    reportes.rankingAlumnosPorPromedio();

    return 0;
}
```

### Salida de Ejemplo

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

Ver documentación completa en [REPORTES.md](REPORTES.md)

---

## 📁 Estructura de Archivos

```
TP-UTN-Campus/
├── README.md                       # Este archivo
├── REPORTES.md                     # Documentación de reportes
├── INICIALIZAR_DATOS.md           # Guía de inicialización
├── CMakeLists.txt                 # Configuración de compilación
│
├── Clases de Entidades/
│   ├── Persona.h/cpp              # Clase base
│   ├── Alumno.h/cpp               # Hereda de Persona
│   ├── Docente.h/cpp              # Hereda de Persona
│   ├── Materia.h/cpp
│   ├── Comision.h/cpp
│   ├── Examen.h/cpp
│   ├── InscripcionComision.h/cpp
│   ├── Correlativa.h/cpp
│   ├── Carrera.h/cpp
│   ├── Fecha.h/cpp
│   └── Direccion.h/cpp
│
├── Clases de Archivos/
│   ├── ArchivoAlumno.h/cpp
│   ├── ArchivoDocente.h/cpp
│   ├── ArchivoMateria.h/cpp
│   ├── ArchivoComision.h/cpp
│   ├── ArchivoExamen.h/cpp
│   ├── ArchivoInscripcionComision.h/cpp
│   ├── ArchivoCorrelativa.h/cpp
│   ├── ArchivoCarrera.h/cpp
│   └── ArchivoPersona.h/cpp
│
├── Clases de Managers/
│   ├── ManagerAlumno.h/cpp
│   ├── ManagerDocente.h/cpp
│   ├── ManagerExamen.h/cpp
│   ├── ManagerReportes.h/cpp       # 13 reportes
│   ├── ManagerComision.h/cpp
│   ├── ManagerMateria.h/cpp
│   ├── ManagerCorrelativa.h/cpp
│   ├── ManagerCarrera.h/cpp
│   └── ManagerInscripcionComision.h/cpp
│
├── Clases de Menús/
│   ├── MenuPrincipal.h/cpp        # Menú de acceso
│   ├── MenuAdmin.h/cpp            # Panel de administración
│   ├── MenuAlumno.h/cpp           # Panel del alumno
│   ├── MenuDocente.h/cpp          # Panel del docente
│   ├── MenuAbmExamen.h/cpp        # ABM de exámenes
│   ├── MenuAbmMateria.h/cpp
│   ├── MenuAbmComision.h/cpp
│   ├── MenuAbmCarrera.h/cpp
│   ├── MenuAbmCorrelativa.h/cpp
│   ├── MenuDatosCSV.h/cpp         # Exportar a CSV
│   ├── MenuCopiaSeguridad.h/cpp   # Backup/Restore
│   └── MenuUtilitarios.h/cpp
│
├── Utilidades/
│   ├── Validacion.h/cpp           # Validación de inputs
│   ├── ValidadorAcceso.h/cpp      # Control de acceso
│   └── utils.h/cpp                # Funciones auxiliares
│
├── Datos/
│   ├── Alumnos.dat
│   ├── Docentes.dat
│   ├── Materias.dat
│   ├── Comisiones.dat
│   ├── Examenes.dat
│   ├── InscripcionesComision.dat
│   ├── Correlativas.dat
│   └── Carreras.dat
│
├── Tests/
│   └── test_alumno.cpp
│
├── Inicializador/
│   └── inicializar_datos.cpp
│
└── main.cpp                        # Punto de entrada
```

---

## 🧪 Testing

El proyecto incluye tests unitarios con GoogleTest:

```bash
# Ejecutar todos los tests
./build/runTests

# Ver cobertura
make test
```

---

## 📚 Documentación Adicional

- [REPORTES.md](REPORTES.md) - Documentación completa de los 13 reportes
- [INICIALIZAR_DATOS.md](INICIALIZAR_DATOS.md) - Guía de inicialización de datos
- [test_data/README.md](test_data/README.md) - Datos de prueba

---

## 🐛 Solución de Problemas

### Problema: Archivos .dat no encontrados
```
Solución: Ejecutar ./build/inicializar_datos desde la raíz del proyecto
```

### Problema: Error de compilación por C++20
```
Solución: Verificar que el compilador soporte C++20
export CXX=g++-11 (o superior)
```

### Problema: Usuario no puede rendir final
```
Verificar:
1. ¿Está inscrito en la comisión?
2. ¿Está REGULAR? (promedio >= 4)
3. ¿Cumple correlativas?
4. ¿Ya tiene final aprobado?
```

### Problema: No puede promocionar aunque tiene 8 y 8
```
Verificar:
- ¿Usó recuperatorio? Si es así, solo puede regularizar.
```

---

## 👥 Contribuciones

Este es un proyecto académico para la UTN.

---

## 📄 Licencia

Proyecto académico - UTN

---

## 📞 Contacto

Para consultas sobre el proyecto, revisar el código fuente o contactar a los desarrolladores.

---

## 🎯 Características Técnicas

### Tecnologías Utilizadas
- **Lenguaje**: C++20
- **Build System**: CMake 3.16+
- **Testing**: GoogleTest
- **Persistencia**: Archivos binarios (.dat)
- **Patrones**: Repository, MVC, Manager
- **STL**: vector, algorithm, string, iostream

### Buenas Prácticas Implementadas
- ✅ Separación de responsabilidades
- ✅ Validación de entrada robusta
- ✅ Manejo de errores
- ✅ Código modular y reutilizable
- ✅ Documentación completa
- ✅ Nombres descriptivos
- ✅ Funciones auxiliares centralizadas (utils.h)
- ✅ Tests unitarios

---

**Desarrollado como Trabajo Práctico para la UTN** 🎓
