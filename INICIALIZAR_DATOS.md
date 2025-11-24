# 📚 Inicializar Datos - Plan de Estudios

Este documento explica cómo inicializar el sistema con el plan de estudios completo de la **Tecnicatura Universitaria en Programación**.

---

## 🎯 ¿Qué hace el inicializador?

El programa `inicializar_datos` crea automáticamente:

✅ **1 Carrera**: Tecnicatura Universitaria en Programación (4 cuatrimestres)

✅ **17 Materias** organizadas en 2 niveles:
- **NIVEL I** (Cuatrimestres 1-2): 8 materias
- **NIVEL II** (Cuatrimestres 3-4): 9 materias

✅ **26 Correlativas** según el plan de estudios oficial

---

## 🚀 Cómo usar

### Paso 1: Compilar el inicializador

```bash
cd build
cmake ..
make
```

Esto generará el ejecutable `inicializar_datos` junto con el programa principal.

### Paso 2: Ejecutar el inicializador

**IMPORTANTE**: Ejecutar desde el directorio raíz del proyecto (NO desde `build/`)

```bash
# Opción A: Desde el root
./build/inicializar_datos

# Opción B: Si estás en build/
cd ..
./build/inicializar_datos
```

### Paso 3: Verificar la creación

El programa mostrará:

```
=== INICIALIZADOR DE DATOS - TECNICATURA ===

[OK] Carrera creada: Tecnicatura Universitaria en Programacion

Creando materias...
  [OK] 1. Programacion I
  [OK] 2. Arquitectura y Sistemas Operativos
  ...
  [OK] 17. Gestion de Desarrollo de Software

Creando correlativas...
  [OK] Materia 5 requiere Materia 1
  [OK] Materia 5 requiere Materia 2
  ...

=========================================
INICIALIZACION COMPLETADA
=========================================
- Carrera: 1
- Materias: 17
- Correlativas: 26
=========================================
```

### Paso 4: Verificar archivos creados

```bash
ls -lh *.dat
```

Deberías ver:
- `Carreras.dat` (con 1 carrera)
- `Materias.dat` (con 17 materias)
- `Correlativas.dat` (con 26 correlativas)

---

## 📋 Plan de Estudios Cargado

### 🟥 NIVEL I (Cuatrimestres 1-2)

| ID | Materia | Cuatri | Correlativas |
|----|---------|--------|--------------|
| 1 | Programación I | 1 | - |
| 2 | Arquitectura y Sistemas Operativos | 1 | - |
| 3 | Matemática | 1 | - |
| 4 | Organización Empresarial | 1 | - |
| 5 | Programación II | 2 | 1, 2 |
| 6 | Probabilidad y Estadística | 2 | 3 |
| 7 | Base de Datos I | 2 | 1, 3 |
| 8 | Inglés I | 2 | - |

### 🟦 NIVEL II (Cuatrimestres 3-4)

| ID | Materia | Cuatri | Correlativas |
|----|---------|--------|--------------|
| 9 | Programación III | 3 | 5, 7 |
| 10 | Base de Datos II | 3 | 7 |
| 11 | Metodología de Sistemas I | 3 | 5, 7, 4 |
| 12 | Inglés II | 3 | 8 |
| 13 | Programación IV | 4 | 9, 10, 11 |
| 14 | Metodología de Sistemas II | 4 | 11 |
| 15 | Introducción al Análisis de Datos | 4 | 10, 6, 7 |
| 16 | Legislación | 4 | 7, 4 |
| 17 | Gestión de Desarrollo de Software | 4 | 9, 10 |

---

## ⚠️ IMPORTANTE

### Si ya tienes datos

El inicializador **agrega** datos, no los reemplaza. Si ya tienes materias:

```bash
# Opción 1: Borrar datos existentes
rm *.dat

# Opción 2: Usar archivos de prueba limpios
cp test_data/*.dat .
```

### Código de administrador

Para acceder al menú de administrador y ver las materias/correlativas:
- **Código**: `1234`

---

## 🔧 Solución de problemas

### Error: "No such file or directory"
```
./build/inicializar_datos
./build/inicializar_datos: error while loading shared libraries...
```

**Solución**: Asegúrate de ejecutar desde el directorio raíz:
```bash
cd /ruta/al/TP-UTN-Campus
./build/inicializar_datos
```

### Los archivos .dat no se crean

**Verificar permisos**:
```bash
ls -la *.dat
```

**Solución**: Ejecutar con permisos adecuados o desde el directorio correcto.

---

## 📝 Notas

- El inicializador crea archivos binarios `.dat` en el directorio actual
- Los IDs de materias son del 1 al 17
- El ID de carrera es 1
- Las correlativas solo se validan para CURSAR (no para rendir final)
