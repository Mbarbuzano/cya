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
  size_t single_pos = line.find("//");
  size_t multi_pos = line.find("/*");

  if (single_pos == std::string::npos && multi_pos == std::string::npos) return;

  // --- 1. Detección de comentario de línea (//) ---
  if (single_pos != std::string::npos && (multi_pos == std::string::npos || single_pos < multi_pos)) {
    std::string contenido = line.substr(single_pos);
    int start_line = lineNumber;
    int end_line = lineNumber;

    // --- 1A. Si es el inicio del archivo y hay varias líneas // consecutivas ---
    if (comentarios_.empty() && lineNumber <= 3) {
      std::string bloque = contenido + "\n";

      // Leer líneas siguientes mientras empiecen por //
      std::streampos prev_pos = file.tellg();  // guarda posición actual
      std::string next;
      while (std::getline(file, next)) {
        ++lineNumber;
        if (next.find("//") == 0 || next.find(" //") == 0) {
          bloque += next + "\n";
          end_line = lineNumber;
          prev_pos = file.tellg(); // actualizar
        } else {
          // Retrocede una línea (hemos leído una no comentario)
          file.seekg(prev_pos);
          --lineNumber;
          break;
        }
      }

      comentarios_.push_back(Comment("description", start_line, end_line, bloque));
      return;
    }

    // --- 1B. Comentario simple normal ---
    comentarios_.push_back(Comment("single", start_line, end_line, contenido));
    return;
  }

  // --- 2. Comentarios multilínea (/* ... */) ---
  if (multi_pos != std::string::npos) {
    std::string contenido = line.substr(multi_pos) + "\n";
    int start_line = lineNumber;

    if (line.find("*/", multi_pos) != std::string::npos) {
      int end_line = lineNumber;
      std::string tipo = (comentarios_.empty()) ? "description" : "multi";
      comentarios_.push_back(Comment(tipo, start_line, end_line, contenido));
      return;
    }

    while (std::getline(file, line)) {
      ++lineNumber;
      contenido += line + "\n";
      if (line.find("*/") != std::string::npos) {
        int end_line = lineNumber;
        std::string tipo = (comentarios_.empty()) ? "description" : "multi";
        comentarios_.push_back(Comment(tipo, start_line, end_line, contenido));
        return;
      }
    }
  }
}

void Analyser::DetectVariable(const std::string& line, const int& lineNumber) {
  // 1. Filtro rápido
  if (line.find("int") == std::string::npos && line.find("double") == std::string::npos)
    return;

  // 2. Evitar declaraciones dentro de bucles
  if (line.find("for(") != std::string::npos || line.find("for (") != std::string::npos ||
      line.find("while(") != std::string::npos || line.find("while (") != std::string::npos) {
    return;
  }

  // 3. Expresión regular más tolerante (acepta indentación y variables locales)
  std::regex varRegex(R"((?:^|\s)(int|double)\s+([a-zA-Z_]\w*)(?:\s*=\s*([^;]+))?;)");
  std::smatch match;

  if (std::regex_search(line, match, varRegex)) {
    std::string type = match[1].str();
    std::string name = match[2].str();
    bool initialized = match[3].matched;
    std::string value = initialized ? match[3].str() : "";
    variables_.push_back(Variable(type, name, lineNumber, initialized, value));
  }
}

void Analyser::DetectLoop(const std::string& line, const int& lineNumber) {
  // --- 1. Filtros para comentarios ---
  // Si la línea contiene // o está dentro de /* ... */, la ignoramos
  if (line.find("//") != std::string::npos || line.find("/*") != std::string::npos)
    return;

  // --- 2. Expresión regular robusta ---
  // \b -> delimita palabra (evita detectar 'before' o 'format')
  // \s*\( -> asegura que esté seguido de un paréntesis
  std::regex loopRegex(R"(\b(for|while)\s*\()");
  std::smatch match;

  // --- 3. Búsqueda ---
  if (std::regex_search(line, match, loopRegex)) {
    std::string tipo = match[1].str();
    bucles_.push_back(Loop(tipo, lineNumber));
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

void Analyser::AnalyseFile(const std::string& input_filename) {
  std::ifstream file(input_filename);
  if (!file.is_open()) {
    std::cerr << "Error: no se pudo abrir el archivo " << input_filename << std::endl;
    return;
  }

  std::string line;
  int line_number = 1;

  // --- Bucle principal de lectura ---
  while (std::getline(file, line)) {
    // 1. Detectar comentarios primero, porque pueden contener texto que coincida con otros patrones
    DetectComment(line, line_number, file);

    // 2. Detectar variables (int y double)
    DetectVariable(line, line_number);

    // 3. Detectar bucles (for y while)
    DetectLoop(line, line_number);

    // 4. Detectar la existencia de main()
    DetectMain(line, line_number);

    // Avanzamos línea
    ++line_number;
  }

  file.close();
}

void Analyser::ExportResults(const std::string& input_filename, const std::string& output_filename) const {
  std::ofstream out(output_filename);
  if (!out.is_open()) {
    std::cerr << "Error: no se pudo crear el archivo " << output_filename << std::endl;
    return;
  }

  // 1. PROGRAM
  out << "PROGRAM: " << input_filename << "\n\n";

  // 2. DESCRIPTION
  out << "DESCRIPTION:\n";
  bool has_description = false;
  for (const auto& com : comentarios_) {
    if (com.tipo() == "description") {
      out << com.contenido() << "\n";
      has_description = true;
      break;
    }
  }
  if (!has_description) out << "(No description found)\n";
  out << "\n";

  // 3. VARIABLES
  out << "VARIABLES:\n";
  if (variables_.empty()) out << "(No variables declared)\n";
  for (const auto& var : variables_) {
    out << var << "\n";
  }
  out << "\n";

  // 4. STATEMENTS
  out << "STATEMENTS:\n";
  if (bucles_.empty()) out << "(No loops found)\n";
  for (const auto& loop : bucles_) {
    out << loop << "\n";
  }
  out << "\n";

  // 5. MAIN
  out << "MAIN:\n";
  out << (func_main() ? "True" : "False") << "\n\n";

  // 6. COMMENTS
  out << "COMMENTS:\n";
  bool any_comments = false;
  for (const auto& com : comentarios_) {
    if (com.tipo() != "description") {
      out << com;
      any_comments = true;
    }
  }
  if (!any_comments) out << "(No comments)\n";

  out.close();
}