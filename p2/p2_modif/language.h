// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 2: Cadenas y Lengugajes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: language.h
// Contenido: declaración de la clase lenguaje

#include "alphabet.h"

#ifndef LANGUAGE_H_
#define LANGUAGE_H_

class Language {
 public:
  Language() {}
  Language(const std::set<Chain>& cadenas) : lenguaje_{cadenas} { }

  std::set<Chain> lenguaje() const { return lenguaje_; }

  void insertar(const Chain& chain) {
    lenguaje().insert(chain);
  }

  Language concatenar(const Language& leng);

 private:
  std::set<Chain> lenguaje_;
};

std::ostream& operator<<(std::ostream& os, const Language& leng);

#endif