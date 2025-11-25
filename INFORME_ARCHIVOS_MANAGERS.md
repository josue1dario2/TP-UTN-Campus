# 📁 INFORME: Archivos y Managers del Sistema

---

## 🎯 Arquitectura del Proyecto

El proyecto sigue el **Patrón Repository** con 3 capas:

```
┌─────────────────────────────────────┐
│  PRESENTACIÓN (main.cpp, menús)    │  ← Interfaz con el usuario
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│  LÓGICA DE NEGOCIO (Managers)      │  ← Validaciones y reglas
└─────────────────────────────────────┘
              ↓
┌─────────────────────────────────────┐
│  ACCESO A DATOS (Archivos)         │  ← Persistencia en .dat
└─────────────────────────────────────┘
```

---

## 📂 CAPA 1: ARCHIVOS (Persistencia)

Los **Archivos** se encargan de **leer y escribir datos en archivos binarios (.dat)**. No tienen lógica de negocio.

### ArchivoAlumno
**Archivo:** `ArchivoAlumno.h` / `ArchivoAlumno.cpp`
**Archivo de datos:** `Alumnos.dat`

**Responsabilidad:** Persistencia de datos de alumnos.

**Métodos principales:**
- `agregarRegistro(Alumno)` → Guardar nuevo alumno
- `leerRegistro(int pos)` → Leer alumno por posición
- `buscarRegistro(int legajo)` → Buscar por legajo
- `modificarRegistro(Alumno, int pos)` → Actualizar alumno
- `contarRegistros()` → Cantidad total de alumnos

**Qué hace:** CRUD básico sobre archivo binario de alumnos.

---

### ArchivoMateria
**Archivo:** `ArchivoMateria.h` / `ArchivoMateria.cpp`
**Archivo de datos:** `Materias.dat`

**Responsabilidad:** Persistencia de materias del plan de estudios.

**Métodos principales:**
- `agregarRegistro(Materia)`
- `leerRegistro(int pos)`
- `buscarRegistro(int idMateria)`
- `modificarRegistro(Materia, int pos)`
- `contarRegistros()`

**Qué hace:** CRUD básico sobre archivo binario de materias.

---

### ArchivoComision
**Archivo:** `ArchivoComision.h` / `ArchivoComision.cpp`
**Archivo de datos:** `Comisiones.dat`

**Responsabilidad:** Persistencia de comisiones (cursos).

**Atributos importantes de Comisión:**
- `idComision` → Identificador único
- `idMateria` → Materia que dicta esta comisión
- `legajoDocente` → Docente asignado
- `cuatrimestre` → Período académico

**Qué hace:** CRUD básico sobre archivo binario de comisiones.

---

### ArchivoInscripcionComision
**Archivo:** `ArchivoInscripcionComision.h` / `ArchivoInscripcionComision.cpp`
**Archivo de datos:** `InscripcionesComision.dat`

**Responsabilidad:** Persistencia de inscripciones de alumnos a comisiones.

**Atributos importantes de InscripcionComision:**
- `legajoAlumno` → Alumno inscripto
- `idComision` → Comisión en la que se inscribió
- `fecha` → Fecha de inscripción
- `estado` → 0=Activo, 1=Pendiente baja, 2=Baja definitiva

**Método especial:**
- `buscarRegistro(int legajo, int idComision)` → Buscar inscripción específica

**Qué hace:** CRUD sobre inscripciones alumno-comisión con estados.

---

### ArchivoExamen
**Archivo:** `ArchivoExamen.h` / `ArchivoExamen.cpp`
**Archivo de datos:** `Examenes.dat`

**Responsabilidad:** Persistencia de todos los exámenes (parciales, recuperatorios, finales).

**Atributos importantes de Examen:**
- `idMateria` → Materia del examen
- `legajoAlumno` → Alumno que rindió
- `tipo` → "Parcial", "Recuperatorio" o "Final"
- `numeroParcial` → 1 o 2 (para parciales/recuperatorios)
- `nota` → Calificación (0-10)
- `fecha` → Fecha del examen
- `corregido` → Si fue corregido

