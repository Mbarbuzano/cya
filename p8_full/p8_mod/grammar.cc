// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 8: gramáticas en C++
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/11/2025
// Archivo: grammar.cc
// Contenido: implementación de la clase gramática

#include "grammar.h"

Grammar::Grammar(const std::string& input) {
  std::ifstream entrada{input};
  if (!entrada.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo de entrada: " + input);
  }

  std::string line;
  std::getline(entrada, line);
  int num_terminales = std::stoi(line);

  for (int i{0}; i < num_terminales; ++i) {
    std::string terminal;
    std::getline(entrada, terminal);
    terminales_.push_back(terminal);
  }

  std::getline(entrada, line);
  int num_no_terminales{std::stoi(line)};

  for (int i{0}; i < num_no_terminales; ++i) {
    std::string no_terminal;
    std::getline(entrada, no_terminal);
    no_terminales_.push_back(no_terminal);
  }
  std::getline(entrada, line);
  int num_producciones{std::stoi(line)};
  producciones_.clear();

  for (int i{0}; i < num_producciones; ++i) {
    std::string linea;
    std::getline(entrada, linea);

    if (linea.empty()) {
      --i;  // por si hay líneas vacías accidentales
      continue;
    }

    // Buscar el primer espacio para separar izquierda y derecha
    size_t espacio = linea.find(' ');
    if (espacio == std::string::npos) {
      throw std::runtime_error("Producción mal formada: " + linea);
    }

    Production prod;
    prod.left = linea.substr(0, espacio);
    std::string parte_derecha = linea.substr(espacio + 1);

    // Rellenar el vector right con cada símbolo (carácter)
    for (char c : parte_derecha) {
      std::string simbolo(1, c);  // convierte el carácter a string
      prod.right.push_back(simbolo);
    }

    producciones_.push_back(prod);
  }
}

void Grammar::WriteToFile(const std::string& fileout) const {
  // Abrir el archivo de salida
  std::ofstream salida{fileout};
  if (!salida.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo de salida: " + fileout);
  }

  // --- Escribir terminales ---
  salida << terminales_.size() << "\n";
  for (const auto& t : terminales_) {
    salida << t << "\n";
  }

  // --- Escribir no terminales ---
  salida << no_terminales_.size() << "\n";
  for (const auto& nt : no_terminales_) {
    salida << nt << "\n";
  }

  // --- Escribir producciones ---
  salida << producciones_.size() << "\n";
  for (const auto& prod : producciones_) {
    salida << prod.left << " ";

    // La parte derecha se concatena sin espacios, igual que en los .gra
    for (const auto& symbol : prod.right) {
      salida << symbol;
    }

    salida << "\n";
  }

  salida.close();  // cerrar el archivo explícitamente
}

void Grammar::ReplaceTerminalsInRules() {
  std::map<std::string, std::string> terminal_to_variable;

  // Crear variables nuevas para cada terminal (Ca, Cb, ...)
  for (const auto& terminal : terminales_) {
    std::string new_var = "C" + terminal;
    terminal_to_variable[terminal] = new_var;
    no_terminales_.push_back(new_var);

    Production prod;
    prod.left = new_var;
    prod.right.push_back(terminal);
    producciones_.push_back(prod);
  }

  // Reemplazar terminales dentro de producciones largas
  for (auto& prod : producciones_) {
    if (prod.right.size() >= 2) {
      for (auto& symbol : prod.right) {
        if (std::find(terminales_.begin(), terminales_.end(), symbol) != terminales_.end()) {
          symbol = terminal_to_variable[symbol];
        }
      }
    }
  }
}

void Grammar::BreakLongProductions() {
  std::vector<Production> nuevas_producciones;

  for (auto& prod : producciones_) {
    if (prod.right.size() <= 2) {
      nuevas_producciones.push_back(prod);
      continue;
    }

    // Necesitamos crear nuevos no terminales intermedios
    std::string left = prod.left;
    for (size_t i = 0; i < prod.right.size() - 2; ++i) {
      std::string new_var = "D" + std::to_string(no_terminales_.size());
      no_terminales_.push_back(new_var);

      Production nueva;
      nueva.left = left;
      nueva.right = { prod.right[i], new_var };
      nuevas_producciones.push_back(nueva);

      left = new_var; // el siguiente eslabón usa este nuevo no terminal
    }

    // Última regla binaria
    Production ultima;
    ultima.left = left;
    ultima.right = { prod.right[prod.right.size() - 2], prod.right.back() };
    nuevas_producciones.push_back(ultima);
  }

  producciones_ = nuevas_producciones;
}

