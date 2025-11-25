# 📚 GUÍA DE ESTUDIO - Sistema de Gestión de Campus UTN
## Programación Orientada a Objetos (POO)

---

## 📑 Índice

1. [Métodos Principales y sus Validaciones](#métodos-principales-y-sus-validaciones)
2. [Flujos de Llamadas entre Métodos](#flujos-de-llamadas-entre-métodos)
3. [Conceptos de POO Aplicados](#conceptos-de-poo-aplicados)
4. [Preguntas Típicas de Examen](#preguntas-típicas-de-examen)
5. [Sistema de Reportes - Análisis POO](#sistema-de-reportes---análisis-poo)

---

## 1️⃣ MÉTODOS PRINCIPALES Y SUS VALIDACIONES

### 1.1 Inscripción a Comisión

**Ubicación:** `ManagerInscripcionComision.cpp:39`

#### Método Principal
```cpp
void ManagerInscripcionComision::cargar()
```

#### Flujo de Validaciones (Paso a Paso)

```
📋 INICIO: cargar()
│
├─ 1️⃣ VALIDACIÓN: ¿Existe la comisión?
│   └─ Llama a: manCom.existeComision(idComision)
│   └─ Si NO existe → ERROR y return
│
├─ 2️⃣ VALIDACIÓN: ¿Ya está inscripto?
│   └─ Llama a: estaInscripto(legajo, idComision)
│   └─ Recorre todas las inscripciones del archivo
│   └─ Si ya existe → ERROR y return
│
├─ 3️⃣ OBTENCIÓN DE DATOS: Buscar materia de la comisión
│   └─ Lee comisión desde archivo
│   └─ Obtiene: int idMateria = com.getIdMateria()
│
├─ 4️⃣ VALIDACIÓN ACADÉMICA: ¿Cumple correlativas?
│   └─ Llama a: manAlumno.cumpleCorrelativas(legajo, idMateria)
│   └─ Si NO cumple → ERROR y return
│   └─ (Ver detalle en sección 1.1.1)
│
├─ 5️⃣ VALIDACIÓN: ¿Ya aprobó la materia?
│   └─ Recorre archivo de exámenes
│   └─ Busca: Final con nota >= 4 en esa materia
│   └─ Si ya aprobó → ERROR y return
│
└─ 6️⃣ CREACIÓN: Guardar inscripción válida
    └─ Crea objeto InscripcionComision
    └─ Setea estado = 0 (activo)
    └─ Guarda en archivo
```

#### 1.1.1 Sub-método: cumpleCorrelativas()

**Ubicación:** `ManagerAlumno.cpp:20`

```
📋 cumpleCorrelativas(legajo, idMateria)
│
├─ 1️⃣ ¿Tiene correlativas la materia?
│   └─ Llama a: mgrCor.tieneCorrelativas(idMateriaObjetivo)
│   └─ Si NO tiene → return true (puede cursar)
│
├─ 2️⃣ Recorrer TODAS las correlativas de la materia
│   │
│   └─ Para cada correlativa:
│       ├─ Obtener idMateriaRequisito
│       │
│       ├─ Buscar en Examenes.dat si el alumno aprobó
│       │   └─ Condiciones:
│       │       • Legajo coincide
│       │       • idMateria = idRequisito
│       │       • Nota >= 4
│       │
│       └─ Si NO aprobó → marcar ok = false
│
└─ 3️⃣ return ok (true solo si aprobó TODAS)
```

**Ejemplo Real:**
```
Alumno quiere cursar: Programación III (ID: 5)
Correlativas:
  - Programación II (ID: 2) ✅ Aprobó con 7
  - Matemática II (ID: 4) ❌ No aprobó

Resultado: return false → NO puede inscribirse
```

---

### 1.2 Cargar Parcial

**Ubicación:** `ManagerExamen.cpp:16`

#### Método Principal
```cpp
void ManagerExamen::cargarParcial(int legajo, int idComision, int nota)
```

#### Flujo de Validaciones

```
📋 INICIO: cargarParcial()
│
├─ 1️⃣ VALIDACIÓN: ¿Existe la comisión?
│   └─ Busca en ArchivoComision
│   └─ Si NO existe → ERROR y return
│
├─ 2️⃣ VALIDACIÓN: ¿Está inscripto en la comisión?
│   └─ Llama a: manInsc.estaInscripto(legajo, idComision)
│   └─ Si NO está inscripto → ERROR y return
│
├─ 3️⃣ VALIDACIÓN: ¿Cuántos parciales tiene?
│   └─ Recorre Examenes.dat
│   └─ Cuenta parciales de ese alumno en esa materia
│   └─ Si tiene 2 → ERROR "Ya tiene los 2 parciales cargados"
│
├─ 4️⃣ CÁLCULO: Determinar número de parcial
│   └─ numeroParcial = parcialesExistentes + 1
│   └─ (Si tiene 0 → será Parcial 1)
│   └─ (Si tiene 1 → será Parcial 2)
│
└─ 5️⃣ CREACIÓN: Guardar examen
    └─ Crea objeto Examen con tipo "Parcial"
    └─ Setea numeroParcial y nota
    └─ Guarda en archivo
```

---

### 1.3 Cargar Recuperatorio

**Ubicación:** `ManagerExamen.cpp:75`

#### Flujo de Validaciones

```
📋 INICIO: cargarRecuperatorio()
│
├─ 1️⃣ VALIDACIÓN: ¿Existe la comisión?
│
├─ 2️⃣ VALIDACIÓN: ¿Está inscripto?
│
├─ 3️⃣ VALIDACIÓN: ¿Tiene parciales desaprobados?
│   └─ Recorre Examenes.dat
│   └─ Busca: tipo = "Parcial" AND nota < 4
│   └─ Si NO tiene desaprobados → ERROR
│
├─ 4️⃣ LÓGICA: Recuperar el último parcial desaprobado
│   └─ parcialARecu = ex.getNumeroParcial()
│   └─ (Puede ser 1 o 2)
│
└─ 5️⃣ CREACIÓN: Guardar recuperatorio
    └─ Tipo = "Recuperatorio"
    └─ numeroParcial = parcialARecu
    └─ REGLA: El recuperatorio reemplaza la nota del parcial
```

**Regla Importante:**
```
Si alumno rindió:
  Parcial 1: 3 (desaprobado)
  Parcial 2: 8 (aprobado)

Recuperatorio válido: Solo del Parcial 1
Nota final P1 = nota del recuperatorio
```

---

### 1.4 Rendir Final

**Ubicación:** `ManagerExamen.cpp:132` (cargarFinal) y `ManagerExamen.cpp:168` (puedeRendirFinal)

#### Método de Validación Completa
```cpp
bool ManagerExamen::puedeRendirFinal(int legajo, int idComision)
```

#### Flujo de Validaciones (MUY IMPORTANTE)

```
📋 INICIO: puedeRendirFinal()
│
├─ 0️⃣ VALIDACIÓN: ¿Existe la comisión?
│
├─ 1️⃣ VALIDACIÓN: ¿Está inscripto en la comisión?
│   └─ Llama a: manInsc.estaInscripto()
│
├─ 2️⃣ VALIDACIÓN ACADÉMICA: ¿Cumple correlativas?
│   └─ Llama a: ma.cumpleCorrelativas(legajo, idMateria)
│   └─ DEBE tener TODAS las correlativas aprobadas
│
├─ 3️⃣ VALIDACIÓN DE CONDICIÓN: ¿NO está promocionado?
│   └─ Llama a: estaPromocionado(legajo, idComision)
│   └─ Si está PROMOCIONADO → ERROR "No necesita final"
│   └─ (Ver sección 1.4.1 para lógica de promoción)
│
├─ 4️⃣ VALIDACIÓN DE CONDICIÓN: ¿NO está libre?
│   └─ Llama a: estaLibre(legajo, idComision)
│   └─ Si está LIBRE → ERROR "Debe cursar primero"
│   └─ Por descarte: debe estar REGULAR
│
└─ 5️⃣ VALIDACIÓN: ¿Ya aprobó el final?
    └─ Busca en Examenes.dat: tipo="Final" y nota >= 4
    └─ Si ya aprobó → ERROR
```

#### 1.4.1 Sub-método: estaPromocionado()

**Ubicación:** `ManagerExamen.cpp:229`

```
📋 estaPromocionado(legajo, idComision)
│
├─ 1️⃣ BÚSQUEDA: Obtener notas de parciales
│   └─ notaP1, notaP2 (de tipo "Parcial")
│   └─ recuP1, recuP2 (de tipo "Recuperatorio")
│
├─ 2️⃣ REGLA CRÍTICA: ¿Usó recuperatorio?
│   └─ if (recuP1 != -1 || recuP2 != -1)
│   └─    return false  ← NO PUEDE PROMOCIONAR
│
├─ 3️⃣ VALIDACIÓN: ¿Tiene los dos parciales?
│   └─ if (notaP1 < 0 || notaP2 < 0)
│   └─    return false
│
├─ 4️⃣ CÁLCULO: Calcular promedio
│   └─ prom = (notaP1 + notaP2) / 2.0
│
└─ 5️⃣ CONDICIÓN: Promedio >= 7
    └─ return prom >= 7
```

**Ejemplos Reales:**

✅ **PROMOCIONADO:**
```
Parcial 1: 8
Parcial 2: 7
Promedio: 7.5
Recuperatorios: NO usó
Resultado: PROMOCIONADO
```

❌ **NO PROMOCIONADO (usó recuperatorio):**
```
Parcial 1: 3
Recuperatorio P1: 9
Parcial 2: 8
Promedio: 8.5 (con recuperatorio)
Resultado: REGULAR (no promociona aunque promedio > 7)
```

#### 1.4.2 Sub-método: estaRegular()

**Ubicación:** `ManagerExamen.cpp:281`

```
📋 estaRegular(legajo, idComision)
│
├─ 1️⃣ VALIDACIÓN PREVIA: ¿Está promocionado?
│   └─ if (estaPromocionado()) return false
│   └─ (No puede ser regular Y promocionado)
│
├─ 2️⃣ OBTENCIÓN: Buscar notas de parciales y recuperatorios
│
├─ 3️⃣ APLICACIÓN DE RECUPERATORIOS:
│   └─ if (recuP1 != -1) → notaP1 = recuP1
│   └─ if (recuP2 != -1) → notaP2 = recuP2
│   └─ El recuperatorio REEMPLAZA la nota del parcial
│
├─ 4️⃣ VALIDACIÓN: ¿Rindió los dos parciales?
│   └─ if (notaP1 < 0 || notaP2 < 0) return false
│
├─ 5️⃣ CÁLCULO Y CONDICIÓN:
│   └─ promedio = (notaP1 + notaP2) / 2.0
│   └─ return promedio >= 4.0
```

#### 1.4.3 Sub-método: estaLibre()

**Ubicación:** `ManagerExamen.cpp:333`

```cpp
bool ManagerExamen::estaLibre(int legajo, int idComision) {
    return !estaPromocionado(legajo, idComision) &&
           !estaRegular(legajo, idComision);
}
```

**Lógica:** Por descarte, si NO está promocionado Y NO está regular → está LIBRE

---

## 2️⃣ FLUJOS DE LLAMADAS ENTRE MÉTODOS

### 2.1 Diagrama: Inscripción a Comisión

```
Usuario → ManagerInscripcionComision::cargar()
            │
            ├─→ ManagerComision::existeComision()
            │     └─→ ArchivoComision::buscarRegistro()
            │
            ├─→ ManagerInscripcionComision::estaInscripto()
            │     └─→ ArchivoInscripcionComision::leerRegistro() (loop)
            │
            ├─→ ArchivoComision::leerRegistro()
            │     └─→ Obtiene idMateria
            │
            ├─→ ManagerAlumno::cumpleCorrelativas()
            │     └─→ ManagerCorrelativa::tieneCorrelativas()
            │     └─→ ArchivoCorrelativa::leerRegistro() (loop)
            │     └─→ ArchivoExamen::leerRegistro() (loop)
            │           └─→ Busca finales aprobados (nota >= 4)
            │
            ├─→ ArchivoExamen::leerRegistro() (loop)
            │     └─→ Verifica si ya aprobó la materia
            │
            └─→ ArchivoInscripcionComision::agregarRegistro()
                  └─→ Guarda la inscripción
```

**Conceptos POO aplicados:**
- ✅ **Composición:** ManagerInscripcionComision contiene instancias de otros managers
- ✅ **Delegación:** Delega validaciones a otros managers especializados
- ✅ **Encapsulamiento:** Cada manager maneja su propia lógica
- ✅ **Responsabilidad Única:** Cada método tiene una responsabilidad clara

---

### 2.2 Diagrama: Rendir Final

```
Usuario → ManagerExamen::cargarFinal()
            │
            ├─→ ManagerExamen::puedeRendirFinal()
            │     │
            │     ├─→ ManagerInscripcionComision::estaInscripto()
            │     │
            │     ├─→ ManagerAlumno::cumpleCorrelativas()
            │     │     └─→ [mismo flujo que antes]
            │     │
            │     ├─→ ManagerExamen::estaPromocionado()
            │     │     └─→ ArchivoExamen::leerRegistro() (loop)
            │     │           └─→ Busca Parciales y Recuperatorios
            │     │
            │     ├─→ ManagerExamen::estaLibre()
            │     │     └─→ estaPromocionado()
            │     │     └─→ estaRegular()
            │     │           └─→ ArchivoExamen::leerRegistro() (loop)
            │     │
            │     └─→ ArchivoExamen::leerRegistro() (loop)
            │           └─→ Verifica finales previos
            │
            └─→ ArchivoExamen::agregarRegistro()
                  └─→ Guarda el final
```

---

### 2.3 Tabla de Dependencias entre Clases

| Manager | Depende de | Motivo |
|---------|------------|--------|
| `ManagerInscripcionComision` | `ManagerComision` | Validar existencia de comisión |
| `ManagerInscripcionComision` | `ManagerAlumno` | Validar correlativas |
| `ManagerInscripcionComision` | `ArchivoExamen` | Verificar si ya aprobó |
| `ManagerExamen` | `ManagerInscripcionComision` | Validar inscripción activa |
| `ManagerExamen` | `ManagerAlumno` | Validar correlativas para final |
| `ManagerAlumno` | `ManagerCorrelativa` | Verificar correlativas |
| `ManagerAlumno` | `ArchivoExamen` | Buscar exámenes aprobados |
| `ManagerReportes` | **Todos** | Generar estadísticas globales |

---

## 3️⃣ CONCEPTOS DE POO APLICADOS

### 3.1 Encapsulamiento

**Definición:** Ocultar los detalles de implementación y exponer solo interfaces públicas.

**Ejemplo en el proyecto:**

```cpp
class ManagerInscripcionComision {
private:
    ArchivoInscripcionComision _archivo;  // ← Atributo privado

    void mostrarEncabezado();  // ← Método privado (helper)
    void mostrarRegistro();    // ← Método privado
    void mostrarPie();         // ← Método privado

public:
    void cargar();   // ← Interfaz pública
    void listar();   // ← Interfaz pública
    bool estaInscripto(int legajo, int idComision);  // ← Interfaz pública
};
```

**Por qué está bien encapsulado:**
- ✅ Los métodos `mostrar*()` son detalles internos → privados
- ✅ El archivo `_archivo` no se expone → privado
- ✅ Los métodos públicos son los que el usuario necesita usar

---

### 3.2 Composición

**Definición:** Una clase contiene objetos de otras clases como atributos.

**Ejemplo en el proyecto:**

```cpp
class ManagerReportes {
private:
    ArchivoAlumno _archivoAlumnos;              // ← Composición
    ArchivoMateria _archivoMaterias;            // ← Composición
    ArchivoComision _archivoComisiones;         // ← Composición
    ArchivoInscripcionComision _archivoInscripciones;  // ← Composición
    ArchivoExamen _archivoExamenes;             // ← Composición
    ArchivoDocente _archivoDocentes;            // ← Composición
    ManagerExamen _managerExamen;               // ← Composición
};
```

**Ventajas:**
- ✅ No necesita crear/destruir objetos dinámicamente
- ✅ Los objetos existen mientras existe ManagerReportes
- ✅ Fácil acceso a funcionalidades de otras clases

---

### 3.3 Delegación

**Definición:** Delegar responsabilidades a objetos especializados.

**Ejemplo en el proyecto:**

```cpp
void ManagerInscripcionComision::cargar() {
    // ❌ MAL: Hacer toda la lógica aquí
    // for (...) buscar correlativas...
    // for (...) verificar exámenes...

    // ✅ BIEN: Delegar a managers especializados
    if (!manCom.existeComision(idComision)) { ... }
    if (!manAlumno.cumpleCorrelativas(legajo, idMateria)) { ... }
}
```

**Por qué está bien:**
- ✅ `ManagerAlumno` sabe cómo validar correlativas
- ✅ `ManagerComision` sabe cómo validar comisiones
- ✅ `ManagerInscripcionComision` solo coordina

---

### 3.4 Responsabilidad Única (SRP)

**Definición:** Cada clase debe tener una única responsabilidad.

**Ejemplo en el proyecto:**

| Clase | Responsabilidad Única |
|-------|----------------------|
| `ManagerAlumno` | Gestión de alumnos y validación de correlativas |
| `ManagerExamen` | Gestión de exámenes y validación de condiciones académicas |
| `ManagerInscripcionComision` | Gestión de inscripciones a comisiones |
| `ManagerReportes` | Generación de reportes estadísticos |
| `ArchivoAlumno` | Persistencia de datos de alumnos en archivo binario |

**Contraejemplo (lo que NO se hizo):**
```cpp
// ❌ MAL: Una clase que hace TODO
class ManagerUniversal {
    void inscribirAlumno();
    void crearComision();
    void cargarExamen();
    void generarReportes();
    void validarCorrelativas();
    void gestionarDocentes();
    // ... 50 métodos más
};
```

---

### 3.5 Abstracción

**Definición:** Simplificar complejidad mediante interfaces claras.

**Ejemplo en el proyecto:**

```cpp
// Interfaz simple para el usuario
bool puedeRendirFinal(int legajo, int idComision);

// Internamente realiza 5 validaciones complejas:
// - Inscripción
// - Correlativas
// - No promocionado
// - No libre
// - No aprobado previamente
```

**El usuario solo llama:**
```cpp
if (managerExamen.puedeRendirFinal(1001, 101)) {
    // Rendir final
}
```

No necesita saber cómo se valida internamente.

---

### 3.6 Patrón Repository

**Definición:** Separar lógica de negocio de lógica de acceso a datos.

**Capas del proyecto:**

```
┌──────────────────────────────────┐
│   PRESENTACIÓN (main.cpp)        │  ← Interacción con usuario
│   - Menús                         │
│   - cout/cin                      │
└──────────────────────────────────┘
              ↓
┌──────────────────────────────────┐
│   LÓGICA DE NEGOCIO (Managers)   │  ← Validaciones y reglas
│   - ManagerAlumno                 │
│   - ManagerExamen                 │
│   - ManagerInscripcionComision    │
└──────────────────────────────────┘
              ↓
┌──────────────────────────────────┐
│   ACCESO A DATOS (Archivos)      │  ← Persistencia
│   - ArchivoAlumno                 │
│   - ArchivoExamen                 │
│   - ArchivoInscripcionComision    │
└──────────────────────────────────┘
              ↓
┌──────────────────────────────────┐
│   ARCHIVOS .dat                   │  ← Datos binarios
└──────────────────────────────────┘
```

**Ventajas:**
- ✅ Cambiar persistencia (de binario a SQL) sin tocar Managers
- ✅ Testear Managers sin acceder a archivos reales
- ✅ Separación clara de responsabilidades

---

## 4️⃣ PREGUNTAS TÍPICAS DE EXAMEN

### Bloque 1: Conceptos Teóricos

**P1: ¿Qué es el encapsulamiento y dónde se aplica en el proyecto?**

**R:** El encapsulamiento es ocultar detalles internos y exponer solo interfaces públicas. Se aplica en:
- Atributos privados (ej: `_archivo` en managers)
- Métodos helper privados (ej: `mostrarEncabezado()`)
- Solo exponer métodos públicos necesarios (ej: `cargar()`, `listar()`)

**Ejemplo:**
```cpp
class ManagerInscripcionComision {
private:
    ArchivoInscripcionComision _archivo;  // No se puede acceder desde afuera
public:
    void cargar();  // Interfaz pública
};
```

---

**P2: ¿Qué diferencia hay entre composición y herencia? ¿Cuál se usa en el proyecto?**

**R:**
- **Composición:** Una clase contiene objetos de otras clases ("tiene un")
- **Herencia:** Una clase extiende otra ("es un")

El proyecto usa **composición**:
```cpp
class ManagerReportes {
private:
    ArchivoAlumno _archivoAlumnos;  // ManagerReportes "tiene un" ArchivoAlumno
    ManagerExamen _managerExamen;   // ManagerReportes "tiene un" ManagerExamen
};
```

**Por qué composición y no herencia:**
- ✅ Más flexible
- ✅ Evita jerarquías complejas
- ✅ Permite reutilizar sin heredar todo

---

**P3: ¿Qué es la delegación? Da un ejemplo del proyecto.**

**R:** Delegación es transferir una responsabilidad a otro objeto especializado.

**Ejemplo:**
```cpp
void ManagerInscripcionComision::cargar() {
    // Delega validación de correlativas a ManagerAlumno
    if (!manAlumno.cumpleCorrelativas(legajo, idMateria)) {
        // ...
    }
}
```

En lugar de implementar la lógica de correlativas aquí, **delega** a `ManagerAlumno`.

---

### Bloque 2: Flujos y Validaciones

**P4: Explica el flujo completo de inscripción a una comisión con sus validaciones.**

**R:**
```
1. Validar que la comisión exista
2. Validar que no esté ya inscripto (evitar duplicados)
3. Obtener idMateria desde la comisión
4. Validar correlativas (debe tener todas aprobadas)
5. Validar que no haya aprobado ya la materia
6. Crear y guardar la inscripción
```

**Métodos involucrados:**
- `existeComision()` → ManagerComision
- `estaInscripto()` → ManagerInscripcionComision
- `cumpleCorrelativas()` → ManagerAlumno
- `agregarRegistro()` → ArchivoInscripcionComision

---

**P5: ¿Cuándo un alumno está PROMOCIONADO?**

**R:**
```cpp
CONDICIONES para PROMOCIÓN:
1. Tiene los dos parciales rendidos
2. NO usó recuperatorio (ni en P1 ni en P2)
3. Promedio >= 7
```

**Código:**
```cpp
bool estaPromocionado() {
    // Si usó recuperatorio → NO promociona
    if (recuP1 != -1 || recuP2 != -1) return false;

    // Necesita ambos parciales
    if (notaP1 < 0 || notaP2 < 0) return false;

    // Promedio >= 7
    float prom = (notaP1 + notaP2) / 2.0f;
    return prom >= 7;
}
```

**Ejemplo:**
- Parcial 1: 8, Parcial 2: 7 → Promedio 7.5 → ✅ PROMOCIONADO
- Parcial 1: 3, Recu P1: 9, Parcial 2: 8 → ❌ NO PROMOCIONA (usó recuperatorio)

---

**P6: ¿Cuándo un alumno está REGULAR?**

**R:**
```cpp
CONDICIONES para REGULARIDAD:
1. NO está promocionado
2. Tiene los dos parciales rendidos (con o sin recuperatorios)
3. Promedio >= 4 (aplicando recuperatorios si los usó)
```

**Código clave:**
```cpp
bool estaRegular() {
    // No puede ser regular si está promocionado
    if (estaPromocionado()) return false;

    // Aplicar recuperatorios
    if (recuP1 != -1) notaP1 = recuP1;
    if (recuP2 != -1) notaP2 = recuP2;

    // Promedio >= 4
    float prom = (notaP1 + notaP2) / 2.0f;
    return prom >= 4.0f;
}
```

---

**P7: ¿Cuándo un alumno está LIBRE?**

**R:** Por descarte:
```cpp
bool estaLibre() {
    return !estaPromocionado() && !estaRegular();
}
```

**Casos:**
- No rindió parciales → LIBRE
- Promedio < 4 → LIBRE
- Solo rindió 1 parcial → LIBRE

---

**P8: ¿Qué validaciones se hacen antes de rendir un final?**

**R:**
```
1. ¿Existe la comisión?
2. ¿Está inscripto en la comisión?
3. ¿Cumple correlativas?
4. ¿NO está promocionado? (si promociona, no necesita final)
5. ¿NO está libre? (debe estar regular)
6. ¿NO aprobó ya el final?
```

**Código:**
```cpp
bool puedeRendirFinal(int legajo, int idComision) {
    if (!manInsc.estaInscripto(...)) return false;
    if (!ma.cumpleCorrelativas(...)) return false;
    if (estaPromocionado(...)) return false;
    if (estaLibre(...)) return false;
    if (yaAproboFinal(...)) return false;
    return true;
}
```

---

### Bloque 3: Análisis de Código

**P9: ¿Qué hace este código y qué concepto de POO aplica?**

```cpp
class ManagerReportes {
private:
    ArchivoAlumno _archivoAlumnos;
    ManagerExamen _managerExamen;

public:
    void reporteRendimientoAcademico(int legajo) {
        float promedio = calcularPromedioAlumno(legajo);
        int aprobadas = contarMateriasAprobadas(legajo);
        // ...
    }
};
```

**R:**
- **Composición:** Contiene `ArchivoAlumno` y `ManagerExamen` como atributos
- **Delegación:** Usa funciones auxiliares (`calcularPromedioAlumno`) para cálculos
- **Encapsulamiento:** Los archivos son privados, solo expone `reporteRendimientoAcademico()`
- **Responsabilidad Única:** Solo se encarga de generar reportes

---

**P10: ¿Por qué este método llama a `cumpleCorrelativas()` desde `ManagerAlumno` en lugar de implementarlo aquí?**

```cpp
void ManagerInscripcionComision::cargar() {
    ManagerAlumno manAlumno;
    if (!manAlumno.cumpleCorrelativas(legajo, idMateria)) {
        // ...
    }
}
```

**R:**
- **Delegación:** La validación de correlativas es responsabilidad de `ManagerAlumno`
- **Responsabilidad Única:** `ManagerInscripcionComision` no debe saber cómo validar correlativas
- **Reutilización:** El método `cumpleCorrelativas()` puede usarse en otros contextos
- **Mantenibilidad:** Si cambia la lógica de correlativas, solo se modifica en un lugar

---

### Bloque 4: Reglas de Negocio

**P11: ¿Cuál es la diferencia entre parcial y recuperatorio en el sistema?**

**R:**
- **Parcial:** Examen normal (pueden ser 2 por materia)
- **Recuperatorio:** Reemplaza la nota de un parcial desaprobado (nota < 4)

**Reglas importantes:**
```
1. Solo se puede recuperar si desaprobó (nota < 4)
2. El recuperatorio REEMPLAZA la nota del parcial
3. Si usa recuperatorio, NO puede promocionar (solo regularizar)
```

**Ejemplo:**
```
Parcial 1: 3
Recuperatorio P1: 7
Parcial 2: 8
Promedio: (7 + 8) / 2 = 7.5

Condición: REGULAR (no promociona porque usó recuperatorio)
```

---

**P12: ¿Qué pasa si un alumno tiene Parcial 1: 8, Recuperatorio P1: 4? ¿Qué nota se toma?**

**R:** Se toma la nota del **recuperatorio** (4), porque el recuperatorio SIEMPRE reemplaza al parcial, aunque sea peor.

```cpp
if (recuP1 != -1) notaP1 = recuP1;  // Reemplaza sin importar si es mejor o peor
```

---

**P13: Un alumno quiere cursar Programación III. ¿Qué correlativas debe tener aprobadas?**

**R:** El sistema busca en `Correlativas.dat` todas las materias requisito para Programación III y verifica:

```cpp
for (cada correlativa) {
    buscar en Examenes.dat:
        - Legajo del alumno
        - idMateria = correlativa
        - Tipo = "Final" (o cualquier examen)
        - Nota >= 4

    if (no encontró) → return false;
}
return true;
```

Debe tener **TODAS** las correlativas aprobadas con nota >= 4.

---

## 5️⃣ SISTEMA DE REPORTES - ANÁLISIS POO

### 5.1 Reportes de Alta Prioridad

#### Reporte 1: Rendimiento Académico

**Ubicación:** `ManagerReportes.cpp:32`

**Método:**
```cpp
void ManagerReportes::reporteRendimientoAcademico(int legajo)
```

**Flujo:**
```
1. Buscar alumno en archivo
2. Calcular promedio → llama a calcularPromedioAlumno(legajo)
3. Contar materias aprobadas → llama a contarMateriasAprobadas(legajo)
4. Contar promocionadas → llama a contarMateriasPromocionadas(legajo)
5. Contar regulares → llama a contarMateriasRegulares(legajo)
6. Contar libres → llama a contarMateriasLibres(legajo)
7. Determinar estado general del alumno
8. Mostrar reporte formateado
```

**Conceptos POO aplicados:**
- ✅ **Delegación:** Usa funciones auxiliares de `utils.h` para cálculos
- ✅ **Composición:** Contiene múltiples archivos como atributos
- ✅ **Encapsulamiento:** Oculta la lógica de cálculo en funciones auxiliares

**Preguntas de examen:**

**Q1: ¿Cómo calcula el promedio general de un alumno?**

**R:**
```cpp
float calcularPromedioAlumno(int legajo) {
    // Busca TODOS los exámenes finales del alumno
    for (cada examen) {
        if (legajo coincide &&
            tipo == "Final" &&
            nota >= 4) {
            suma += nota;
            cant++;
        }
    }
    return (cant > 0) ? suma / cant : 0.0f;
}
```

Solo cuenta finales aprobados (nota >= 4).

---

**Q2: ¿Cómo determina el estado general (EXCELENTE, MUY BUENO, REGULAR, EN RIESGO)?**

**R:**
```cpp
if (libres > cursadas / 2) {
    cout << "Estado: EN RIESGO ACADEMICO\n";
} else if (promedio >= 7) {
    cout << "Estado: EXCELENTE\n";
} else if (promedio >= 6) {
    cout << "Estado: MUY BUENO\n";
} else {
    cout << "Estado: REGULAR\n";
}
```

**Criterio de riesgo:** Más del 50% de materias libres.

---

#### Reporte 2: Listado de Alumnos por Comisión

**Ubicación:** `ManagerReportes.cpp:85`

**Flujo:**
```
1. Buscar comisión en archivo
2. Obtener datos de la materia
3. Obtener datos del docente
4. Recorrer todas las inscripciones
5. Filtrar por idComision
6. Para cada inscripción, buscar datos del alumno
7. Mostrar tabla formateada con estados
```

**Preguntas de examen:**

**Q3: ¿Qué estados puede tener una inscripción?**

**R:**
```cpp
if (estado == 0) → "Activo"
else if (estado == 1) → "Pendiente de baja"
else → "Baja"
```

**Q4: ¿Cómo cuenta los inscriptos en una comisión?**

**R:**
```cpp
int contarInscriptosEnComision(int idComision) {
    int count = 0;
    for (cada inscripción) {
        if (idComision coincide && estado == 0) {
            count++;
        }
    }
    return count;
}
```

Solo cuenta inscripciones **activas** (estado = 0).

---

#### Reporte 3: Estadísticas por Materia

**Ubicación:** `ManagerReportes.cpp:150`

**Flujo:**
```
1. Buscar materia
2. Buscar TODAS las comisiones de esa materia
3. Para cada comisión:
   - Buscar inscripciones activas
   - Para cada alumno inscripto:
     - Verificar si está promocionado → _managerExamen.estaPromocionado()
     - Verificar si está regular → _managerExamen.estaRegular()
     - Si no → está libre
     - Calcular promedio de parciales
4. Calcular estadísticas globales
5. Mostrar reporte
```

**Preguntas de examen:**

**Q5: ¿Cómo calcula la tasa de aprobación de una materia?**

**R:**
```cpp
int tasaAprobacion = (totalInscriptos > 0) ?
    ((promocionados + regulares) * 100 / totalInscriptos) : 0;
```

**Aprobación** = promocionados + regulares (los libres NO aprueban).

---

**Q6: ¿Por qué este reporte llama a `_managerExamen.estaPromocionado()`?**

**R:**
- **Delegación:** La lógica de determinar condición académica es responsabilidad de `ManagerExamen`
- **Reutilización:** No duplicar código de validación
- **Composición:** `ManagerReportes` contiene `ManagerExamen` como atributo

---

#### Reporte 4: Finales Pendientes

**Ubicación:** `ManagerReportes.cpp:231`

**Flujo:**
```
1. Buscar alumno
2. Para CADA materia:
   - Buscar una comisión de la materia
   - Verificar si está regular → _managerExamen.estaRegular()
   - Buscar en exámenes si tiene final aprobado
   - Si está regular Y NO tiene final aprobado:
     - Agregar a la lista
3. Mostrar todas las materias con final pendiente
```

**Preguntas de examen:**

**Q7: ¿Por qué un alumno tiene "final pendiente"?**

**R:**
```
Condiciones:
1. Está REGULAR en la materia (promedio >= 4)
2. NO tiene final aprobado (nota >= 4 en tipo "Final")
```

Si está libre → no tiene final pendiente (debe cursar primero).
Si está promocionado → no tiene final pendiente (ya aprobó).

---

#### Reporte 5: Comisiones por Cupo

**Ubicación:** `ManagerReportes.cpp:299`

**Flujo:**
```
1. Para CADA comisión activa:
   - Obtener datos de la materia
   - Contar inscriptos → contarInscriptosEnComision()
   - Calcular porcentaje de ocupación
   - Determinar estado (LLENA, Casi llena, Media, Disponible)
2. Mostrar tabla ordenada
```

**Preguntas de examen:**

**Q8: ¿Cómo determina si una comisión está LLENA?**

**R:**
```cpp
int inscriptos = contarInscriptosEnComision(idComision);
int cupo = 30;  // Cupo estándar
int porcentaje = (inscriptos * 100 / cupo);

if (inscriptos >= cupo) estado = "LLENA";
else if (porcentaje >= 80) estado = "Casi llena";
else if (porcentaje >= 50) estado = "Media";
else estado = "Disponible";
```

---

### 5.2 Reportes de Media Prioridad

#### Reporte 6: Ranking por Promedio

**Ubicación:** `ManagerReportes.cpp:349`

**Conceptos POO aplicados:**

**Q9: ¿Qué estructura de datos usa para ordenar alumnos?**

**R:**
```cpp
struct AlumnoPromedio {
    int legajo;
    string nombre;
    float promedio;
};

vector<AlumnoPromedio> alumnos;

// Ordenar usando algoritmo STL
sort(alumnos.begin(), alumnos.end(),
     [](const AlumnoPromedio& a, const AlumnoPromedio& b) {
         return a.promedio > b.promedio;
     });
```

**Conceptos:**
- ✅ **Struct:** Agrupar datos relacionados
- ✅ **Vector:** Contenedor dinámico de STL
- ✅ **Lambda:** Función anónima para comparación
- ✅ **Algoritmo STL:** `sort()` con comparador personalizado

---

#### Reporte 7: Calendario de Finales

**Ubicación:** `ManagerReportes.cpp:406`

**Q10: ¿Cómo cuenta cuántos alumnos deben rendir final en cada materia?**

**R:**
```
Para cada materia:
  Para cada alumno:
    Si está REGULAR Y NO tiene final aprobado:
      contador++
```

**Importante:** Solo cuenta regulares (no libres, no promocionados).

---

#### Reporte 9: Alumnos en Riesgo Académico

**Ubicación:** `ManagerReportes.cpp:610`

**Q11: ¿Cuáles son los criterios para considerar un alumno en riesgo?**

**R:**
```cpp
int libres = contarMateriasLibres(legajo);
float promedio = calcularPromedioAlumno(legajo);
int cursadas = promocionadas + regulares + libres;

// Criterio de riesgo
if ((cursadas > 0 && libres > cursadas / 2) || promedio < 4) {
    // ALUMNO EN RIESGO
}
```

**Criterios:**
1. Más del 50% de materias cursadas están libres
2. **O** promedio general < 4

---

### 5.3 Reportes Analíticos

#### Reporte 12: Materias con Mayor Índice de Libre

**Ubicación:** `ManagerReportes.cpp:743`

**Q12: ¿Cómo calcula el porcentaje de alumnos libres por materia?**

**R:**
```cpp
struct MateriaEstadistica {
    int idMateria;
    string nombre;
    int totalAlumnos;
    int libres;
    float porcentaje;
};

// Para cada materia:
for (cada comisión de la materia) {
    for (cada inscripción) {
        totalAlumnos++;
        if (_managerExamen.estaLibre(legajo, idComision)) {
            libres++;
        }
    }
}

porcentaje = (libres * 100.0f / totalAlumnos);

// Ordenar por porcentaje descendente
sort(materias.begin(), materias.end(),
     [](const MateriaEstadistica& a, const MateriaEstadistica& b) {
         return a.porcentaje > b.porcentaje;
     });
```

---

## 6️⃣ PREGUNTAS AVANZADAS DE EXAMEN

### Pregunta 1: Análisis Completo

**Analiza el siguiente código y explica qué conceptos de POO aplica:**

```cpp
class ManagerReportes {
private:
    ArchivoAlumno _archivoAlumnos;
    ArchivoExamen _archivoExamenes;
    ManagerExamen _managerExamen;

public:
    void estadisticasPorMateria(int idMateria) {
        // ...
        if (_managerExamen.estaPromocionado(legajo, idComision)) {
            promocionados++;
        }
        // ...
    }
};
```

**Respuesta esperada:**

1. **Encapsulamiento:**
   - Atributos privados (`_archivoAlumnos`, etc.)
   - Método público (`estadisticasPorMateria`)

2. **Composición:**
   - Contiene objetos de otras clases como atributos
   - `ManagerReportes` "tiene un" `ArchivoAlumno`

3. **Delegación:**
   - Delega a `_managerExamen` la validación de promoción
   - No implementa la lógica localmente

4. **Responsabilidad Única:**
   - `ManagerReportes` solo genera reportes
   - `ManagerExamen` maneja lógica de exámenes

5. **Patrón Repository:**
   - Separa lógica de negocio (Manager) de acceso a datos (Archivo)

---

### Pregunta 2: Trace Completo

**Realiza un trace del siguiente flujo: Un alumno intenta inscribirse a Programación III**

**Datos:**
- Legajo: 1001
- Comisión: 301 (Programación III)
- Correlativas: Programación II, Matemática II
- Estado actual: Aprobó Programación II con 8, pero no cursó Matemática II

**Trace:**

```
1. Usuario llama: managerInsc.cargar()
   - Ingresa legajo: 1001
   - Ingresa comisión: 301

2. Validación: ¿Existe comisión?
   └→ manCom.existeComision(301) → TRUE ✅

3. Validación: ¿Ya está inscripto?
   └→ estaInscripto(1001, 301) → FALSE ✅

4. Obtención: idMateria de la comisión
   └→ com.getIdMateria() → 5 (Programación III)

5. Validación: ¿Cumple correlativas?
   └→ manAlumno.cumpleCorrelativas(1001, 5)
       └→ Busca correlativas de materia 5:
           - Correlativa 1: Programación II (ID: 2)
           - Correlativa 2: Matemática II (ID: 4)

       └→ Verifica Programación II:
           └→ Busca en Examenes.dat:
               legajo=1001, idMateria=2, nota>=4
           └→ Encuentra: Final con nota 8 ✅

       └→ Verifica Matemática II:
           └→ Busca en Examenes.dat:
               legajo=1001, idMateria=4, nota>=4
           └→ NO encuentra ❌

       └→ return FALSE

6. ERROR: "El alumno NO cumple las correlativas"
7. return → NO se crea la inscripción
```

**Resultado:** La inscripción es rechazada porque falta aprobar Matemática II.

---

### Pregunta 3: Modificación de Código

**Si quisieras cambiar el criterio de promoción de promedio >= 7 a promedio >= 8, ¿dónde modificarías el código?**

**Respuesta:**

```cpp
// Archivo: ManagerExamen.cpp
// Línea: 276

bool ManagerExamen::estaPromocionado(int legajo, int idComision) {
    // ... código ...

    float prom = (notaP1 + notaP2) / 2.0f;

    return prom >= 8;  // ← Cambiar aquí de 7 a 8
}
```

**Por qué solo aquí:**
- ✅ **Responsabilidad Única:** La lógica de promoción está centralizada en un método
- ✅ **Encapsulamiento:** Todos los lugares que necesitan saber si un alumno está promocionado llaman a este método
- ✅ **Mantenibilidad:** Cambiar en un solo lugar afecta todo el sistema

---

### Pregunta 4: Diseño de Nuevo Reporte

**Diseña un nuevo reporte: "Docentes con Mayor Carga Académica" que muestre los top 5 docentes ordenados por cantidad total de alumnos.**

**Respuesta:**

```cpp
void ManagerReportes::docentesMayorCarga() {
    struct DocenteCarga {
        int legajo;
        string nombre;
        int totalAlumnos;
    };

    vector<DocenteCarga> docentes;

    // 1. Recopilar datos
    int totalDoc = _archivoDocentes.contarRegistros();

    for (int i = 0; i < totalDoc; i++) {
        Docente doc = _archivoDocentes.leerRegistro(i);
        if (doc.getEliminado()) continue;

        int alumnos = 0;

        // Contar alumnos en todas sus comisiones
        int totalCom = _archivoComisiones.contarRegistros();
        for (int j = 0; j < totalCom; j++) {
            Comision com = _archivoComisiones.leerRegistro(j);

            if (com.getLegajoDocente() == doc.getLegajo()) {
                alumnos += contarInscriptosEnComision(com.getIdComision());
            }
        }

        if (alumnos > 0) {
            DocenteCarga dc;
            dc.legajo = doc.getLegajo();
            dc.nombre = string(doc.getNombre()) + " " + string(doc.getApellido());
            dc.totalAlumnos = alumnos;
            docentes.push_back(dc);
        }
    }

    // 2. Ordenar por cantidad de alumnos descendente
    sort(docentes.begin(), docentes.end(),
         [](const DocenteCarga& a, const DocenteCarga& b) {
             return a.totalAlumnos > b.totalAlumnos;
         });

    // 3. Mostrar top 5
    cout << "\n=== TOP 5 DOCENTES CON MAYOR CARGA ===\n";
    for (size_t i = 0; i < docentes.size() && i < 5; i++) {
        cout << (i+1) << ". " << docentes[i].nombre
             << " - " << docentes[i].totalAlumnos << " alumnos\n";
    }
}
```

**Conceptos POO aplicados:**
- ✅ Struct para agrupar datos
- ✅ Vector de STL
- ✅ Lambda para ordenamiento
- ✅ Delegación (usa `contarInscriptosEnComision()`)
- ✅ Composición (usa archivos como atributos)

---

## 7️⃣ CONSEJOS PARA EL EXAMEN

### ✅ Qué estudiar bien

1. **Flujos de validación:**
   - Inscripción a comisión (6 pasos)
   - Rendir final (5 validaciones)
   - Validación de correlativas

2. **Reglas de negocio:**
   - Promoción vs Regular vs Libre
   - Recuperatorios (reemplazan notas)
   - Correlativas (deben estar aprobadas)

3. **Conceptos POO:**
   - Encapsulamiento (private vs public)
   - Composición (tiene un)
   - Delegación (delegar responsabilidades)
   - Responsabilidad Única (SRP)

4. **Estructura del proyecto:**
   - Managers (lógica de negocio)
   - Archivos (persistencia)
   - Utils (funciones auxiliares)

### ❌ Errores comunes a evitar

1. **Confundir composición con herencia**
   - Composición: "tiene un" (usado en el proyecto)
   - Herencia: "es un" (NO usado)

2. **No entender la diferencia entre promocionado/regular/libre**
   - Promocionado: promedio >= 7, sin recuperatorios
   - Regular: promedio >= 4, puede haber usado recuperatorios
   - Libre: promedio < 4 o no rindió ambos parciales

3. **Olvidar que los recuperatorios impiden la promoción**
   - Aunque el promedio sea > 7, si usó recuperatorio → solo regular

4. **No saber explicar por qué se usa delegación**
   - Responsabilidad Única
   - Reutilización de código
   - Mantenibilidad

---

## 🎯 CHECKLIST FINAL

Antes del examen, asegúrate de poder responder:

- [ ] ¿Qué validaciones hace el método de inscripción a comisión?
- [ ] ¿Cómo funciona `cumpleCorrelativas()`?
- [ ] ¿Cuándo un alumno está promocionado/regular/libre?
- [ ] ¿Qué validaciones se hacen para rendir un final?
- [ ] ¿Qué es encapsulamiento y dónde se aplica?
- [ ] ¿Qué es composición y por qué se usa en lugar de herencia?
- [ ] ¿Qué es delegación y por qué se usa?
- [ ] ¿Cómo funcionan los recuperatorios?
- [ ] ¿Cómo se estructura el patrón Repository?
- [ ] ¿Qué hace cada reporte principal y qué métodos auxiliares usa?

---

## 📞 Contacto

Para cualquier duda, revisa:
- Código fuente completo en el repositorio
- REPORTES.md para detalles de reportes
- INFORME_ACADEMICO.md para reglas de negocio detalladas

**¡Mucha suerte en tu examen! 🚀**
