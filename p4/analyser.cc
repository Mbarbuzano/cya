// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: analyser.cc
// Contenido: implementación de la clase analizador

#include "analyser.h"

void Analyser::DetectComment(std::string& line, int& lineNumber, std::ifstream& file) {
  // --- 1. Comprobamos si hay un comentario en la línea ---
  size_t single_pos = line.find("//");
  size_t multi_pos = line.find("/*");

  // Si no hay ningún tipo de comentario, salimos
  if (single_pos == std::string::npos && multi_pos == std::string::npos) return;

  // --- 2. Comentario de una sola línea ---
  if (single_pos != std::string::npos && (multi_pos == std::string::npos || single_pos < multi_pos)) {
    std::string contenido = line.substr(single_pos);  // desde "//" hasta el final
    std::string tipo = (comentarios_.empty()) ? "description" : "single";
    comentarios_.push_back(Comment(tipo, lineNumber, lineNumber, contenido));
    return;
  }

  // --- 3. Comentario multilínea ---
  if (multi_pos != std::string::npos) {
    std::string contenido = line.substr(multi_pos) + "\n";
    int start_line = lineNumber;

    // Si ya termina en la misma línea
    if (line.find("*/", multi_pos) != std::string::npos) {
      int end_line = lineNumber;
      std::string tipo = (comentarios_.empty()) ? "description" : "multi";
      comentarios_.push_back(Comment(tipo, start_line, end_line, contenido));
      return;
    }

    // Si no, seguimos leyendo líneas hasta encontrar "*/"
    while (std::getline(file, line)) {
      ++lineNumber;
      contenido += line + "\n";
      if (line.find("*/") != std::string::npos) {
        int end_line = lineNumber;
        std::string tipo = (comentarios_.empty()) ? "description" : "multi";
        comentarios().push_back(Comment(tipo, start_line, end_line, contenido));
        return;
      }
    }
  }
}

void Analyser::DetectVariable(const std::string& line, const int& lineNumber) {
  // --- 1. Filtro rápido ---
  // Si no hay int ni double, o si parece un bucle for, salimos
  if ((line.find("int") == std::string::npos && line.find("double") == std::string::npos) ||
      line.find("for(") != std::string::npos) {
    return;
  }

  // --- 2. Definimos la expresión regular ---
  // Captura: tipo, nombre, valor (si lo hay)
  std::regex varRegex(R"(^(?:\s*)(int|double)\s+([a-zA-Z_]\w*)(?:\s*=\s*([^;]+))?;)");
  std::smatch match;

  // --- 3. Intentamos buscar coincidencia ---
  if (std::regex_search(line, match, varRegex)) {
    std::string type = match[1].str();
    std::string name = match[2].str();

    bool initialized = match[3].matched;
    std::string value = initialized ? match[3].str() : "";

    // --- 4. Creamos y almacenamos la variable ---
    variables().push_back(Variable(type, name, lineNumber, initialized, value));
  }
}

void Analyser::DetectLoop(const std::string& line, const int& lineNumber) {
  // --- 1. Filtro rápido ---
  // Solo seguimos si la línea contiene 'for' o 'while'
  if (line.find("for") == std::string::npos && line.find("while") == std::string::npos)
    return;

  // --- 2. Expresión regular ---
  // Busca 'for (' o 'while (', permitiendo espacios previos
  std::regex loopRegex(R"(^\s*(for|while)\s*\()");
  std::smatch match;

  // --- 3. Si hay coincidencia ---
  if (std::regex_search(line, match, loopRegex)) {
    std::string tipo = match[1].str();  // "for" o "while"
    bucles().push_back(Loop(tipo, lineNumber));
  }
}

void Analyser::DetectMain(const std::string& line, const int& lineNumber) {
  // --- 1. Filtro rápido ---
  // Si la línea no contiene "main", salimos
  if (line.find("main") == std::string::npos) return;

  // --- 2. Expresión regular ---
  // Detecta la declaración típica de main:
  // int main() o int main(int argc, char* argv[])

  std::regex mainRegex(R"(\bint\s+main\s*\()");
  if (std::regex_search(line, mainRegex)) {
    set_func_main(true); // atributo privado bool de la clase Analyser
  }
}