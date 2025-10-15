cmake_minimum_required(VERSION 3.31)
project(TP_UTN_Campus)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP_UTN_Campus
        main.cpp
        Direccion.cpp
        MesaDocente.cpp
        MesaExamen.cpp
        Fecha.cpp
        OfertaAcademica.cpp
        Validacion.cpp
        Cuota.h
        Cuota.cpp
        Alumno_menu.h
        Alumno_menu.cpp
        Profesor_menu.h
        Profesor_menu.cpp
        Tesoreria_menu.h
        Tesoreria_menu.cpp   # <-- agregar
)