**Qué hace:** CRUD sobre exámenes con múltiples tipos.

---

### ArchivoDocente
**Archivo:** `ArchivoDocente.h` / `ArchivoDocente.cpp`
**Archivo de datos:** `Docentes.dat`

**Responsabilidad:** Persistencia de docentes.

**Herencia:** Extiende `ArchivoPersona` (comparte estructura de Persona).

**Qué hace:** CRUD básico sobre archivo binario de docentes.

---

### ArchivoCarrera
**Archivo:** `ArchivoCarrera.h` / `ArchivoCarrera.cpp`
**Archivo de datos:** `Carreras.dat`

**Responsabilidad:** Persistencia de carreras universitarias.

**Atributos importantes de Carrera:**
- `idCarrera` → Identificador único
- `nombre` → Nombre de la carrera
- `duracionAnios` → Duración en años
- `resolucion` → Número de resolución ministerial

**Qué hace:** CRUD básico sobre archivo binario de carreras.

---

### ArchivoCorrelativa
**Archivo:** `ArchivoCorrelativa.h` / `ArchivoCorrelativa.cpp`
**Archivo de datos:** `Correlativas.dat`

**Responsabilidad:** Persistencia de correlativas (requisitos entre materias).

**Atributos importantes de Correlativa:**
- `idMateriaObjetivo` → Materia que quiere cursar
- `idMateriaRequisito` → Materia que debe tener aprobada

**Ejemplo:**
```
idMateriaObjetivo: 5 (Programación III)
idMateriaRequisito: 2 (Programación II)
→ Para cursar Programación III, debe tener aprobada Programación II
```

**Qué hace:** CRUD sobre relaciones de correlatividad.

---

### ArchivoPersona
**Archivo:** `ArchivoPersona.h` / `ArchivoPersona.cpp`

**Responsabilidad:** Clase base para archivos de personas (Alumno, Docente).

**Atributos compartidos:**
- Legajo
- Nombre, Apellido
- DNI, Email, Teléfono

**Qué hace:** Proporciona estructura común para personas. Usa **herencia**.

---

## 💼 CAPA 2: MANAGERS (Lógica de Negocio)

Los **Managers** contienen la **lógica de validaciones y reglas de negocio**. Usan los Archivos para persistencia.

### ManagerAlumno
**Archivo:** `ManagerAlumno.h` / `ManagerAlumno.cpp`

**Responsabilidad:** Gestión completa de alumnos y validación de correlativas.

**Métodos principales:**

#### Gestión básica:
- `registrarAlumno()` → Dar de alta un nuevo alumno
- `listarAlumnos()` → Mostrar todos los alumnos
- `buscarAlumno(int legajo)` → Buscar por legajo
- `editarDatos(int legajo)` → Modificar datos del alumno

#### Validación académica:
- `cumpleCorrelativas(int legajo, int idMateria)` → **CRÍTICO**
  - Verifica si el alumno tiene TODAS las correlativas aprobadas
  - Usado por: inscripción a comisión, rendir final

#### Consultas:
- `mostrarHistorialNotas(int legajo)` → Ver todas las notas del alumno
- `mostrarMateriasAprobadas(int legajo)` → Materias con final >= 4
- `mostrarMateriasPendientes(int legajo)` → Materias que puede cursar

**Por qué es importante:**
- ✅ Centraliza validación de correlativas
- ✅ Maneja el ciclo de vida completo del alumno
- ✅ Proporciona consultas académicas

---

### ManagerMateria
**Archivo:** `ManagerMateria.h` / `ManagerMateria.cpp`

**Responsabilidad:** Gestión del plan de estudios (materias).

