// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: chain.cc
// Contenido: implementación de la clase cadena

#include "chain.h"

std::vector<Symbol> Chain::inversa() {
  std::vector<Symbol> result;
  for (int i{cadena().size() - 1}; i >= 0; --i) {
    result.push_back(cadena()[i]);
  }
  return result;
}

std::set<Chain> Chain::prefijos() const {
  std::set<Chain> result;
  result.insert(Chain{});  

  std::vector<Symbol> temp;

  for (const auto& sym : cadena()) {
    temp.push_back(sym);
    result.insert(Chain{temp});
  }

  return result;
}

std::set<Chain> Chain::sufijos() const {
  std::set<Chain> result;
  result.insert(Chain{});

  const auto& vec = cadena();

  for (size_t i = 0; i < vec.size(); ++i) {
    std::vector<Symbol> temp(vec.begin() + i, vec.end());
    result.insert(Chain{temp});
  }

  return result;
}

std::ostream& operator<<(std::ostream& os, const Chain& chain) {
  if (chain.longitud() == 0) os << "&";
  else {
    for (size_t i{0}; i < chain.longitud(); ++i) {
      os << chain.cadena()[i];
    }
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<Chain> set) {
  
}