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

// En el método inversa() se usa un vector para ingresar los símbolos 
// recorriendo el vector desde el final al principio
Chain Chain::inversa() const {
  std::vector<Symbol> result;
  for (auto it = cadena().rbegin(); it != cadena().rend(); ++it) {
    result.push_back(*it);
  }
  return Chain{result};
}

// Primero se inserta la cadena vacía y se usa std::set para evitar duplicados
// Se va insertando en un vector temporal 
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

std::set<Chain> Chain::subcadenas() const {
  std::set<Chain> result;

  // Subcadena vacía
  result.insert(Chain{});

  // Recorrer todos los posibles inicios
  for (size_t i = 0; i < cadena().size(); ++i) {
    // Recorrer todos los posibles finales
    for (size_t j = i; j < cadena().size(); ++j) {
      // Extraer la subcadena symbols_[i..j]
      std::vector<Symbol> temp(cadena().begin() + i, cadena().begin() + j + 1);
      result.insert(Chain{temp});
    }
  }

  return result;
}

// Para concatenar
Chain Chain::operator+(const Chain& other) const {
  std::vector<Symbol> result = cadena();  // copia de la cadena actual
  result.insert(result.end(), other.cadena().begin(), other.cadena().end());
  return Chain{result};
}


bool Chain::operator<(const Chain& other) const {
  if (longitud() != other.longitud()) {
    return longitud() < other.longitud();
  }
  return cadena() < other.cadena();
}

std::ostream& operator<<(std::ostream& os, const Chain& chain) {
  if (chain.longitud() == 0) os << "&";
  else {
    for (int i{0}; i < chain.longitud(); ++i) {
      os << chain.cadena()[i];
    }
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<Chain>& set) {
  os << "{";
  for (auto it = set.begin(); it != set.end(); ++it) {
    os << *it;                       
    if (std::next(it) != set.end()) {
      os << ", ";
    }
  }
  os << "}";
  return os;
}
