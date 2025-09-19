// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: symbol.h
// Contenido: declaración de la clase símbolo

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <iostream>
#include <string>

class Symbol {
 public:
  Symbol() { }
  Symbol(const char symbol) : simbolo_{symbol} { }
  
  char simbolo() const { return simbolo_; }

  void operator=(const char& symbol);
  bool operator<(const Symbol& other) const;
  bool operator==(const Symbol& symbol);
  
 private:
  char simbolo_;
};

#endif