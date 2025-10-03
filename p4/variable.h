// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: variable.h
// Contenido: declaración de la clase variable

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <iostream>
#include <regex>

class Variable {
 public:
  Variable() { }
  Variable(const std::string type, const std::string name, const int line, const bool inicialised, 
           const std::string value) : tipo_{type}, nombre_{name}, linea_{line}, inicializado_{inicialised}, valor_{value} { }

  std::string tipo() const {return tipo_;}
  std::string nombre() const {return nombre_;}
  int linea() const {return linea_;}
  bool inicializado() const {return inicializado_;}
  std::string valor() const {return valor_;}

 private:
  std::string tipo_;
  std::string nombre_;
  int linea_;
  bool inicializado_;
  std::string valor_;
};

std::ostream& operator<<(std::ostream& os, const Variable& var);

#endif