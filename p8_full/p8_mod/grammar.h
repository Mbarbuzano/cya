// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: gramáticas en C++
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/11/2025
// Archivo: grammar.h
// Contenido: declaración de la clase gramática

#ifndef GRAMMAR_H_
#define GRAMMAR_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>

struct Production {
  std::string left;
  std::vector<std::string> right;
};

class Grammar {
 public:
  Grammar() { }
  Grammar(const std::string& input);

  void WriteToFile(const std::string& fileout) const;

  void ReplaceTerminalsInRules();
  void BreakLongProductions();
  void RemoveEmptyProductions();
  void RemoveUnitProductions();

  void Chomsky();
  void ReplaceSingleTerminalProductions();
  
 private:
  std::vector<std::string> terminales_;
  std::vector<std::string> no_terminales_;
  std::string simbolo_inicial_;
  std::vector<Production> producciones_;
};

#endif