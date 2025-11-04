#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "Validacion.h"
using namespace std;

std::string cargarCadena()
{
  std::string texto;

  if(std::cin.peek() == '\n')
  {
    std::cin.ignore();
  }

  std::getline(std::cin, texto);

  return texto;
}

int buscarMaximo(int vec[], int cant){
  int indexMax = 0;
  
  for(int i=1; i<cant; i++){
    if(vec[i] > vec[indexMax]){
      indexMax = i;    
    }  
  }
  
  return indexMax;
}

void clearScreen()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pauseScreen()
{
#ifdef _WIN32
  system("pause");
#else
  cout << "Presione ENTER para continuar...";
  if (cin.peek() == '\n') cin.ignore();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif
}

