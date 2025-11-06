// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: gramáticas en C++
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/11/2025
// Archivo: main.cc
// Contenido: archivo principal de compilación

#include "grammar.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n"
              <<  "Pruebe Grammar2CNF --help para mas informacion.\n";
    return 1;
  }

  if (argc == 2 && std::string(argv[1]) == "--help") {
    std::cout << "Este archivo toma ficheros del tipo .gra para tomar"
              << "gramáticas y pasarlas a Forma normal de chomsky\n";
    return 1;
  }

  std::string entrada{argv[1]};
  std::string salida{argv[2]};
  Grammar gramatica{entrada};
  gramatica.Chomsky();
  gramatica.WriteToFile(salida);
  return 0;
}