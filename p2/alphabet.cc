// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: alphabet.cc
// Contenido: implementación de la clase alfabeto

#include "alphabet.h"

std::ostream& operator<<(std::ostream& os, const Alphabet& alfabeto) {
  std::set<Symbol> alphabet = alfabeto.simbolos();
  os << "{";
  bool first = true;
  for (const auto& a : alphabet) {
    if (!first) {
      os << ", ";
    }
    os << a;
    first = false;
  }
  os << "}\n";
  
  return os;
}