**Métodos principales:**
- `crearMateria()` → Alta de nueva materia
- `listarMaterias()` → Mostrar todas las materias
- `modificarMateria()` → Editar datos de materia
- `borrar()` → Baja lógica de materia

**Qué hace:** CRUD de materias con validaciones básicas.

---

### ManagerComision
**Archivo:** `ManagerComision.h` / `ManagerComision.cpp`

**Responsabilidad:** Gestión de comisiones (cursos dictados).

**Métodos principales:**
- `crearComision()` → Alta de nueva comisión
  - Valida que exista la materia
  - Valida que exista el docente
- `listarComisiones()` → Mostrar todas las comisiones
- `modificarComision()` → Editar comisión
- `borrar()` → Baja lógica
- `existeComision(int idComision)` → Validación de existencia

**Por qué es importante:**
- ✅ Valida que materia y docente existan antes de crear comisión
- ✅ Usado por inscripciones para validar comisión

---

### ManagerInscripcionComision
**Archivo:** `ManagerInscripcionComision.h` / `ManagerInscripcionComision.cpp`

**Responsabilidad:** Gestión de inscripciones de alumnos a comisiones.

**Métodos principales:**

#### Alta:
- `cargar()` → **MÉTODO CRÍTICO** - Inscribir alumno a comisión
  - Valida que exista la comisión
  - Valida que no esté ya inscripto (evita duplicados)
  - Valida correlativas → llama a `ManagerAlumno::cumpleCorrelativas()`
  - Valida que no haya aprobado ya la materia

#### Consultas:
- `estaInscripto(int legajo, int idComision)` → Verificar inscripción activa
  - Usado por: cargar exámenes, rendir final

#### Gestión de bajas:
- `borrar()` → Solicitar baja (estado = 1, pendiente)
- `procesarSolicitudesPendientes()` → Administrador aprueba/rechaza bajas

**Flujo de baja:**
```
Alumno solicita baja → estado = 1 (Pendiente)
Administrador aprueba → estado = 2 (Baja definitiva)
Administrador rechaza → estado = 0 (Vuelve a Activa)
```

**Por qué es importante:**
- ✅ Implementa todas las validaciones para cursar
- ✅ Evita inscripciones duplicadas
- ✅ Valida correlativas antes de permitir inscripción

---

### ManagerExamen
**Archivo:** `ManagerExamen.h` / `ManagerExamen.cpp`

**Responsabilidad:** Gestión de exámenes y validación de condiciones académicas.

**Métodos de alta:**
- `cargarParcial(int legajo, int idComision, int nota)`
  - Valida inscripción en comisión
  - Valida que no tenga ya los 2 parciales
  - Determina automáticamente si es Parcial 1 o 2

- `cargarRecuperatorio(int legajo, int idComision, int nota)`
  - Valida que tenga parciales desaprobados (nota < 4)
  - Recupera el último parcial desaprobado

- `cargarFinal(int legajo, int idComision, int nota)`
  - Llama a `puedeRendirFinal()` para validar

**Métodos de validación académica:**

- `puedeRendirFinal(int legajo, int idComision)` → **MÉTODO CRÍTICO**
  - Valida inscripción
  - Valida correlativas
  - Valida que NO esté promocionado
  - Valida que NO esté libre (debe estar regular)
  - Valida que no haya aprobado ya el final

- `estaPromocionado(int legajo, int idComision)` → **REGLA DE NEGOCIO**
  - Tiene los 2 parciales
  - NO usó recuperatorio
  - Promedio >= 7

- `estaRegular(int legajo, int idComision)` → **REGLA DE NEGOCIO**
  - NO está promocionado
  - Tiene los 2 parciales (con o sin recuperatorios)
  - Promedio >= 4 (aplicando recuperatorios)

- `estaLibre(int legajo, int idComision)` → **REGLA DE NEGOCIO**
  - NO está promocionado Y NO está regular
  - (Por descarte)

