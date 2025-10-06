// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: main.cc
// Contenido: fichero principal del programa con la función main

#include "analyser.h"

void ModoDeEmpleo() {
  std::cout << "Modo de uso: ./p04_code_analyzer [fichero de código].cc [fichero de salida].txt\n";
}


int main(int argc, char* argv[]) {
  if (argc == 1) ModoDeEmpleo();

  return 0;
}