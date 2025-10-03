// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: loop.h
// Contenido: declaración de la clase bucle

#ifndef LOOP_H_
#define LOOP_H_

#include "variable.h"

class Loop {
 public:
  Loop() { }
  Loop(const std::string type, const int line) : tipo_{type}, linea_{line} { }

  std::string tipo() const {return tipo_;}
  int linea() const {return linea_;}

 private:
  std::string tipo_;
  int linea_;
};

std::ostream& operator<<(std::ostream& os, const Loop& buc);

#endif