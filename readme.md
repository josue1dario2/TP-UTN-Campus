# 📘 Informe Académico - Sistema de Gestión Universitaria

**Trabajo Práctico Final - Laboratorio de Computación II**
**Universidad Tecnológica Nacional**

---

## 📋 Índice

1. [Introducción](#1-introducción)
2. [Objetivo del Sistema](#2-objetivo-del-sistema)
3. [Reglas de Negocio](#3-reglas-de-negocio)
4. [Arquitectura del Sistema](#4-arquitectura-del-sistema)
5. [Modelo de Datos](#5-modelo-de-datos)
6. [Diagrama UML de Clases](#6-diagrama-uml-de-clases)
7. [Casos de Uso Principales](#7-casos-de-uso-principales)
8. [Implementación Técnica](#8-implementación-técnica)
9. [Conclusiones](#9-conclusiones)

---

## 1. Introducción

El presente trabajo consiste en el desarrollo de un **Sistema Completo de Gestión Universitaria** implementado en C++20. El sistema permite administrar todos los aspectos académicos de una institución universitaria, desde la gestión de alumnos y docentes hasta el control de exámenes, inscripciones y generación de reportes estadísticos.

### 1.1 Alcance del Proyecto

El sistema cubre:
- Gestión de alumnos, docentes y personal administrativo
- Administración del plan de estudios (materias y correlativas)
- Control de comisiones y cupos
- Sistema completo de exámenes (parciales, recuperatorios, finales)
- Cálculo automático de condiciones académicas
- Sistema de reportes estadísticos (13 reportes)
- Persistencia de datos en archivos binarios
- Exportación a CSV y backups

### 1.2 Tecnologías Utilizadas

- **Lenguaje**: C++20
- **Sistema de Build**: CMake 3.16
- **Testing**: GoogleTest
- **Persistencia**: Archivos binarios (.dat)
- **Paradigma**: Programación Orientada a Objetos
- **Patrones**: Repository, MVC, Manager

---

## 2. Objetivo del Sistema

El objetivo principal es **automatizar y centralizar la gestión académica universitaria**, garantizando:

### 2.1 Objetivos Funcionales

1. **Integridad de Datos**: Validación exhaustiva en todas las operaciones
2. **Aplicación de Reglas Académicas**: Cumplimiento automático de normativas
3. **Trazabilidad**: Historial completo de todas las operaciones
4. **Acceso Diferenciado**: Permisos específicos por rol (Alumno/Docente/Admin)
5. **Reportes Estadísticos**: 13 reportes para toma de decisiones

### 2.2 Objetivos No Funcionales

1. **Rendimiento**: Operaciones en tiempo real
2. **Mantenibilidad**: Código modular y documentado
3. **Escalabilidad**: Arquitectura por capas
4. **Confiabilidad**: Sistema de backups y restauración
5. **Portabilidad**: Compatible con Linux/Windows

---

## 3. Reglas de Negocio

### 3.1 Sistema de Exámenes

#### 3.1.1 Parciales

**Definición**: Evaluaciones periódicas durante la cursada de una materia.

**Reglas:**
- Se toman **2 (dos) parciales obligatorios** por materia
- Escala de calificación: **0 a 10**
- Nota mínima de aprobación: **4 (cuatro)**
- Cada parcial se identifica por su número (1 o 2)

**Validaciones:**
```
✅ El alumno debe estar inscrito en la comisión
✅ No se pueden cargar más de 2 parciales
✅ La nota debe estar entre 0 y 10
✅ Se asigna automáticamente el número de parcial (1 o 2)
```

**Implementación:**
```cpp
void ManagerExamen::cargarParcial(int legajoAlumno, int idComision, int nota) {
    // 1. Validar que la comisión existe
    // 2. Validar que el alumno está inscrito
    // 3. Contar parciales existentes (máximo 2)
    // 4. Asignar número de parcial automáticamente
    // 5. Guardar examen
}
```

#### 3.1.2 Recuperatorios

**Definición**: Instancia adicional para recuperar parciales desaprobados.

**Reglas Críticas:**
- Solo se puede recuperar un parcial **DESAPROBADO** (nota < 4)
- Se otorga **1 (un) recuperatorio por parcial**
- El recuperatorio **REEMPLAZA** la nota del parcial original (no la promedia)
- Mantiene el mismo número de parcial que recupera

**Validaciones:**
```
✅ El alumno debe tener al menos un parcial desaprobado
✅ El recuperatorio debe corresponder a un parcial existente
✅ Se identifica qué parcial recupera (P1 o P2)
```

**Ejemplo de Aplicación:**
```
Caso 1: Alumno aprueba con recuperatorio
  Parcial 1: 3 (desaprobado)
  Recuperatorio P1: 7 (aprobado)
  Parcial 2: 8 (aprobado)

  Nota Final P1 = 7 (el recuperatorio reemplaza el 3)
  Nota Final P2 = 8
  Promedio = (7 + 8) / 2 = 7.5

Caso 2: Alumno usa recuperatorio pero no llega a 7
  Parcial 1: 2 (desaprobado)
  Recuperatorio P1: 6 (aprobado)
  Parcial 2: 7 (aprobado)

  Nota Final P1 = 6
  Nota Final P2 = 7
  Promedio = (6 + 7) / 2 = 6.5
  Condición: REGULAR (usó recuperatorio, no puede promocionar)
```

**Implementación:**
```cpp
void ManagerExamen::cargarRecuperatorio(int legajoAlumno, int idComision, int nota) {
    // 1. Validar inscripción
    // 2. Buscar parciales desaprobados (nota < 4)
    // 3. Tomar el último parcial desaprobado
    // 4. Crear recuperatorio con el mismo numeroParcial
    // 5. Guardar examen
}
```

#### 3.1.3 Finales

**Definición**: Examen final integrador de la materia.

**Reglas:**
- Solo para alumnos **REGULARES**
- Requiere cumplir **correlativas aprobadas**
- No se permite si el alumno está **PROMOCIONADO** o **LIBRE**
- Nota mínima de aprobación: **4 (cuatro)**

**Validaciones del Sistema:**
```
1. ✅ Alumno inscrito en la comisión
2. ✅ Cumplir correlativas (materias previas aprobadas)
3. ✅ Estar en condición REGULAR
4. ✅ NO estar promocionado
5. ✅ NO estar libre
6. ✅ NO tener final aprobado anteriormente
```

**Casos Especiales:**
```
❌ Alumno PROMOCIONADO intenta rendir final
   Error: "Está PROMOCIONADO. No necesita rendir final."
   Razón: Ya aprobó la materia con promoción directa

❌ Alumno LIBRE intenta rendir final
   Error: "Está LIBRE. Debe cursar y regularizar primero."
   Razón: No cumple requisitos mínimos de cursada

❌ Alumno NO inscrito intenta rendir
   Error: "NO está inscrito en esta comisión."
   Razón: No cursó la materia
```

### 3.2 Condiciones Académicas

#### 3.2.1 PROMOCIONADO

**Definición**: El alumno aprueba la materia sin rendir examen final.

**Requisitos Obligatorios:**
```
1. ✅ Haber rendido AMBOS parciales (P1 y P2)
2. ✅ NO haber usado NINGÚN recuperatorio
3. ✅ Promedio >= 7 (siete)
```

**Fórmula de Cálculo:**
```
Promedio = (NotaP1 + NotaP2) / 2

Si Promedio >= 7.0 Y NO usó recuperatorio → PROMOCIONADO
```

**Ejemplos:**
```
✅ Caso Promocionado Válido:
   P1: 8, P2: 7
   Promedio: 7.5
   Recuperatorios: Ninguno
   → PROMOCIONADO

✅ Caso Promocionado Límite:
   P1: 7, P2: 7
   Promedio: 7.0
   Recuperatorios: Ninguno
   → PROMOCIONADO

❌ Caso NO Promocionado (usó recuperatorio):
   P1: 3, RecuP1: 9, P2: 8
   Promedio: 8.5
   Recuperatorios: Usó RecuP1
   → REGULAR (aunque el promedio sea > 7)

❌ Caso NO Promocionado (promedio < 7):
   P1: 6, P2: 6
   Promedio: 6.0
   Recuperatorios: Ninguno
   → REGULAR
```

**Consecuencias:**
- ✅ Aprueba automáticamente la materia
- ✅ No necesita rendir final
- ✅ Se registra como materia aprobada
- ✅ Cumple como correlativa para otras materias

**Implementación:**
```cpp
bool ManagerExamen::estaPromocionado(int legajoAlumno, int idComision) {
    // 1. Buscar parciales y recuperatorios del alumno
    // 2. Si existe CUALQUIER recuperatorio → return false
    // 3. Verificar que existan ambos parciales
    // 4. Calcular promedio
    // 5. return (promedio >= 7.0)
}
```

#### 3.2.2 REGULAR

**Definición**: El alumno está habilitado para rendir examen final.

**Requisitos Obligatorios:**
```
1. ✅ Haber rendido AMBOS parciales (P1 y P2)
2. ✅ Promedio >= 4 (cuatro)
3. ✅ NO estar PROMOCIONADO
```

**Casos que Resultan en REGULAR:**
```
Caso A: Promedio entre 4 y 7 sin recuperatorio
  P1: 6, P2: 5
  Promedio: 5.5
  → REGULAR

Caso B: Promedio >= 7 CON recuperatorio
  P1: 3, RecuP1: 9, P2: 8
  Promedio: 8.5
  → REGULAR (usó recuperatorio, no puede promocionar)

Caso C: Promedio >= 4 con recuperatorios
  P1: 3, RecuP1: 4, P2: 5
  Promedio: 4.5
  → REGULAR
```

**Fórmula de Cálculo:**
```
Paso 1: Calcular notas finales
  NotaFinalP1 = (RecuP1 != -1) ? RecuP1 : NotaP1
  NotaFinalP2 = (RecuP2 != -1) ? RecuP2 : NotaP2

Paso 2: Calcular promedio
  Promedio = (NotaFinalP1 + NotaFinalP2) / 2

Paso 3: Evaluar condición
  Si Promedio >= 4.0 Y NO promocionado → REGULAR
```

**Consecuencias:**
- ✅ Puede inscribirse a mesas de examen final
- ✅ Mantiene condición por tiempo determinado
- ❌ NO cumple como correlativa hasta aprobar final
- ❌ NO tiene la materia aprobada aún

**Implementación:**
```cpp
bool ManagerExamen::estaRegular(int legajoAlumno, int idComision) {
    // 1. Si está promocionado → return false
    // 2. Buscar parciales y recuperatorios
    // 3. Aplicar recuperatorios (reemplazan parciales)
    // 4. Verificar que existan ambos parciales
    // 5. Calcular promedio con notas finales
    // 6. return (promedio >= 4.0)
}
```

#### 3.2.3 LIBRE

**Definición**: El alumno NO cumple requisitos mínimos de cursada.

**Casos que Resultan en LIBRE:**
```
Caso A: No rindió ambos parciales
  P1: 7, P2: -
  → LIBRE (falta rendir P2)

Caso B: Promedio < 4
  P1: 3, P2: 2
  Promedio: 2.5
  → LIBRE

Caso C: Promedio < 4 incluso con recuperatorio
  P1: 2, RecuP1: 3, P2: 3
  Promedio: 3.0
  → LIBRE
```

**Consecuencias:**
- ❌ NO puede rendir final
- ❌ Debe volver a cursar la materia
- ❌ Debe inscribirse nuevamente
- ❌ Pierde todo avance anterior

**Implementación:**
```cpp
bool ManagerExamen::estaLibre(int legajoAlumno, int idComision) {
    // 1. return !estaPromocionado() && !estaRegular()
}
```

### 3.3 Sistema de Correlativas

#### 3.3.1 Definición

**Correlativa**: Materia que debe estar **APROBADA** (final >= 4) para poder cursar otra materia.

#### 3.3.2 Reglas

**Para CURSAR una materia:**
```
✅ Todas las materias correlativas deben estar APROBADAS
✅ Aprobada = Final rendido con nota >= 4
✅ Promoción también cuenta como aprobada
```

**Para RENDIR FINAL:**
```
✅ Todas las correlativas deben estar aprobadas
✅ Además, debe estar REGULAR en la materia
```

#### 3.3.3 Ejemplo del Plan de Estudios

**Tecnicatura Universitaria en Programación:**

```
NIVEL I (Cuatrimestre 1)
1. Programación I (sin correlativas)
2. Arquitectura y Sistemas Operativos (sin correlativas)
3. Matemática (sin correlativas)
4. Organización Empresarial (sin correlativas)

NIVEL I (Cuatrimestre 2)
5. Programación II
   Correlativas:
   - Programación I ✅ (debe estar aprobada)
   - Arquitectura y Sistemas Operativos ✅

6. Probabilidad y Estadística
   Correlativas:
   - Matemática ✅

7. Base de Datos I
   Correlativas:
   - Programación I ✅
   - Matemática ✅

8. Inglés I (sin correlativas)

NIVEL II (Cuatrimestre 3)
9. Programación III
   Correlativas:
   - Programación II ✅
   - Base de Datos I ✅

10. Base de Datos II
    Correlativas:
    - Base de Datos I ✅

11. Metodología de Sistemas I
    Correlativas:
    - Programación II ✅
    - Base de Datos I ✅
    - Organización Empresarial ✅

12. Inglés II
    Correlativas:
    - Inglés I ✅

NIVEL II (Cuatrimestre 4)
13. Programación IV
    Correlativas:
    - Programación III ✅
    - Base de Datos II ✅
    - Metodología de Sistemas I ✅

14. Metodología de Sistemas II
    Correlativas:
    - Metodología de Sistemas I ✅

15. Introducción al Análisis de Datos
    Correlativas:
    - Base de Datos II ✅
    - Probabilidad y Estadística ✅
    - Base de Datos I ✅

16. Legislación
    Correlativas:
    - Base de Datos I ✅
    - Organización Empresarial ✅

17. Gestión de Desarrollo de Software
    Correlativas:
    - Programación III ✅
    - Base de Datos II ✅
```

#### 3.3.4 Validación de Correlativas

**Implementación:**
```cpp
bool ManagerAlumno::cumpleCorrelativas(int legajoAlumno, int idMateriaObjetivo) {
    // 1. Buscar todas las correlativas de la materia objetivo
    // 2. Para cada correlativa:
    //    a. Verificar que el alumno tenga final aprobado (nota >= 4)
    // 3. Si falta alguna → return false
    // 4. Si cumple todas → return true
}
```

**Ejemplo de Validación:**
```
Alumno quiere cursar Programación III (ID: 9)

Correlativas requeridas:
- Programación II (ID: 5)
- Base de Datos I (ID: 7)

Verificación:
1. Buscar final de Programación II del alumno
   → Final: nota 8 → ✅ CUMPLE

2. Buscar final de Base de Datos I del alumno
   → Final: nota 6 → ✅ CUMPLE

Resultado: ✅ Puede inscribirse a Programación III
```

### 3.4 Sistema de Inscripciones

#### 3.4.1 Inscripción a Comisión

**Validaciones Obligatorias:**
```
1. ✅ La comisión debe existir y estar activa
2. ✅ El alumno NO debe estar ya inscrito en esa comisión
3. ✅ Debe cumplir correlativas para cursar
4. ✅ NO debe tener la materia aprobada
5. ✅ Debe haber cupo disponible (máximo 30 alumnos)
```

**Estados de Inscripción:**
```
Estado 0: ACTIVA
  - Alumno inscrito y cursando
  - Puede rendir parciales

Estado 1: PENDIENTE DE BAJA
  - Alumno solicitó baja
  - Esperando aprobación de administrador

Estado 2: BAJA APROBADA
  - Inscripción cancelada
  - Alumno NO puede rendir exámenes
```

#### 3.4.2 Proceso de Baja

**Flujo:**
```
1. Alumno solicita baja de comisión
   → Estado cambia a 1 (PENDIENTE)

2. Administrador revisa solicitud
   → Puede APROBAR o RECHAZAR

3. Si aprueba:
   → Estado cambia a 2 (BAJA DEFINITIVA)
   → Libera cupo en la comisión

4. Si rechaza:
   → Estado vuelve a 0 (ACTIVA)
   → Alumno continúa cursando
```

### 3.5 Sistema de Cupos

**Regla:** Cada comisión tiene un cupo máximo de **30 alumnos**.

**Validación:**
```cpp
int inscriptos = contarInscriptosEnComision(idComision);
if (inscriptos >= 30) {
    cout << "ERROR: Comisión llena";
    return false;
}
```

**Estados de Comisión:**
```
- Disponible: < 50% ocupado (< 15 alumnos)
- Media: 50-80% ocupado (15-24 alumnos)
- Casi llena: 80-99% ocupado (24-29 alumnos)
- LLENA: 100% ocupado (30 alumnos)
```

---

## 4. Arquitectura del Sistema

### 4.1 Patrón Arquitectónico

El sistema implementa el patrón **Repository** con arquitectura de **3 capas**:

```
┌────────────────────────────────────────┐
│     CAPA DE PRESENTACIÓN (Menús)      │
│  MenuAlumno, MenuAdmin, MenuDocente    │
│  - Interacción con usuario             │
│  - Validación de entrada               │
│  - Formato de salida                   │
└──────────────┬─────────────────────────┘
               │
┌──────────────▼─────────────────────────┐
│  CAPA DE LÓGICA DE NEGOCIO (Managers) │
│  ManagerAlumno, ManagerExamen, etc.    │
│  - Reglas de negocio                   │
│  - Validaciones complejas              │
│  - Cálculos de condiciones             │
│  - Coordinación de operaciones         │
└──────────────┬─────────────────────────┘
               │
┌──────────────▼─────────────────────────┐
│  CAPA DE ACCESO A DATOS (Archivos)    │
│  ArchivoAlumno, ArchivoExamen, etc.    │
│  - CRUD de registros                   │
│  - Búsqueda y filtrado                 │
│  - Gestión de archivos .dat            │
└──────────────┬─────────────────────────┘
               │
┌──────────────▼─────────────────────────┐
│      CAPA DE PERSISTENCIA (.dat)      │
│  Alumnos.dat, Examenes.dat, etc.       │
│  - Almacenamiento binario              │
│  - Persistencia en disco               │
└────────────────────────────────────────┘
```

### 4.2 Responsabilidades por Capa

#### Capa de Presentación
- Mostrar menús y opciones
- Capturar entrada del usuario
- Validar formato de entrada
- Formatear salida
- Control de flujo de la aplicación

#### Capa de Lógica de Negocio
- Aplicar reglas académicas
- Validar condiciones complejas
- Calcular promedios y condiciones
- Verificar correlativas
- Coordinar múltiples operaciones

#### Capa de Acceso a Datos
- Leer/Escribir archivos binarios
- Buscar registros por ID
- Filtrar por criterios
- Modificar registros existentes
- Eliminar (lógico) registros

#### Capa de Persistencia
- Almacenamiento físico en disco
- Archivos binarios (.dat)
- Formato binario optimizado

---

## 5. Modelo de Datos

### 5.1 Archivos de Persistencia

El sistema utiliza **8 archivos binarios (.dat)** principales:

#### 5.1.1 Alumnos.dat

**Estructura:**
```cpp
class Alumno : public Persona {
private:
    int   _legajo;           // Identificador único
    char  _nombre[50];       // Heredado de Persona
    char  _apellido[50];     // Heredado de Persona
    int   _dni;              // Heredado de Persona
    Direccion _direccion;    // Domicilio completo
    char  _telefono[15];
    char  _email[100];
    Fecha _fechaNacimiento;
    bool  _eliminado;        // Baja lógica
};
```

**Ejemplo de Registro:**
```
Legajo: 1001
Nombre: Juan
Apellido: Pérez
DNI: 12345678
Dirección: Calle Falsa 123, Springfield
Teléfono: 1234-5678
Email: juan.perez@alumno.utn.edu.ar
Fecha Nac: 15/03/2000
Eliminado: false
```

#### 5.1.2 Docentes.dat

**Estructura:**
```cpp
class Docente : public Persona {
private:
    int   _legajo;           // Identificador único
    char  _nombre[50];
    char  _apellido[50];
    int   _dni;
    char  _especialidad[100];// Área de conocimiento
    bool  _eliminado;
};
```

**Ejemplo de Registro:**
```
Legajo: 5001
Nombre: María
Apellido: González
DNI: 23456789
Especialidad: Ingeniería en Sistemas
Eliminado: false
```

#### 5.1.3 Materias.dat

**Estructura:**
```cpp
class Materia {
private:
    int  _idMateria;         // Identificador único
    char _nombre[100];       // Nombre de la materia
    int  _cuatrimestre;      // 1, 2, 3 o 4
    bool _eliminado;
};
```

**Ejemplo de Registros:**
```
ID: 1, Nombre: Programación I, Cuatrimestre: 1
ID: 2, Nombre: Arquitectura y Sistemas Operativos, Cuatrimestre: 1
ID: 5, Nombre: Programación II, Cuatrimestre: 2
ID: 9, Nombre: Programación III, Cuatrimestre: 3
ID: 13, Nombre: Programación IV, Cuatrimestre: 4
```

#### 5.1.4 Comisiones.dat

**Estructura:**
```cpp
class Comision {
private:
    int  _idComision;        // Identificador único
    int  _idMateria;         // FK a Materias
    char _turno[10];         // "Mañana", "Tarde", "Noche"
    char _modalidad[10];     // "Presencial", "Virtual"
    int  _cuatrimestre;      // Período lectivo
    int  _anio;              // Año lectivo
    int  _legajoDocente;     // FK a Docentes
    bool _eliminado;
};
```

**Ejemplo de Registro:**
```
ID: 101
IDMateria: 5 (Programación II)
Turno: Mañana
Modalidad: Presencial
Cuatrimestre: 2
Año: 2024
LegajoDocente: 5001
Eliminado: false
```

**Nota:** El cupo estándar es de 30 alumnos por comisión.

#### 5.1.5 Examenes.dat

**Estructura:**
```cpp
class Examen {
private:
    int   _idExamen;         // Identificador único
    int   _idMateria;        // FK a Materias
    int   _legajoAlumno;     // FK a Alumnos
    char  _tipo[15];         // "Parcial", "Recuperatorio", "Final"
    int   _numeroParcial;    // 1, 2 (para parciales/recuperatorios)
    Fecha _fecha;            // Fecha del examen
    int   _nota;             // 0-10
    bool  _corregido;        // true/false
    bool  _eliminado;
};
```

**Ejemplo de Registros:**
```
// Parcial 1
ID: 1001, IDMateria: 5, Legajo: 1001, Tipo: "Parcial"
NumeroParcial: 1, Fecha: 15/09/2024, Nota: 3, Corregido: true

// Recuperatorio del Parcial 1
ID: 1002, IDMateria: 5, Legajo: 1001, Tipo: "Recuperatorio"
NumeroParcial: 1, Fecha: 20/10/2024, Nota: 7, Corregido: true

// Parcial 2
ID: 1003, IDMateria: 5, Legajo: 1001, Tipo: "Parcial"
NumeroParcial: 2, Fecha: 15/10/2024, Nota: 8, Corregido: true

// Final
ID: 1004, IDMateria: 5, Legajo: 1001, Tipo: "Final"
NumeroParcial: 0, Fecha: 15/12/2024, Nota: 7, Corregido: true
```

#### 5.1.6 InscripcionesComision.dat

**Estructura:**
```cpp
class InscripcionComision {
private:
    int   _legajoAlumno;     // FK a Alumnos
    int   _idComision;       // FK a Comisiones
    Fecha _fecha;            // Fecha de inscripción
    int   _estado;           // 0: Activa, 1: Pendiente, 2: Baja
};
```

**Ejemplo de Registros:**
```
Legajo: 1001, IDComision: 101, Fecha: 01/08/2024, Estado: 0 (Activa)
Legajo: 1002, IDComision: 101, Fecha: 01/08/2024, Estado: 1 (Pendiente)
Legajo: 1003, IDComision: 102, Fecha: 01/08/2024, Estado: 2 (Baja)
```

#### 5.1.7 Correlativas.dat

**Estructura:**
```cpp
class Correlativa {
private:
    int  _idMateriaObjetivo;  // Materia que requiere correlativas
    int  _idMateriaRequisito; // Materia que debe estar aprobada
    bool _eliminado;
};
```

**Ejemplo de Registros:**
```
MateriaObjetivo: 5 (Programación II)
  → Requisito: 1 (Programación I)
  → Requisito: 2 (Arquitectura y SO)

MateriaObjetivo: 9 (Programación III)
  → Requisito: 5 (Programación II)
  → Requisito: 7 (Base de Datos I)

MateriaObjetivo: 13 (Programación IV)
  → Requisito: 9 (Programación III)
  → Requisito: 10 (Base de Datos II)
  → Requisito: 11 (Metodología I)
```

#### 5.1.8 Carreras.dat

**Estructura:**
```cpp
class Carrera {
private:
    int  _idCarrera;         // Identificador único
    char _nombre[100];       // Nombre de la carrera
    int  _duracionCuatrimestres; // Duración total
    bool _eliminado;
};
```

**Ejemplo de Registro:**
```
ID: 1
Nombre: Tecnicatura Universitaria en Programación
Duración: 4 cuatrimestres (2 años)
Eliminado: false
```

### 5.2 Relaciones entre Entidades

```
Alumno (1) ─────── (N) InscripcionComision (N) ─────── (1) Comision
                                                              │
                                                              │
Alumno (1) ─────── (N) Examen (N) ─────────────────────────  │
                          │                                   │
                          │                                   │
                          └──────────(N) Materia (1) ─────────┘
                                          │
                                          │
                          Materia (N) ─── (N) Correlativa
                          (objetivo)         (requisito)
                                          │
                                          │
Docente (1) ─────────────────────────────┘
     │
     │
Persona (clase base)
```

---

## 6. Diagrama UML de Clases

### 6.1 Clases Principales del Dominio

```
┌─────────────────────┐
│      Persona        │ (Abstracta)
├─────────────────────┤
│ - legajo: int       │
│ - nombre: char[50]  │
│ - apellido: char[50]│
│ - dni: int          │
│ - eliminado: bool   │
├─────────────────────┤
│ + getLegajo()       │
│ + getNombre()       │
│ + virtual mostrar() │
└──────────△──────────┘
           │
           │ (herencia)
           │
    ┌──────┴──────┐
    │             │
┌───▼──────────┐ ┌▼──────────────┐
│   Alumno     │ │   Docente     │
├──────────────┤ ├───────────────┤
│ - direccion  │ │ - especialidad│
│ - telefono   │ │   : char[100] │
│ - email      │ ├───────────────┤
│ - fechaNac   │ │ + mostrar()   │
├──────────────┤ └───────────────┘
│ + mostrar()  │
└──────────────┘


┌──────────────────┐
│    Materia       │
├──────────────────┤
│ - idMateria: int │
│ - nombre: char[] │
│ - cuatrimestre:  │
│   int            │
│ - eliminado: bool│
├──────────────────┤
│ + getIdMateria() │
│ + getNombre()    │
│ + mostrar()      │
└──────────────────┘


┌──────────────────────┐
│     Comision         │
├──────────────────────┤
│ - idComision: int    │
│ - idMateria: int     │
│ - turno: char[10]    │
│ - modalidad: char[10]│
│ - cuatrimestre: int  │
│ - anio: int          │
│ - legajoDocente: int │
│ - eliminado: bool    │
├──────────────────────┤
│ + getIdComision()    │
│ + getIdMateria()     │
│ + getTurno()         │
│ + mostrar()          │
└──────────────────────┘


┌──────────────────────────┐
│        Examen            │
├──────────────────────────┤
│ - idExamen: int          │
│ - idMateria: int         │
│ - legajoAlumno: int      │
│ - tipo: char[15]         │
│ - numeroParcial: int     │
│ - fecha: Fecha           │
│ - nota: int              │
│ - corregido: bool        │
│ - eliminado: bool        │
├──────────────────────────┤
│ + getTipo()              │
│ + getNumeroParcial()     │
│ + getNota()              │
│ + corregir(nota: int)    │
│ + mostrar()              │
└──────────────────────────┘


┌──────────────────────────┐
│  InscripcionComision     │
├──────────────────────────┤
│ - legajoAlumno: int      │
│ - idComision: int        │
│ - fecha: Fecha           │
│ - estado: int            │
│   (0=Activa, 1=Pend,     │
│    2=Baja)               │
├──────────────────────────┤
│ + getEstado()            │
│ + setEstado(estado: int) │
│ + mostrar()              │
└──────────────────────────┘


┌──────────────────────┐
│   Correlativa        │
├──────────────────────┤
│ - idMateriaObjetivo  │
│   : int              │
│ - idMateriaRequisito │
│   : int              │
│ - eliminado: bool    │
├──────────────────────┤
│ + getIdMateriaObj()  │
│ + getIdMateriaReq()  │
│ + mostrar()          │
└──────────────────────┘
```

### 6.2 Clases de Managers (Lógica de Negocio)

```
┌────────────────────────────┐
│     ManagerExamen          │
├────────────────────────────┤
│ - archivoExamen            │
├────────────────────────────┤
│ + cargarParcial()          │
│ + cargarRecuperatorio()    │
│ + cargarFinal()            │
│ + estaPromocionado()       │
│ + estaRegular()            │
│ + estaLibre()              │
│ + puedeRendirFinal()       │
│ + promedioConReglas()      │
│ + mostrarHistorial()       │
│ + recalcularCondicion()    │
└────────────────────────────┘


┌────────────────────────────┐
│     ManagerAlumno          │
├────────────────────────────┤
│ - archivoAlumnos           │
│ - archivoMaterias          │
│ - archivoInscripciones     │
│ - examenManager            │
├────────────────────────────┤
│ + registrarAlumno()        │
│ + listarAlumnos()          │
│ + cumpleCorrelativas()     │
│ + mostrarHistorialNotas()  │
│ + mostrarMateriasAprobadas│
│ + mostrarMateriasPend()    │
│ + inscribirseAComision()   │
│ + inscribirseAFinal()      │
│ + verCondicionMateria()    │
└────────────────────────────┘


┌────────────────────────────┐
│    ManagerReportes         │
├────────────────────────────┤
│ - archivoAlumnos           │
│ - archivoMaterias          │
│ - archivoComisiones        │
│ - archivoExamenes          │
│ - managerExamen            │
├────────────────────────────┤
│ + reporteRendimiento()     │
│ + listadoAlumnosPorCom()   │
│ + estadisticasPorMateria() │
│ + finalesPendientes()      │
│ + reporteComisionesCupo()  │
│ + rankingAlumnos()         │
│ + calendarioFinales()      │
│ + alumnosEnRiesgo()        │
│ + cargaHorariaDocentes()   │
│ ... (13 reportes total)    │
└────────────────────────────┘
```

### 6.3 Clases de Archivos (Acceso a Datos)

```
┌────────────────────────────┐
│    ArchivoAlumno           │
├────────────────────────────┤
│ - nombreArchivo: string    │
│ - archivo: FILE*           │
├────────────────────────────┤
│ + agregarRegistro()        │
│ + leerRegistro(pos: int)   │
│ + modificarRegistro()      │
│ + buscarRegistro(id: int)  │
│ + contarRegistros()        │
└────────────────────────────┘

(Similar para ArchivoExamen,
 ArchivoMateria, ArchivoComision,
 etc.)
```

### 6.4 Clases de Utilidades

```
┌──────────────────────────┐
│      Validacion          │
├──────────────────────────┤
│ (funciones estáticas)    │
├──────────────────────────┤
│ + validarEntero()        │
│ + validarEnteroEnRango() │
│ + validarCadena()        │
│ + validarEmail()         │
│ + desearGuardar()        │
└──────────────────────────┘


┌──────────────────────────┐
│        utils.h           │
├──────────────────────────┤
│ (funciones globales)     │
├──────────────────────────┤
│ + calcularPromedioAlu()  │
│ + contarMateriasAprob()  │
│ + contarMateriasProm()   │
│ + contarMateriasReg()    │
│ + contarMateriasLibres() │
│ + contarInscriptosEn()   │
│ + clearScreen()          │
│ + pauseScreen()          │
└──────────────────────────┘
```

---

## 7. Casos de Uso Principales

### 7.1 CU-01: Alumno Cursa una Materia

**Actor**: Alumno

**Precondiciones:**
- El alumno existe en el sistema
- Existe una comisión abierta de la materia
- El alumno cumple correlativas
- Hay cupo disponible

**Flujo Principal:**
1. Alumno accede al sistema con su legajo
2. Selecciona "Inscribirse a Comisión"
3. Sistema muestra materias disponibles
4. Alumno selecciona materia
5. Sistema valida correlativas
6. Sistema muestra comisiones disponibles
7. Alumno selecciona comisión
8. Sistema registra inscripción (estado: ACTIVA)
9. Sistema confirma inscripción

**Flujo Alternativo:**
- 5a. No cumple correlativas → Sistema rechaza con mensaje
- 7a. Comisión llena → Sistema muestra mensaje y otras opciones

### 7.2 CU-02: Docente Carga Parcial

**Actor**: Docente

**Precondiciones:**
- El docente tiene comisiones asignadas
- Existe el alumno en la comisión

**Flujo Principal:**
1. Docente accede al sistema
2. Selecciona "Cargar Parcial"
3. Ingresa legajo del alumno
4. Ingresa ID de comisión
5. Sistema valida inscripción del alumno
6. Ingresa nota (0-10)
7. Sistema determina número de parcial automáticamente
8. Sistema guarda examen
9. Sistema confirma carga exitosa

**Flujo Alternativo:**
- 5a. Alumno no inscrito → Sistema rechaza
- 5b. Ya tiene 2 parciales → Sistema rechaza

### 7.3 CU-03: Alumno Usa Recuperatorio

**Actor**: Docente (carga la nota)

**Precondiciones:**
- Alumno tiene al menos un parcial desaprobado (< 4)

**Flujo Principal:**
1. Docente selecciona "Cargar Recuperatorio"
2. Ingresa legajo del alumno
3. Ingresa ID de comisión
4. Sistema busca parciales desaprobados
5. Sistema identifica qué parcial recupera
6. Docente ingresa nota
7. Sistema guarda recuperatorio
8. **Sistema recalcula condición automáticamente**
9. Sistema confirma carga

**Postcondición:**
- El recuperatorio reemplaza la nota del parcial
- La condición académica se actualiza
- Si ahora promedio >= 4 → pasa de LIBRE a REGULAR
- **Si usó recuperatorio → NO puede promocionar (aunque promedio >= 7)**

### 7.4 CU-04: Sistema Determina Condición Académica

**Actor**: Sistema (automático)

**Precondiciones:**
- Alumno tiene al menos un examen registrado

**Flujo Principal:**
1. Sistema busca todos los parciales del alumno en la materia
2. Sistema busca si hay recuperatorios
3. Sistema aplica regla de reemplazo:
   ```
   NotaFinalP1 = (RecuP1 existe) ? RecuP1 : NotaP1
   NotaFinalP2 = (RecuP2 existe) ? RecuP2 : NotaP2
   ```
4. Sistema verifica si tiene ambos parciales
5. Sistema calcula promedio:
   ```
   Promedio = (NotaFinalP1 + NotaFinalP2) / 2
   ```
6. Sistema determina condición:
   ```
   Si usó recuperatorio:
     → REGULAR (aunque promedio >= 7)
   Sino:
     Si promedio >= 7:
       → PROMOCIONADO
     Sino si promedio >= 4:
       → REGULAR
     Sino:
       → LIBRE
   ```

**Casos Especiales:**
```
Caso A: P1=8, P2=7, sin recuperatorio
  → Promedio: 7.5
  → Condición: PROMOCIONADO

Caso B: P1=3, RecuP1=9, P2=8, usó recuperatorio
  → Promedio: 8.5
  → Condición: REGULAR (usó recuperatorio)

Caso C: P1=6, P2=5, sin recuperatorio
  → Promedio: 5.5
  → Condición: REGULAR

Caso D: P1=3, P2=2
  → Promedio: 2.5
  → Condición: LIBRE
```

### 7.5 CU-05: Alumno Intenta Rendir Final

**Actor**: Alumno

**Precondiciones:**
- Alumno existe en el sistema
- Tiene exámenes registrados

**Flujo Principal:**
1. Alumno selecciona "Inscribirse a Mesa de Examen"
2. Selecciona materia
3. **Sistema ejecuta validaciones:**
   a. ¿Está inscrito en una comisión? ✅
   b. ¿Cumple correlativas? ✅
   c. ¿Está PROMOCIONADO? ❌ (debe ser NO)
   d. ¿Está LIBRE? ❌ (debe ser NO)
   e. ¿Está REGULAR? ✅ (debe ser SI)
   f. ¿Ya tiene final aprobado? ❌ (debe ser NO)
4. Si todas las validaciones pasan → Sistema permite inscripción
5. Alumno confirma inscripción
6. Sistema registra inscripción a mesa

**Flujos Alternativos:**
- 3c. Está promocionado → "Está PROMOCIONADO. No necesita rendir final"
- 3d. Está libre → "Está LIBRE. Debe cursar y regularizar primero"
- 3e. No está regular → "Debe regularizar la materia primero"

### 7.6 CU-06: Administrador Genera Reporte

**Actor**: Administrador

**Precondiciones:**
- Existen datos en el sistema

**Flujo Principal:**
1. Admin selecciona "Sistema de Reportes"
2. Sistema muestra menú con 13 reportes
3. Admin selecciona reporte (ej: "Alumnos en Riesgo")
4. Si requiere parámetros:
    - Admin ingresa legajo/ID materia/etc.
5. Sistema procesa datos
6. Sistema muestra reporte formateado
7. Admin puede exportar a CSV (opcional)

**Ejemplo de Reportes:**
- Rendimiento académico por alumno
- Ranking por promedio
- Finales pendientes
- Estadísticas por materia
- Alumnos en riesgo académico

---

## 8. Implementación Técnica

### 8.1 Tecnologías y Herramientas

| Componente | Tecnología |
|------------|------------|
| Lenguaje | C++20 |
| Build System | CMake 3.16 |
| Compilador | GCC 11+ / Clang 14+ |
| Testing | GoogleTest |
| Persistencia | Archivos binarios (.dat) |
| IDE Sugerido | CLion, VS Code, Visual Studio |

### 8.2 Compilación

```bash
# Configuración inicial
mkdir build && cd build
cmake ..

# Compilación
make

# Ejecución
./TP_UTN_Campus
```

### 8.3 Estructura del Proyecto

```
TP-UTN-Campus/
├── CMakeLists.txt
├── README.md
├── INFORME_ACADEMICO.md
│
├── Entidades/          (Clases del dominio)
├── Archivos/           (Acceso a datos)
├── Managers/           (Lógica de negocio)
├── Menus/              (Presentación)
├── Utils/              (Utilidades)
│
├── *.dat               (Archivos de datos)
├── tests/              (Tests unitarios)
└── main.cpp
```

### 8.4 Principios de Diseño Aplicados

#### SOLID
- **S**ingle Responsibility: Cada clase tiene una responsabilidad clara
- **O**pen/Closed: Extensible mediante herencia (Persona → Alumno/Docente)
- **L**iskov Substitution: Polimorfismo correcto
- **I**nterface Segregation: Interfaces específicas por rol
- **D**ependency Inversion: Managers dependen de abstracciones (Archivos)

#### DRY (Don't Repeat Yourself)
- Funciones auxiliares centralizadas en `utils.h/cpp`
- Validaciones reutilizables en `Validacion`
- Clases base para comportamiento común

#### KISS (Keep It Simple)
- Código legible y autodocumentado
- Nombres descriptivos
- Funciones cortas y específicas

### 8.5 Validaciones Implementadas

#### Input del Usuario
```cpp
// Validar entero
int edad = Validacion::validarEntero("Ingrese edad: ");

// Validar rango
int nota = Validacion::validarEnteroEnRango("Nota (0-10): ", 0, 10);

// Validar cadena no vacía
string nombre = Validacion::validarCadena("Nombre: ");
```

#### Reglas de Negocio
```cpp
// Validar correlativas
if (!ManagerAlumno::cumpleCorrelativas(legajo, idMateria)) {
    cout << "ERROR: No cumple correlativas";
    return false;
}

// Validar condición para final
if (!ManagerExamen::puedeRendirFinal(legajo, idComision)) {
    // Mensaje específico según el motivo
    return false;
}

// Validar inscripción
if (!ManagerInscripcionComision::estaInscripto(legajo, idComision)) {
    cout << "ERROR: No está inscrito";
    return false;
}
```

---

## 9. Conclusiones

### 9.1 Logros del Proyecto

1. **Sistema Completo y Funcional**
    - 8 archivos de datos (.dat) con persistencia
    - 13 reportes estadísticos
    - 3 perfiles de usuario (Alumno/Docente/Admin)

2. **Reglas de Negocio Complejas**
    - Sistema de promoción directa
    - Recuperatorios que reemplazan notas
    - Validación de correlativas
    - Cálculo automático de condiciones

3. **Arquitectura Escalable**
    - Patrón Repository en 3 capas
    - Separación clara de responsabilidades
    - Código modular y reutilizable

4. **Buenas Prácticas**
    - Principios SOLID
    - Validación exhaustiva
    - Documentación completa
    - Tests unitarios

### 9.2 Desafíos Enfrentados

1. **Gestión de Recuperatorios**
    - Implementar reemplazo de notas (no promedio)
    - Garantizar que uso de recuperatorio impide promoción

2. **Validaciones Complejas**
    - Múltiples condiciones para rendir final
    - Verificación de correlativas en cadena
    - Estado de inscripciones con flujo de aprobación

3. **Persistencia de Datos**
    - Archivos binarios con estructuras complejas
    - Mantenimiento de integridad referencial manual
    - Búsquedas eficientes en archivos grandes

### 9.3 Posibles Mejoras Futuras

1. **Base de Datos Relacional**
    - Migrar de archivos .dat a SQLite/MySQL
    - Integridad referencial automática
    - Consultas más eficientes

2. **Interfaz Gráfica**
    - GUI con Qt o similar
    - Mejor experiencia de usuario

3. **Sistema de Notificaciones**
    - Email para inscripciones
    - Recordatorios de exámenes
    - Alertas de cambios de estado

4. **Historial de Cambios**
    - Auditoría completa
    - Quién modificó qué y cuándo

5. **Integración con Servicios Externos**
    - Sistema de pagos
    - Plataforma educativa (Moodle)
    - Sistema de bibliotecas

### 9.4 Aprendizajes

1. **Diseño de Software**
    - Importancia de la arquitectura en capas
    - Ventajas del patrón Repository
    - Separación de responsabilidades

2. **C++ Moderno**
    - Uso de STL (vector, algorithm)
    - Gestión de memoria
    - Herencia y polimorfismo

3. **Reglas de Negocio**
    - Complejidad del sistema académico real
    - Importancia de validaciones exhaustivas
    - Casos especiales y excepciones

4. **Trabajo en Equipo**
    - Versionado con Git
    - Documentación clara
    - Código autodocumentado

---

## 📚 Bibliografía

- **C++20 Documentation**: https://en.cppreference.com/
- **CMake Documentation**: https://cmake.org/documentation/
- **GoogleTest**: https://google.github.io/googletest/
- **Clean Code** - Robert C. Martin
- **Design Patterns** - Gang of Four

---

## 📎 Anexos

### Anexo A: Comandos de Compilación

```bash
# Compilar
cd build
cmake ..
make

# Ejecutar
./TP_UTN_Campus

# Tests
./runTests

# Inicializar datos
./inicializar_datos
```

### Anexo B: Ejemplos de Uso

Ver `README.md` y `REPORTES.md` para ejemplos detallados.

### Anexo C: Archivos del Proyecto

Ver sección "Estructura de Archivos" en `README.md`.

---

**Fin del Informe Académico**

---
