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
  std::regex singleLine(R"(^\s*//(.*))");
  std::regex multiStart(R"(^\s*/\*.*)");
  std::regex multiEnd(R"(.*\*/\s*$)");
  std::smatch match;

  if (std::regex_search(line, match, singleLine)) {
    std::string contenido = "//" + match[1].str();
    int start_line = lineNumber, end_line = lineNumber;

    std::string tipo = (comentarios_.empty() && lineNumber <= 3) ? "description" : "single";
    comentarios_.push_back(Comment(tipo, start_line, end_line, contenido));
    return;
  }

  if (std::regex_search(line, match, multiStart)) {
    std::string contenido = line + "\n";
    int start_line = lineNumber;
    if (std::regex_search(line, multiEnd)) {
      comentarios_.push_back(Comment("multi", start_line, lineNumber, contenido));
      return;
    }
    while (std::getline(file, line)) {
      ++lineNumber;
      contenido += line + "\n";
      if (std::regex_search(line, multiEnd)) break;
    }
    std::string tipo = (comentarios_.empty()) ? "description" : "multi";
    comentarios_.push_back(Comment(tipo, start_line, lineNumber, contenido));
  }
}


void Analyser::DetectVariable(const std::string& line, const int& lineNumber) {
  std::regex varRegex(R"(^\s*(?!for|while)(int|double)\s+([a-zA-Z_]\w*)(?:\s*=\s*([^;]+))?;)");
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
  std::regex loopRegex(R"(^\s*(?!//)\b(for|while)\s*\()");
  std::smatch match;

  if (std::regex_search(line, match, loopRegex)) {
    bucles_.push_back(Loop(match[1].str(), lineNumber));
  }
}



void Analyser::DetectMain(const std::string& line) {
  // Busca "int main(" o "void main("
  std::regex mainRegex(R"(\b(int|void)\s+main\s*\()");
  if (std::regex_search(line, mainRegex)) {
    set_func_main(true);
  }
}

// MODIFICACIÓN

void Analyser::DetectInclusion(std::string& line) {
  std::regex include_pattern(R"(^\s*#include\s*([<"])([^">]+)([>"]))");

  std::smatch match;
  if (std::regex_search(line, match, include_pattern)) {
    std::string name = match[2];
    char delimiter = match[1].str()[0];
    bool is_system = (delimiter == '<');
    includes_.emplace_back(name, is_system);
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

  while (std::getline(file, line)) {
    // 1. Detectar comentarios
    DetectComment(line, line_number, file);

    // 2. Detectar variables (int y double)
    DetectVariable(line, line_number);

    // 3. Detectar bucles (for y while)
    DetectLoop(line, line_number);

    // 4. Detectar la existencia de main()
    DetectMain(line);

    // 5. Detección de includes
    DetectInclusion(line);

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
    if (com.tipo() != "description\n") {
      out << com << "\n\n";
      any_comments = true;
    }
  }
  if (!any_comments) out << "(No comments)\n";

  // MODIFICACIÓN

  out << "INCLUDES:\n";
  int std_count = 0;
  int user_count = 0;

  for (const auto& inc : includes_) {
    if (inc.system()) ++std_count;
    else ++user_count;
  }

  out << "STD: " << std_count << "\n";
  out << "USER: " << user_count << "\n";

  out.close();
}