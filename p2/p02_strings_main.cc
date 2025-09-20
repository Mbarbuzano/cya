// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica -:
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: p02_strings_main.cc
// Contenido: la función main del proyecto 

#include "chain.h"

void ModoDeEmpleo() {
  std::cout << "Modo de empleo: ./p02_strings filein.txt fileout.txt opcode" << std::endl;
  std::cout << "Pruebe: './p02_strings --help' para más información." << std::endl;
}

void Info() {
  std::cout << "Este programa está diseñado para leer diferentes cadenas que recibe de ficheros de entrada.\n"
            << "Especifique los ficheros de entrada y salida para que funcione correctamente.\n";
}

int main(int argc, char **argv[]) {
  if (argc > 1 && std::string(argv[4]) == "--help") {
    Info();
    return 0;
  }
  if (argc == 1) {
    ModoDeEmpleo();
    return 1;
  }

  std::string filein{argv[1]};
}