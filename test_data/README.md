# Datos de Prueba

Esta carpeta contiene archivos `.dat` de prueba para el sistema de gestión de campus.

## Archivos incluidos

- `Alumnos.dat` - Base de datos de alumnos
- `Docentes.dat` - Base de datos de docentes
- `Carreras.dat` - Base de datos de carreras
- `Materias.dat` - Base de datos de materias
- `Comisiones.dat` - Base de datos de comisiones
- `InscripcionesComision.dat` - Inscripciones de alumnos a comisiones
- `Examenes.dat` - Registro de exámenes (parciales, recuperatorios, finales)
- `Correlativas.dat` - Correlativas entre materias

## Cómo usar

### Opción 1: Copiar al directorio raíz para pruebas

```bash
cp test_data/*.dat .
```

### Opción 2: Modificar el programa para usar test_data/

Cambiar las rutas en los archivos Manager y Archivo para usar `test_data/` como prefijo.

### Opción 3: Ejecutar desde test_data/

```bash
cd test_data
../build/TP_UTN_Campus
```

## Nota

Estos archivos están inicialmente vacíos. El programa los populará automáticamente al usar las opciones de "Alta" en cada ABM.

## Código de administrador

- Código: `1234`
