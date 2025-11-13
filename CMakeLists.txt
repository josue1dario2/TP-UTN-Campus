cmake_minimum_required(VERSION 3.31)
project(TP_UTN_Campus)

set(CMAKE_CXX_STANDARD 20)

# --- ejecutable principal ---
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
        Materia.cpp
        Persona.cpp
        Validacion.cpp
        MenuPrincipal.cpp
        MenuAdmin.cpp
        MenuAbmCarreras.cpp
        MenuAbmComisiones.cpp
        MenuAbmMaterias.cpp
        MenuAlumno.cpp
        MenuDocente.cpp
        MenuUtilitarios.cpp
        ManagerCarrera.cpp
        ManagerMateria.cpp
        ManagerAlumno.cpp
        ManagerExamen.cpp
        ManagerDocente.cpp
        ManagerComision.cpp
        ArchivoComision.cpp
        ArchivoInscripcionComision.cpp
        ArchivoExamen.cpp
        InscripcionComision.cpp
        utils.cpp
)

# --- GoogleTest setup ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- ejecutable de tests ---
add_executable(runTests
        tests/test_alumno.cpp
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
        Materia.cpp
        Persona.cpp
        Validacion.cpp
        ArchivoComision.cpp
        ArchivoInscripcionComision.cpp
        ArchivoExamen.cpp
        ArchivoCorrelativa.cpp
        ArchivoPersona.cpp
        utils.cpp
        ManagerDocente.cpp
        ManagerCorrelativa.cpp
        ManagerInscripcionComision.cpp
)

target_link_libraries(runTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
