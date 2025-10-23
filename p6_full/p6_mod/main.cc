// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 6: Autómatas finitos
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 23/10/2025
// Archivo: main.cc
// Contenido: archivo principal del programa para simular autómatas finitos

#include "automaton.h"

void ModoDeEmpleo() {
  std::cout << "Modo de empleo: ./p06_automata_simulator input.fa input.txt"
            << "Pruebe p06_automata_simulator --help para mas informacion.\n";
}

void Ayuda() {
  std::cout << "Este programa simula el comportamiento de un autómata y una serie"
            << "de cadenas que se le pasan con los dos archivos especificados.\n";
}

int main(int argc, char* argv[]) {
  if (argc == 2 && std::string(argv[1]) == "--help") {
    Ayuda();
    return 1;
  }

  if (argc < 3 || argc > 4) {
    ModoDeEmpleo();
    return 1;
  }

  bool modo_traza = (argc >= 4 && std::string(argv[3]) == "trace");
  std::string entrada{argv[1]};
  Automaton automata{entrada};
  std::ifstream input(argv[2]);

  if (!input.is_open()) {
    std::cerr << "Error al abrir el archivo de cadenas: " << argv[2] << "\n";
    return 1;
  }

  std::string cadena;

  while (input >> cadena) {
    if (modo_traza)
      automata.TrazarCadena(cadena);
    else {
     bool aceptada = automata.ProcesarCadena(cadena);
      std::cout << cadena << " --- " << (aceptada ? "Accepted" : "Rejected") << "\n";
    }
  }


  return 0;
}