#include <iostream>
using namespace std;
#include "Direccion.h"

void imprimir(const Direccion &d, const char *titulo)
{
    cout << "---- " << titulo << " ----\n";
    d.mostrar();
    // Getters individuales
    cout << "getCalle(): " << d.getCalle() << "\n";
    cout << "getProvincia(): " << d.getProvincia() << "\n";
    cout << "getCiudad(): " << d.getCiudad() << "\n";
    cout << "getNumero(): " << d.getNumero() << "\n";
    cout << "getCodigoPostal(): " << d.getCodigoPostal() << "\n\n";
}

int main()
{
    // 1) Constructor por defecto
    Direccion d1;
    imprimir(d1, "Constructor por defecto (valores iniciales)");

    // 2) Constructor con parámetros válidos
    Direccion d2("San Martin", "Mendoza", "Godoy Cruz", 1234, 5501);
    imprimir(d2, "Constructor con parámetros válidos");

    // 3) Constructor con parámetros inválidos (negativos / null)
    Direccion d3(nullptr, nullptr, nullptr, -10, -999);
    imprimir(d3, "Constructor con parámetros inválidos (nullptr/negativos)");

    // 4) Método cargar() con valores válidos
    d1.cargar("Belgrano", "Buenos Aires", "CABA", 200, 1000);
    imprimir(d1, "cargar() con valores válidos");

    // 5) Setters uno por uno (válidos)
    d1.setCalle("Sarmiento");
    d1.setProvincia("San Juan");
    d1.setCiudad("Capital");
    d1.setNumero(555);
    d1.setCodigoPostal(5400);
    imprimir(d1, "Setters válidos uno por uno");

    // 6) Setters con entradas inválidas: nullptr / negativos
    d1.setCalle(nullptr);
    d1.setProvincia(nullptr);
    d1.setCiudad(nullptr);
    d1.setNumero(-1);
    d1.setCodigoPostal(-1);
    imprimir(d1, "Setters inválidos (nullptr/negativos)");

    // 7) Cadenas demasiado largas (deben caer en fallback “Desconocida” según tu validación < 50)
    // Construimos un string largo de 60 'A' (sin usar std::string para mantener C-style).
    char muyLargo[61];
    memset(muyLargo, 'A', 60);
    muyLargo[60] = '\0';

    d2.setCalle(muyLargo);
    d2.setProvincia(muyLargo);
    d2.setCiudad(muyLargo);
    imprimir(d2, "Setters con cadenas demasiado largas (fallback)");

    // 8) Caso límite: exactamente 49 caracteres (debe ser válido porque strlen < 50)
    char cuarentaYNueve[50]; // 49 letras + '\0'
    for (int i = 0; i < 49; ++i)
        cuarentaYNueve[i] = (i % 26) + 'a'; // abc... repetido
    cuarentaYNueve[49] = '\0';

    d3.setCalle(cuarentaYNueve);
    d3.setProvincia(cuarentaYNueve);
    d3.setCiudad(cuarentaYNueve);
    d3.setNumero(1);
    d3.setCodigoPostal(1);
    imprimir(d3, "Setters con longitud exactamente 49 (válido)");

    // 9) Uso sobre objeto const (requiere que getters/métodos de lectura sean const)
    const Direccion dConst("Italia", "Cordoba", "Villa Maria", 789, 5900);
    cout << "---- Objeto const (solo lectura) ----\n";
    cout << dConst.toString() << "\n";
    cout << "getCalle(): " << dConst.getCalle() << "\n\n";
    // dConst.setCalle("No se puede"); // <- esto debe fallar si lo descomentás (correcto)

    // 10) Demostración de que toString() no modifica estado y puede usarse en const
    cout << "toString() de const: " << dConst.toString() << "\n\n";

    // 11) Re-cargar con mezcla válida/invalid para ver comportamiento final
    d1.cargar("9 de Julio", nullptr, "San Rafael", -25, 5600);
    imprimir(d1, "cargar() mixto (algunas inválidas)");

    // 12) Getters directos para validar que no permiten modificar el buffer devuelto
    // Nota: Como retornan const char*, no deberías poder hacer: d1.getCalle()[0] = 'X';
    // Si intentás descomentar la próxima línea, debería dar error de compilación:
    // d1.getCalle()[0] = 'X';

    cout << "Fin de pruebas.\n";

    return 0;
}