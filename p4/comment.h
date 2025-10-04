// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: comment.h
// Contenido: declaración de la clase comentario

#ifndef COMMENT_H_
#define COMMENT_H_

#include "loop.h"

class Comment {
 public:
  Comment() { }
  Comment(const std::string& type, const int& first_line, const int& end_line, const std::string& content) : 
          tipo_{type}, linea_ini_{first_line}, linea_fin_{end_line}, contenido_{content} {}

  std::string tipo() const { return tipo_; }
  int linea_ini() const { return linea_ini_; }
  int linea_fin() const { return linea_fin_; }
  std::string contenido() const { return contenido_; }

 private:
  std::string tipo_;
  int linea_ini_;
  int linea_fin_;
  std::string contenido_;
};

std::ostream& operator<<(std::ostream& os, const Comment& com);

#endif