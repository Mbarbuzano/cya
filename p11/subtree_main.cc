// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/12/2025
// Archivo: point_cloud_main.cc
// Contenido: archivo principal de compilación del proyecto

#include "subtree.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    ModoDeEmpleo();
    return 1;
  }

  if (std::string(argv[1]) == "--help") {
    Ayuda();
    return 1;
  }

  return 0;
}