#include <gtest/gtest.h>
#include "../Alumno.h"

TEST(AlumnoTest, CrearAlumnoCorrectamente) {
    Alumno a;
    a.setLegajo(123);
    EXPECT_EQ(a.getLegajo(), 123);
}

TEST(AlumnoTest, NombreNoVacio) {
    Alumno a;
    a.setNombre("Josue");
    EXPECT_STRNE(a.getNombre(), "");
}
