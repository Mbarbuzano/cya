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

  std::getline(entrada, line);
  int num_no_terminales{std::stoi(line)};

  for (int i{0}; i < num_no_terminales; ++i) {
    std::string no_terminal;
    std::getline(entrada, no_terminal);
    no_terminales_.push_back(no_terminal);
  }
  std::getline(entrada, line);
  int num_producciones{std::stoi(line)};
  producciones_.clear();

  for (int i{0}; i < num_producciones; ++i) {
    std::string linea;
    std::getline(entrada, linea);

    if (linea.empty()) {
      --i;  // por si hay líneas vacías accidentales
      continue;
    }

    // Buscar el primer espacio para separar izquierda y derecha
    size_t espacio = linea.find(' ');
    if (espacio == std::string::npos) {
      throw std::runtime_error("Producción mal formada: " + linea);
    }

    Production prod;
    prod.left = linea.substr(0, espacio);
    std::string parte_derecha = linea.substr(espacio + 1);

    // Rellenar el vector right con cada símbolo (carácter)
    for (char c : parte_derecha) {
      std::string simbolo(1, c);  // convierte el carácter a string
      prod.right.push_back(simbolo);
    }

    producciones_.push_back(prod);
  }

}