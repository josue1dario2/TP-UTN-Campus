#pragma once
#include <string>

using namespace std;

class Validacion {
public:

    // Validar Enteros
    static int validarEntero(const string& mensaje);



    // Validación Fechas
    static bool esAnioBisiesto(int anio);
    static bool esFechaValidaManual(int dia, int mes, int anio);

    // Validar Bool
    static bool validarBool(const string& mensaje);


    // Validar Cadenas
    static bool validarCadena(const string& cadena, size_t longMininaCadena, size_t longMaximaCadena);
    static bool validarLongitudCadena(const string& cadena, size_t longMininaCadena, size_t longMaximaCadena);
    static bool validadCaracteresProhibidos(const string& cadena, const string& caracteresProhibidos);

    //No usado
    static string pedirEntradaCadena(const string& mensaje, size_t longMininaCadena, size_t longMaximaCadena);

};
