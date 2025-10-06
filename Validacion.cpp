
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

#include "Validacion.h"

using namespace std;

// Método genérico para validar la entrada de un entero
int Validacion::validarEntero(const string& mensaje) {

    int valor;
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada);
        stringstream ss(entrada);
        if (ss >> valor && ss.eof() && valor >= 0) {
            return valor;
        }
        cout << "Entrada inválida. Ingrese un número entero válido.\n";
    }
    //limpia el búffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

bool Validacion::validarBool(const string& mensaje){
    bool miBooleano;
    cout << mensaje;

    while (!(cin >> miBooleano)) { // Mientras el valor ingresador no sea válido
        cout << "Entrada inválida. "+ mensaje + " :";
        cin.clear(); //
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //
    }
    return miBooleano;
}


//No funciona, a corregir o rehacer
string Validacion::pedirEntradaCadena(const string& mensaje, size_t longMininaCadena, size_t longMaximaCadena) {
    string entrada;
    while (true) {

        cout << mensaje;
        //cin.ignore(); // Limpiar buffer
        // Se usa getline para leer la línea completa, incluyendo espacios
        getline(cin, entrada);

        // Se usa el método de la clase Validacion para comprobar la longitud
        if ((Validacion::validarLongitudCadena(entrada, longMininaCadena, longMaximaCadena))){

            string caracteresProhibidos="°|¬!#$%&/()=?¡¨*[];:_'~^`-+*";
            if ((Validacion::validadCaracteresProhibidos(entrada, caracteresProhibidos))){

                return entrada;
            }

        }
        /*
        else {
            cout << "Error, vuelva a ingresar el valor.";
            //cout << "Error: La cadena debe tener entre " << longMininaCadena
            //          << " y " << longMaximaCadena << " caracteres. Intenta de nuevo." << endl;
        }
        */
        cout << "Error, vuelva a ingresar el valor."<< endl;
    }
}


bool Validacion::validadCaracteresProhibidos(const string& cadena, const string& caracteresProhibidos) {
    for (char c : cadena) {
        if (caracteresProhibidos.find(c) != string::npos) {
            return false; // contiene un carácter prohibido
        }
    }
    return true; // no contiene caracteres prohibidos
}



// Implementación del nuevo método para validar la longitud de una cadena
bool Validacion::validarLongitudCadena(const string& cadena, size_t longMininaCadena, size_t longMaximaCadena) {
    size_t longitud = cadena.length(); // O cadena.size(), que es lo mismo
    return (longitud >= longMininaCadena && longitud <= longMaximaCadena);

}


bool Validacion::esAnioBisiesto(int anio){
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool Validacion::esFechaValidaManual(int dia, int mes, int anio){
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) return false;

    int diasPorMes[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Índice 0 no usado

    if (mes == 2) {
        if (esAnioBisiesto(anio)) {
            if (dia > 29) return false;
        } else {
            if (dia > 28) return false;
        }
    } else {
        if (dia > diasPorMes[mes]) return false;
    }

    return true;



}
