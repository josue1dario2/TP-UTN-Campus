#pragma once
#include <string>

class Validacion {
public:
    static int  validarEntero(const std::string& mensaje);
    static int  validarEnteroNoNegativo(const std::string& mensaje);
    static int  validarEnteroEnRango(const std::string& mensaje, int minV, int maxV);

    static bool validarBool(const std::string& mensaje);

    static bool validarLongitudCadena(const std::string& cadena,
                                      std::size_t longMininaCadena,
                                      std::size_t longMaximaCadena);

    static bool validadCaracteresProhibidos(const std::string& cadena,
                                            const std::string& caracteresProhibidos);

    static bool validarCadena(const std::string& cadena,
                              std::size_t longMininaCadena,
                              std::size_t longMaximaCadena,
                              const std::string& caracteresProhibidos = "");

    static std::string pedirEntradaCadena(const std::string& mensaje,
                                          std::size_t longMininaCadena,
                                          std::size_t longMaximaCadena,
                                          const std::string& caracteresProhibidos = "");
    static bool desearAccionar(std::string mensaje);
};
