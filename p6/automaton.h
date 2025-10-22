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
#include <queue>
#include <set>
#include <map>

class Automaton {
 public:
  Automaton() {}
  Automaton(const std::string& filename);
  bool ProcesarCadena(const std::string& cadena) const;

 private:
  std::set<char> alfabeto_;
  int n_estados_;
  int inicial_;
  std::set<int> finales_;
  std::map<int, std::map<char, std::set<int>>> transiciones_;

  std::set<int> Move(const std::set<int>& estados, char simbolo) const;
  std::set<int> EpsilonClosure(const std::set<int>& estados) const;
  bool Intersecta(const std::set<int>& a, const std::set<int>& b) const;
};


#endif