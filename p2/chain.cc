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

std::ostream& operator<<(std::ostream& os, const Chain& chain) {
  if (chain.length() == 0) os << "&";
  else {
    for (size_t i{0}; i < chain.length(); ++i) {
      os << chain.cadena()[i];
    }
  }
  return os;
}