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

#include "automaton.h"

Automaton::Automaton(const std::string& input) {
  std::ifstream file(input);
  if (!file.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + input);
  }

  std::string linea;
  if (std::getline(file, linea)) {
    throw std::runtime_error("El archivo está vacío");
  }

  for (char c : linea) {
    if (c != ' ') alfabeto_.insert(c);
  }

  if (!std::getline(file, linea)) throw std::runtime_error("Falta número de estados.");
  n_estados_ = std::stoi(linea);

  if (!std::getline(file, linea)) throw std::runtime_error("Falta estado inicial.");
  inicial_ = std::stoi(linea);

    // Leer líneas siguientes: definición de cada estado
    while (std::getline(file, linea)) {
      std::istringstream ss(linea);
      int id, num_trans;
      int es_final;
      ss >> id >> es_final >> num_trans;
      if (es_final) finales_.insert(id);

      for (int i = 0; i < num_trans; ++i) {
        char simbolo;
        int destino;
        ss >> simbolo >> destino;
        transiciones_[id][simbolo].insert(destino);
      }
    }
}