cmake_minimum_required(VERSION 3.16)
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
        Materia.cpp
        Persona.cpp
        Validacion.cpp
        ValidadorAcceso.cpp
        MenuPrincipal.cpp
        MenuAdmin.cpp
        MenuAbmCarrera.cpp
        MenuAbmComision.cpp
        MenuAbmMateria.cpp
        MenuAlumno.cpp
        MenuDocente.cpp
        MenuUtilitarios.cpp
        MenuDatosCSV.cpp
        MenuCopiaSeguridad.cpp
        MenuAbmExamen.cpp
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
        MenuAbmCorrelativa.cpp
        ArchivoCorrelativa.cpp
        ManagerCorrelativa.cpp
        MenuAbmCorrelativa.cpp
        utils.cpp
        ManagerInscripcionComision.cpp
)

# --- GoogleTest setup ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Ejecutable de tests ---
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
        ManagerAlumno.cpp
        ManagerCarrera.cpp
        ManagerMateria.cpp
        ManagerDocente.cpp
        ManagerCorrelativa.cpp
        ManagerInscripcionComision.cpp
        ManagerExamen.cpp
        ManagerComision.cpp
        InscripcionComision.cpp
)

target_link_libraries(runTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)

# --- Ejecutable inicializador de datos ---
add_executable(inicializar_datos
        inicializar_datos.cpp
        Materia.cpp
        ArchivoMateria.cpp
        Carrera.cpp
        ArchivoCarrera.cpp
        Correlativa.cpp
        ArchivoCorrelativa.cpp
        Fecha.cpp
)
