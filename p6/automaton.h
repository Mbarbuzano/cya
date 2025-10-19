// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 23/10/2025
// Archivo: automaton.h
// Contenido: declaración de la clase autómata

#ifndef AUTOMATON_H_
#define AUTOMATON_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <map>

class Automaton {
 public:
  Automaton() {}
  Automaton(const std::string& input);
  
  std::set<char> alfabeto() const { return alfabeto_; }
  int n_estados() const { return n_estados_; }
  int inicial() const { return inicial_; }
  std::set<int> finales() { return finales_; }
  std::map<int, std::map<char, std::set<int>>> transiciones() { return transiciones_; }

 private:
  std::set<char> alfabeto_;
  int n_estados_;
  int inicial_;
  std::set<int> finales_;
  std::map<int, std::map<char, std::set<int>>> transiciones_;
};

#endif