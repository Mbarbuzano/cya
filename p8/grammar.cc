// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: gramáticas en C++
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/11/2025
// Archivo: grammar.cc
// Contenido: implementación de la clase gramática

#include "grammar.h"

Grammar::Grammar(const std::string& input) {
  std::ifstream entrada{input};
  if (!entrada.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo de entrada: " + input);
  }

  std::string line;
  std::getline(entrada, line);
  int num_terminales = std::stoi(line);

  for (int i{0}; i < num_terminales; ++i) {
    std::string terminal;
    std::getline(entrada, terminal);
    terminales_.push_back(terminal);
  }
}