**Métodos auxiliares:**
- `promedioConReglas(int legajo, int idMateria)` → Calcula promedio aplicando recuperatorios
- `mostrarHistorial(int legajo)` → Ver todos los exámenes del alumno
- `recalcularCondicion(int legajo, int idComision)` → Mostrar condición actual

**Por qué es importante:**
- ✅ Implementa TODAS las reglas académicas
- ✅ Valida condiciones para rendir final
- ✅ Calcula estados académicos (promocionado/regular/libre)
- ✅ Usado por reportes para estadísticas

---

### ManagerDocente
**Archivo:** `ManagerDocente.h` / `ManagerDocente.cpp`

**Responsabilidad:** Gestión de docentes.

**Métodos principales:**
- `cargar()` → Alta de nuevo docente
- `listar()` → Mostrar todos los docentes
- `borrar()` → Baja lógica de docente

**Qué hace:** CRUD de docentes con validaciones básicas.

---

### ManagerCarrera
**Archivo:** `ManagerCarrera.h` / `ManagerCarrera.cpp`

**Responsabilidad:** Gestión de carreras universitarias.

**Métodos principales:**
- `cargar()` → Alta de nueva carrera
- `listar()` → Mostrar todas las carreras
- `borrar()` → Baja lógica de carrera

**Qué hace:** CRUD de carreras.

---

### ManagerCorrelativa
**Archivo:** `ManagerCorrelativa.h` / `ManagerCorrelativa.cpp`

**Responsabilidad:** Gestión de correlativas entre materias.

**Métodos principales:**
- `cargar()` → Crear correlativa
  - Valida que ambas materias existan
  - Valida que no se cree correlativa duplicada

- `listar()` → Mostrar todas las correlativas
- `borrar()` → Eliminar correlativa
- `tieneCorrelativas(int idMateria)` → Verifica si una materia tiene requisitos
- `listarCorrelativasDe(int idMateria)` → Mostrar correlativas de una materia

**Por qué es importante:**
- ✅ Mantiene el grafo de correlativas del plan de estudios
- ✅ Usado por `ManagerAlumno::cumpleCorrelativas()`

---

### ManagerReportes
**Archivo:** `ManagerReportes.h` / `ManagerReportes.cpp`

**Responsabilidad:** Generación de reportes estadísticos y académicos.

**Contiene:** 13 reportes organizados por prioridad.

#### Reportes de Alta Prioridad:
1. `reporteRendimientoAcademico(int legajo)`
   - Promedio general del alumno
   - Materias aprobadas, promocionadas, regulares, libres
   - Estado general (EXCELENTE, MUY BUENO, REGULAR, EN RIESGO)

2. `listadoAlumnosPorComision(int idComision)`
   - Todos los alumnos de una comisión con sus estados

3. `estadisticasPorMateria(int idMateria)`
   - Inscriptos, promocionados, regulares, libres
   - Promedio de la materia
   - Tasa de aprobación

4. `finalesPendientesPorAlumno(int legajo)`
   - Materias con final pendiente (regular sin final aprobado)

5. `reporteComisionesPorCupo()`
   - Estado de ocupación de todas las comisiones

#### Reportes de Media Prioridad:
6. `rankingAlumnosPorPromedio()` → Top 20 alumnos
7. `calendarioFinales()` → Alumnos que deben rendir final por materia
8. `historialNotasPorMateria(int legajo, int idMateria)` → Notas detalladas
9. `alumnosEnRiesgoAcademico()` → Alumnos con >50% libres o promedio < 4
10. `cargaHorariaDocentes()` → Comisiones y alumnos por docente

#### Reportes Analíticos:
11. `tasaAprobacionPorCuatrimestre()` → Estadísticas globales
12. `materiasConMayorIndiceLibre()` → Top 10 materias más difíciles
13. `tiempoPromedioCarrera()` → Análisis de avance

