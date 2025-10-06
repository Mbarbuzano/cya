// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 4: Expresiones Regulares
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 09/10/2025
// Archivo: analyser.h
// Contenido: declaración de la clase analizador de código

#ifndef ANALYSER_H_
#define ANALYSER_H_

#include "comment.h"

class Analyser {
 public:
  Analyser() { }
  Analyser(const std::vector<Variable>& variables, const std::vector<Loop>& loops, const std::vector<Comment>& comments, 
           const bool& main_func) : variables_{variables}, bucles_{loops}, comentarios_{comments}, func_main_{main_func} { }

  std::vector<Variable> variables() const { return variables_; }
  std::vector<Loop> bucles() const { return bucles_; }
  std::vector<Comment> comentarios() const { return comentarios_; }
  bool func_main() const { return func_main_; }
  void set_func_main(bool found) { func_main_ = found; }

  void DetectVariable(const std::string& line, const int& line_number);
  void DetectLoop(const std::string& line, const int& line_number);
  void DetectMain(const std::string& line, const int& line_number);
  void DetectComment(std::string& line, int& line_number, std::ifstream& file);

  void AnalyseFile(const std::string& inputf_filename);
  void ExportResults(const std::string& input_filename, const std::string& output_filename) const;

 private:
  std::vector<Variable> variables_;
  std::vector<Loop> bucles_;
  std::vector<Comment> comentarios_;
  bool func_main_;
};

#endif