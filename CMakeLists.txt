cmake_minimum_required(VERSION 3.16)
project(TP_UTN_Campus)

set(CMAKE_CXX_STANDARD 20)

# -----------------------------
# Ejecutable principal
# -----------------------------
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
        utils.cpp
        ManagerInscripcionComision.cpp
        ManagerReportes.cpp
)
