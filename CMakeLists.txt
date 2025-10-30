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
        ArchivoExamen.cpp
        ArchivoComision.cpp
        ArchivoInscripcion.cpp
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
        MenuPrincipal.cpp
        MenuAdmin.cpp
        MenuAbmCarreras.cpp
        MenuAbmComisiones.cpp
        MenuAbmMaterias.cpp
        MenuAlumno.cpp
        MenuDocente.cpp
        MenuUtilitarios.cpp
        PrincipalManager.cpp
        AlumnoManager.cpp
        ExamenManager.cpp
        ComisionManager.cpp
        MenuCopiaSeguridad.cpp
        MenuDatosCSV.cpp

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
        Inscripcion.cpp
        Materia.cpp
        Persona.cpp
        Validacion.cpp
        ArchivoComision.h
        ArchivoComision.cpp
        ArchivoInscripcion.h
        ArchivoInscripcion.cpp
        ArchivoExamen.h
        ArchivoExamen.cpp
        ArchivoCorrelativa.h
        ArchivoCorrelativa.cpp
        ArchivoPersona.h
        ArchivoPersona.cpp
        AlumnoManager.h
        AlumnoManager.cpp
        ExamenManager.h
        ExamenManager.cpp
        ComisionManager.h
        ComisionManager.cpp
)

target_link_libraries(runTests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
