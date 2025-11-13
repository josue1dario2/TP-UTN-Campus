#include <gtest/gtest.h>
#include "../Alumno.h"
#include "../Direccion.h"
#include "../Fecha.h"

using namespace std;

// --- TEST 1: Set y Get de legajo ---
TEST(AlumnoTest, SetAndGetLegajo) {
    Alumno a;
    a.setLegajo(1234);
    EXPECT_EQ(a.getLegajo(), 1234);
}

// --- TEST 2: Set y Get de FechaIngreso ---
TEST(AlumnoTest, SetAndGetFechaIngreso) {
    Fecha f(10, 3, 2024);
    Alumno a;
    a.setFechaIngreso(f);

    EXPECT_EQ(a.getFechaIngreso().getDia(), 10);
    EXPECT_EQ(a.getFechaIngreso().getMes(), 3);
    EXPECT_EQ(a.getFechaIngreso().getAnio(), 2024);
}

// --- TEST 3: Constructor parametrizado ---
TEST(AlumnoTest, ConstructorCompleto) {
    Direccion dir("San Martín", "123", "Rosario", 2000, 1);
    Fecha nacimiento(15, 7, 1991);
    Fecha ingreso(1, 3, 2024);

    Alumno a(100, 12345678, "Josue", "Solis", "3415555555", "josue@mail.com",
             dir, nacimiento, ingreso, false);

    EXPECT_EQ(a.getLegajo(), 100);
    EXPECT_EQ(a.getDni(), 12345678);
    EXPECT_STREQ(a.getNombre(), "Josue");
    EXPECT_STREQ(a.getApellido(), "Solis");
    EXPECT_STREQ(a.getTelefono(), "3415555555");
    EXPECT_STREQ(a.getEmail(), "josue@mail.com");
    EXPECT_EQ(a.getFechaIngreso().getAnio(), 2024);
    EXPECT_EQ(a.getFechaNacimiento().getAnio(), 1991);
}

// --- TEST 4: mostrar() no lanza excepciones ---
TEST(AlumnoTest, MostrarNoFalla) {
    Alumno a;
    a.setLegajo(1);
    a.setNombre("Josue");
    a.setApellido("Solis");
    EXPECT_NO_THROW(a.mostrar());
}

// --- TEST 5: cargar() no rompe el flujo ---
TEST(AlumnoTest, CargarNoFalla) {
    Alumno a;
    EXPECT_NO_THROW(a.cargar());
}