**Composición (atributos):**
```cpp
ArchivoAlumno _archivoAlumnos;
ArchivoMateria _archivoMaterias;
ArchivoComision _archivoComisiones;
ArchivoInscripcionComision _archivoInscripciones;
ArchivoExamen _archivoExamenes;
ArchivoDocente _archivoDocentes;
ManagerExamen _managerExamen;
```

**Usa funciones auxiliares de `utils.h`:**
- `calcularPromedioAlumno(int legajo)`
- `contarMateriasAprobadas(int legajo)`
- `contarMateriasPromocionadas(int legajo)`
- `contarMateriasRegulares(int legajo)`
- `contarMateriasLibres(int legajo)`
- `contarInscriptosEnComision(int idComision)`

**Por qué es importante:**
- ✅ Proporciona visibilidad del estado académico
- ✅ Ayuda a identificar problemas (alumnos en riesgo, materias difíciles)
- ✅ Usa delegación para cálculos complejos

---

## 🔗 DEPENDENCIAS ENTRE MANAGERS

### Tabla de Dependencias

| Manager | Depende de | Para qué |
|---------|------------|----------|
| `ManagerInscripcionComision` | `ManagerComision` | Validar que exista la comisión |
| `ManagerInscripcionComision` | `ManagerAlumno` | Validar correlativas |
| `ManagerInscripcionComision` | `ArchivoExamen` | Verificar si ya aprobó la materia |
| `ManagerExamen` | `ManagerInscripcionComision` | Validar inscripción activa |
| `ManagerExamen` | `ManagerAlumno` | Validar correlativas para final |
| `ManagerAlumno` | `ManagerCorrelativa` | Verificar correlativas |
| `ManagerAlumno` | `ArchivoExamen` | Buscar exámenes aprobados |
| `ManagerReportes` | **Todos los archivos** | Generar estadísticas |
| `ManagerReportes` | `ManagerExamen` | Validar condiciones académicas |

---

## 📊 RESUMEN POR FUNCIONALIDAD

### 1. Inscripción a Comisión
**Flujo:**
```
Usuario → ManagerInscripcionComision::cargar()
           ├→ ManagerComision::existeComision()
           ├→ ManagerInscripcionComision::estaInscripto()
           ├→ ManagerAlumno::cumpleCorrelativas()
           │   └→ ManagerCorrelativa::tieneCorrelativas()
           │   └→ ArchivoExamen::leerRegistro()
           └→ ArchivoInscripcionComision::agregarRegistro()
```

**Archivos involucrados:**
- ArchivoComision (validar comisión)
- ArchivoInscripcionComision (guardar inscripción)
- ArchivoCorrelativa (obtener correlativas)
- ArchivoExamen (verificar correlativas aprobadas)

**Managers involucrados:**
- ManagerInscripcionComision (coordinador)
- ManagerComision (validar existencia)
- ManagerAlumno (validar correlativas)
- ManagerCorrelativa (obtener correlativas)

---

### 2. Rendir Final
**Flujo:**
```
Usuario → ManagerExamen::cargarFinal()
           └→ ManagerExamen::puedeRendirFinal()
               ├→ ManagerInscripcionComision::estaInscripto()
               ├→ ManagerAlumno::cumpleCorrelativas()
               ├→ ManagerExamen::estaPromocionado()
               ├→ ManagerExamen::estaLibre()
               │   └→ ManagerExamen::estaRegular()
               └→ ArchivoExamen::agregarRegistro()
```

**Archivos involucrados:**
- ArchivoComision (obtener materia)
- ArchivoInscripcionComision (validar inscripción)
- ArchivoCorrelativa (validar correlativas)
- ArchivoExamen (guardar final, verificar estado)

**Managers involucrados:**
- ManagerExamen (coordinador y validaciones)
- ManagerInscripcionComision (validar inscripción)
- ManagerAlumno (validar correlativas)

---

