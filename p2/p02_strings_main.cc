// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica -:
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/09/2025
// Archivo: p02_strings_main.cc
// Contenido: la función main del proyecto 

#include "alphabet.h"

void ModoDeEmpleo() {
  std::cout << "Modo de empleo: ./p02_strings filein.txt fileout.txt opcode" << std::endl;
  std::cout << "Pruebe: './p02_strings --help' para más información." << std::endl;
}

void Info() {
  std::cout << "Este programa está diseñado para leer diferentes cadenas que recibe de ficheros de entrada.\n"
            << "Especifique los ficheros de entrada y salida para que funcione correctamente.\n";
}

int main(int argc, char* argv[]) {
  if (argc > 1 && std::string(argv[1]) == "--help") {
    Info();
    return 0;
  }
  if (argc == 1) {
    ModoDeEmpleo();
    return 1;
  }

  std::string filein{argv[1]};
  std::string fileout{argv[2]};
  int opcode = std::stoi(argv[3]);
  std::ifstream infile(filein);
  std::ofstream outfile(fileout);

  if (!infile.is_open()) {
    std::cerr << "El fichero no está abierto; no se tiene acceso.\n";
    return 1;
  }

   if (!outfile.is_open()) {
    std::cerr << "ERROR: no se pudo abrir el fichero de salida.\n";
    return 1;
  }

  std::string cadena, alfabeto;
  std::vector<Symbol> vector_cadena;
  std::set<Symbol> simbolos;
  while (infile >> cadena >> alfabeto) {
    vector_cadena.clear();
    simbolos.clear();
    for (char c : cadena) {
      vector_cadena.push_back(c);
    }
    for (char c : alfabeto) {
      simbolos.insert(c);
    }
    Chain chain{vector_cadena}; 
    Alphabet alphabet{simbolos};

    if (opcode > 5 || opcode < 1) {
      std::cout << "Número inválido. Ingrese un número entre 1 y 5.\n";
      return 1;
    }

    switch (opcode) {
      case 1:
        outfile << alphabet << "\n";
      break;

      case 2:
        outfile << chain.longitud() << "\n";
      break;

      case 3:
        outfile << chain.inversa() << "\n";
      break;

      

    }

    cadena.clear();
    alfabeto.clear();
  }
  infile.close();
  outfile.close();

  return 0;
}