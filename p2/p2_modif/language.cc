// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: language.cc
// Contenido: implementación de la clase lenguaje

#include "language.h"

std::ostream& operator<<(std::ostream& os, const Language& leng) {
  os << "{";
  std::set<Chain> indice{leng.lenguaje()};
  for (auto it = indice.begin(); it != indice.end(); ++it) {
    os << *it;                       
    if (std::next(it) != indice.end()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}

Language Language::concatenar(const Language& leng) {
  Language resultado;

  for (auto it1 = lenguaje().begin(); it1 != lenguaje().end(); ++it1) {
    for (auto it2 = leng.lenguaje().begin(); it2 != leng.lenguaje().end(); ++it2) {
      resultado.insertar(*it1 + *it2);
    }
  }

  return resultado;
}