### 3. Generar Reporte de Rendimiento
**Flujo:**
```
Usuario → ManagerReportes::reporteRendimientoAcademico()
           ├→ ArchivoAlumno::leerRegistro()
           ├→ calcularPromedioAlumno() [utils]
           │   └→ ArchivoExamen::leerRegistro()
           ├→ contarMateriasAprobadas() [utils]
           ├→ contarMateriasPromocionadas() [utils]
           ├→ contarMateriasRegulares() [utils]
           └→ contarMateriasLibres() [utils]
```

**Archivos involucrados:**
- ArchivoAlumno (datos del alumno)
- ArchivoExamen (todas las notas)
- ArchivoMateria (total de materias)

**Funciones auxiliares:**
- utils.h (cálculos estadísticos)

---

## 🎯 RESPONSABILIDADES CLAVE

### Archivos
✅ **Solo persistencia** (CRUD básico)
✅ **No tienen lógica de negocio**
✅ **Leen/escriben archivos .dat**
✅ **No validan reglas académicas**

### Managers
✅ **Lógica de negocio y validaciones**
✅ **Coordinan múltiples archivos**
✅ **Implementan reglas académicas**
✅ **Delegan a otros managers especializados**
✅ **Proporcionan interfaces claras al usuario**

---

## 💡 CONCEPTOS POO APLICADOS

### Separación de Responsabilidades
```
ARCHIVO → Persistencia
MANAGER → Validaciones y lógica
```

### Composición
```cpp
class ManagerReportes {
    ArchivoAlumno _archivoAlumnos;  // "tiene un"
    ManagerExamen _managerExamen;   // "tiene un"
};
```

### Delegación
```cpp
// ManagerInscripcionComision delega validación a ManagerAlumno
if (!manAlumno.cumpleCorrelativas(legajo, idMateria)) {
    // ...
}
```

### Encapsulamiento
```cpp
class ManagerAlumno {
private:
    ArchivoAlumno _archivoAlumnos;  // Oculto
public:
    bool cumpleCorrelativas();  // Expuesto
};
```

---

## 📋 LISTA COMPLETA

### 9 Archivos
1. ArchivoAlumno → Alumnos.dat
2. ArchivoMateria → Materias.dat
3. ArchivoComision → Comisiones.dat
4. ArchivoInscripcionComision → InscripcionesComision.dat
5. ArchivoExamen → Examenes.dat
6. ArchivoDocente → Docentes.dat
7. ArchivoCarrera → Carreras.dat
8. ArchivoCorrelativa → Correlativas.dat
9. ArchivoPersona → Clase base (herencia)

### 9 Managers
1. ManagerAlumno → Gestión de alumnos + validación correlativas
2. ManagerMateria → Gestión de materias
3. ManagerComision → Gestión de comisiones
4. ManagerInscripcionComision → Inscripciones con validaciones
5. ManagerExamen → Exámenes + condiciones académicas
6. ManagerDocente → Gestión de docentes
7. ManagerCarrera → Gestión de carreras
8. ManagerCorrelativa → Gestión de correlativas
9. ManagerReportes → 13 reportes estadísticos

---

## 🔍 Para Estudiar

**Pregunta clave:** ¿Por qué separar Archivos y Managers?

**Respuesta:**
1. **Responsabilidad Única:** Cada clase tiene una función clara
2. **Mantenibilidad:** Cambiar persistencia (de .dat a SQL) sin tocar Managers
3. **Testeo:** Probar lógica de negocio sin acceso a archivos reales
4. **Claridad:** Código más legible y organizado
5. **Patrón Repository:** Separar lógica de negocio de acceso a datos

---

## 📌 Resumen Ejecutivo

| Componente | Cantidad | Responsabilidad |
|------------|----------|-----------------|
| **Archivos** | 9 | Persistencia en .dat (CRUD) |
| **Managers** | 9 | Lógica de negocio y validaciones |
| **Archivos .dat** | 8 | Almacenamiento binario |
| **Reportes** | 13 | Estadísticas y análisis |

**Total de clases de persistencia + lógica:** 18 clases principales
