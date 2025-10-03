#pragma once
#include <string>

using namespace std;

class Validacion {
public:

    static int validarEntero(const string& mensaje);

    static bool validarBool(const string& mensaje);

    static bool validarCadena(const string& cadena, size_t longMininaCadena, size_t longMaximaCadena);
    static bool validarLongitudCadena(const string& cadena, size_t longMininaCadena, size_t longMaximaCadena);
    static bool validadCaracteresProhibidos(const string& cadena, const string& caracteresProhibidos);

    //No usado
    static string pedirEntradaCadena(const string& mensaje, size_t longMininaCadena, size_t longMaximaCadena);

};
