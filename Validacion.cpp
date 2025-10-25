#include "Validacion.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

// ------------- helpers internos -------------
static string trim(const string& s) {
    size_t i = 0, j = s.size();
    while (i < j && isspace((unsigned char)s[i])) ++i;
    while (j > i && isspace((unsigned char)s[j-1])) --j;
    return s.substr(i, j - i);
}

static string tolower_copy(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c){ return (char)tolower(c); });
    return s;
}

// ------------- enteros -------------
int Validacion::validarEntero(const string& mensaje) {
    while (true) {
        cout << mensaje;
        string entrada;
        if (!getline(cin, entrada)) { cin.clear(); continue; }
        entrada = trim(entrada);

        // permitir +/-
        if (entrada.empty()) { cout << "Entrada invalida.\n"; continue; }
        size_t k = (entrada[0] == '+' || entrada[0] == '-') ? 1u : 0u;
        bool ok = (k < entrada.size());
        for (; k < entrada.size(); ++k)
            if (!isdigit((unsigned char)entrada[k])) { ok = false; break; }
        if (!ok) { cout << "Debe ser un numero entero.\n"; continue; }

        try { return stoi(entrada); }
        catch (...) { cout << "Formato invalido.\n"; }
    }
}

int Validacion::validarEnteroNoNegativo(const string& mensaje) {
    while (true) {
        int v = validarEntero(mensaje);
        if (v >= 0) return v;
        cout << "Debe ser >= 0.\n";
    }
}

int Validacion::validarEnteroEnRango(const string& mensaje, int minV, int maxV) {
    if (minV > maxV) std::swap(minV, maxV);
    while (true) {
        int v = validarEntero(mensaje);
        if (v >= minV && v <= maxV) return v;
        cout << "Fuera de rango [" << minV << "," << maxV << "].\n";
    }
}

// ------------- booleano -------------
bool Validacion::validarBool(const string& mensaje){
    while (true) {
        cout << mensaje;
        string s;
        if (!getline(cin, s)) { cin.clear(); continue; }
        s = tolower_copy(trim(s));

        if (s == "s" || s == "si" || s == "1" || s == "true")  return true;
        if (s == "n" || s == "no" || s == "0" || s == "false") return false;

        cout << "Responda si/no (s/n, 1/0, true/false).\n";
    }
}

// ------------- cadenas -------------
bool Validacion::validarLongitudCadena(const std::string& cadena,
                                       std::size_t longMininaCadena,
                                       std::size_t longMaximaCadena) {
    if (longMaximaCadena < longMininaCadena) longMaximaCadena = longMininaCadena;
    size_t L = cadena.size();
    return (L >= longMininaCadena && L <= longMaximaCadena);
}

bool Validacion::validadCaracteresProhibidos(const std::string& cadena,
                                             const std::string& caracteresProhibidos) {
    if (caracteresProhibidos.empty()) return true;
    for (char c : cadena) {
        if (caracteresProhibidos.find(c) != string::npos) return false;
    }
    return true;
}

bool Validacion::validarCadena(const std::string& cadena,
                               std::size_t longMininaCadena,
                               std::size_t longMaximaCadena,
                               const std::string& caracteresProhibidos) {
    if (!validarLongitudCadena(cadena, longMininaCadena, longMaximaCadena)) return false;
    if (!validadCaracteresProhibidos(cadena, caracteresProhibidos))           return false;
    return true;
}

std::string Validacion::pedirEntradaCadena(const std::string& mensaje,
                                           std::size_t longMininaCadena,
                                           std::size_t longMaximaCadena,
                                           const std::string& caracteresProhibidos) {
    while (true) {
        cout << mensaje;
        string entrada;
        if (!getline(cin, entrada)) { cin.clear(); continue; }
        entrada = trim(entrada);

        if (!validarCadena(entrada, longMininaCadena, longMaximaCadena, caracteresProhibidos)) {
            cout << "Error: longitud [" << longMininaCadena << "," << longMaximaCadena << "]";
            if (!caracteresProhibidos.empty()) cout << " y sin caracteres prohibidos";
            cout << ". Reintente.\n";
            continue;
        }
        return entrada;
    }
}
