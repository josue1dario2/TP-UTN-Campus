cmake_minimum_required(VERSION 3.31)
project(TP_UTN_Campus)

set(CMAKE_CXX_STANDARD 20)

# --- Ejecutable principal ---
add_executable(TP_UTN_Campus
        main.cpp
        Alumno.cpp
        ArchivoAlumno.cpp
        ArchivoDocente.cpp
        ArchivoCarrera.cpp
        ArchivoMateria.cpp
        Carrera.cpp
        Comision.cpp
        Correlativa.cpp
        Direccion.cpp
        Docente.cpp
        Examen.cpp
        Fecha.cpp
        Inscripcion.cpp
        Materia.cpp
        Persona.cpp
        Validacion.cpp
)

# --- Sección de Testing ---
enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# --- Ejecutable de pruebas ---
add_executable(runTests
        tests/test_alumno.cpp
)

# Enlazar con GoogleTest y tus clases
target_link_libraries(runTests gtest_main)

# Incluir headers del proyecto
target_include_directories(runTests PRIVATE ${CMAKE_SOURCE_DIR})

# Registrar los tests
add_test(NAME runTests COMMAND runTests)
