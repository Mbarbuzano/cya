// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: comment.cc
// Contenido: implementación de la clase comentario

#include "comment.h"

std::ostream& operator<<(std::ostream& os, const Comment& com) {
  if (com.linea_ini() == com.linea_fin())
  os << "[Line " << com.linea_ini() << "] ";

  else
  os << "[Line " << com.linea_ini() << "-" << com.linea_fin() << "] ";

  if (com.tipo() == "description") {
  os << "DESCRIPTION:\n";
  } 
  else {
    os << "COMMENT: " << com.contenido();
  }

  return os;
}