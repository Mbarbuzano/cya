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

std::set<int> Automaton::Move(const std::set<int>& estados, char simbolo) const {
  std::set<int> resultado;

  for (int estado : estados) {
    auto it_estado = transiciones_.find(estado);
    if (it_estado == transiciones_.end()) continue;  // sin transiciones

    auto it_simbolo = it_estado->second.find(simbolo);
    if (it_simbolo == it_estado->second.end()) continue;

    // Insertar todos los destinos posibles
    resultado.insert(it_simbolo->second.begin(), it_simbolo->second.end());
  }

  return resultado;
}

std::set<int> Automaton::EpsilonClosure(const std::set<int>& estados) const {
  std::set<int> closure = estados;
  std::queue<int> pendientes;

  for (int e : estados) pendientes.push(e);

  while (!pendientes.empty()) {
    int estado = pendientes.front();
    pendientes.pop();

    auto it_estado = transiciones_.find(estado);
    if (it_estado == transiciones_.end()) continue;

    auto it_eps = it_estado->second.find('&');
    if (it_eps == it_estado->second.end()) continue;

    for (int destino : it_eps->second) {
      if (closure.insert(destino).second) { // si se añadió nuevo
        pendientes.push(destino);
      }
    }
  }

  return closure;
}

bool Automaton::Intersecta(const std::set<int>& a, const std::set<int>& b) const {
  for (int x : a) {
    if (b.count(x)) return true;
  }
  return false;
}


bool Automaton::ProcesarCadena(const std::string& cadena) const {
  std::set<int> actuales = EpsilonClosure({inicial_});

  for (char simbolo : cadena) {
    if (!alfabeto_.count(simbolo)) {
      // símbolo no reconocido → rechazo inmediato
      return false;
    }

    std::set<int> siguientes = Move(actuales, simbolo);
    actuales = EpsilonClosure(siguientes);
  }

  return Intersecta(actuales, finales_);
}
