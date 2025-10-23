cmake_minimum_required(VERSION 3.31)
project(TP_UTN_Campus)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP_UTN_Campus
        main.cpp
        Direccion.cpp
        Fecha.cpp
        Validacion.cpp
        Correlativa.h
        Correlativa.cpp
        Examen.h
        Examen.cpp
        # <-- agregar
)