// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: loop.cc
// Contenido: implementación de la clase bucle

#include "loop.h"

std::ostream& operator<<(std::ostream& os, const Loop& buc) {
  os << "[Line " << buc.linea() << "] LOOP: " << buc.tipo() << "\n";
  return os;
}