#pragma once
#include <string>

// Funciones de utilidad general
std::string cargarCadena();
int buscarMaximo(int vec[], int cant);

void clearScreen();
void pauseScreen();

// Funciones auxiliares para reportes y estadísticas
float calcularPromedioAlumno(int legajo);
int contarMateriasAprobadas(int legajo);
int contarMateriasPromocionadas(int legajo);
int contarMateriasRegulares(int legajo);
int contarMateriasLibres(int legajo);
int contarInscriptosEnComision(int idComision);
std::string quitarAcentos(const char* texto);
std::string validarTelefono(const char* mensaje);
std::string validarDNI(const char* mensaje);
bool validarEmail(const std::string& email);
std::string pedirEmail(const char* mensaje);


