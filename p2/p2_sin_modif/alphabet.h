// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: alphabet.h
// Contenido: declaración de la clase alfabeto

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include "chain.h"

class Alphabet {
 public:
  Alphabet() { }
  Alphabet(std::set<Symbol> symbols) : simbolos_{symbols} { }

  std::set<Symbol> simbolos() const {
    return simbolos_;
  }

 private:
  std::set<Symbol> simbolos_;
};

std::ostream& operator<<(std::ostream& os, const Alphabet& alfabeto);

#endif