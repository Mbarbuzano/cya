// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: variable.cc
// Contenido: implementación de la clase variable

#include "variable.h"

std::ostream& operator<<(std::ostream& os, const Variable& var) {
  os << "[Line " << var.linea() << "] " << var.tipo() << ": "
     << var.nombre();
  if (var.inicializado()) {
      os << " = " << var.valor();
  }
  return os;
}