void Grammar::RemoveEmptyProductions() {
  std::set<std::string> anulables;

  // Buscar símbolos que producen ε directamente
  for (const auto& prod : producciones_) {
    if (prod.right.size() == 1 && prod.right[0] == "&") {
      anulables.insert(prod.left);
    }
  }

  std::vector<Production> nuevas;
  for (const auto& prod : producciones_) {
    if (prod.right.size() == 1 && prod.right[0] == "&") continue;

    // Generar variantes eliminando símbolos anulables
    size_t n = prod.right.size();
    std::vector<int> indices;
    for (size_t i = 0; i < n; ++i) {
      if (anulables.count(prod.right[i])) indices.push_back(i);
    }

    // Añadir combinaciones con símbolos anulados
    for (int mask = 0; mask < (1 << indices.size()); ++mask) {
      Production variante = prod;
      for (size_t j = 0; j < indices.size(); ++j) {
        if (mask & (1 << j)) variante.right[indices[j]] = "";
      }
      std::vector<std::string> right_no_vacios;
      for (auto& s : variante.right) if (!s.empty()) right_no_vacios.push_back(s);
      if (!right_no_vacios.empty()) {
        variante.right = right_no_vacios;
        nuevas.push_back(variante);
      }
    }
  }

  // Reemplazar y restaurar S → & si procede
  producciones_ = nuevas;
  if (anulables.count(simbolo_inicial_)) {
    Production p;
    p.left = simbolo_inicial_;
    p.right = { "&" };
    producciones_.push_back(p);
  }
}

void Grammar::RemoveUnitProductions() {
  std::map<std::string, std::set<std::string>> unitarias;
  for (const auto& nt : no_terminales_) {
    unitarias[nt].insert(nt);
  }

  // Construir la clausura de producciones unitarias
  bool cambio = true;
  while (cambio) {
    cambio = false;
    for (const auto& prod : producciones_) {
      if (prod.right.size() == 1 && 
          std::find(no_terminales_.begin(), no_terminales_.end(), prod.right[0]) != no_terminales_.end()) {
        std::string A = prod.left;
        std::string B = prod.right[0];
        size_t antes = unitarias[A].size();
        unitarias[A].insert(unitarias[B].begin(), unitarias[B].end());
        if (unitarias[A].size() > antes) cambio = true;
      }
    }
  }

  // Generar nuevas producciones sin las unitarias
  std::vector<Production> nuevas;
  for (const auto& prod : producciones_) {
    if (prod.right.size() == 1 && 
        std::find(no_terminales_.begin(), no_terminales_.end(), prod.right[0]) != no_terminales_.end()) {
      continue; // saltar unitarias
    }
  }

  for (const auto& [A, clausura] : unitarias) {
    for (const auto& B : clausura) {
      for (const auto& prod : producciones_) {
        if (prod.left == B && 
            !(prod.right.size() == 1 && std::find(no_terminales_.begin(), no_terminales_.end(), prod.right[0]) != no_terminales_.end())) {
          Production nueva = prod;
          nueva.left = A;
          nuevas.push_back(nueva);
        }
      }
    }
  }

  producciones_ = nuevas;
}

void Grammar::Chomsky() {
  RemoveEmptyProductions();
  RemoveUnitProductions();
  ReplaceTerminalsInRules();
  BreakLongProductions();
}

void Grammar::ReplaceSingleTerminalProductions() {
  std::map<std::string, std::string> reemplazos;

  // 1. Buscar no terminales con una sola producción formada solo por terminales
  for (const auto& nt : no_terminales_) {
    std::vector<std::vector<std::string>> rhs_list;
    for (const auto& prod : producciones_) {
      if (prod.left == nt) {
        rhs_list.push_back(prod.right);
      }
    }

    if (rhs_list.size() == 1) {
      const auto& rhs = rhs_list[0];
      bool solo_terminales = true;
      std::string cadena;

      for (const auto& simbolo : rhs) {
        // Si no es terminal, no vale
        if (std::find(terminales_.begin(), terminales_.end(), simbolo) == terminales_.end()) {
          solo_terminales = false;
          break;
        }
        cadena += simbolo;
      }

      if (solo_terminales) {
        reemplazos[nt] = cadena;
      }
    }
  }

  // 2. Reemplazar en las demás producciones
  for (auto& prod : producciones_) {
    for (auto& simbolo : prod.right) {
      if (reemplazos.count(simbolo)) {
        // Reemplazar el no terminal por su cadena expandida
        std::string expansion = reemplazos[simbolo];
        simbolo = expansion;  // reemplaza en posición
      }
    }
  }

  // 3. Eliminar las producciones originales de esos no terminales
  std::vector<Production> nuevas_producciones;
  for (const auto& prod : producciones_) {
    if (!reemplazos.count(prod.left)) {
      nuevas_producciones.push_back(prod);
    }
  }
  producciones_ = nuevas_producciones;
}
