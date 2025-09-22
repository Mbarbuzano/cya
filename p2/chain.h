// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: chain.h
// Contenido: declaración de la clase cadena

#ifndef CHAIN_H_
#define CHAIN_H_

#include "symbol.h"

class Chain {
 public:
  Chain() { }
  Chain(const std::vector<Symbol>& chain) : cadena_{chain} { }

  std::vector<Symbol> cadena() const {
    return cadena_;
  }

  int longitud() const {
    return cadena().size();
  }

  std::vector<Symbol> inversa();
  std::set<Chain> prefijos() const;
  std::set<Chain> sufijos() const;

 private:
  std::vector<Symbol> cadena_;
};

std::ostream& operator<<(std::ostream& os, const Chain& chain);
std::ostream& operator<<(std::ostream& os, const std::set<Chain>& cadenas);

#endif