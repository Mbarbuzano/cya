// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/12/2025
// Archivo: subtree.cc
// Contenido: implementación de la clase subtree, que contiene el
//            constructor de la clase y otras funciones

#include "subtree.h"

void ModoDeEmpleo() {
  std::cout << "Modo de empleo: './emst <archivo_entrada> <archivo_salida>'\n"
            << "pruebe '--help' para más información\n";
}

void Ayuda() {
  std::cout << "Este programa usa el algoritmo de Kruskal para crear un árbol"
            << "generador de mínimo coste a partir de unas coordenadas que se"
            << "le pasan a través de un archivo de entrada\n";
}

namespace EMST {
  sub_tree::sub_tree(void) : arcs_(), points_(), cost_(0) {}

	sub_tree::~sub_tree(void) {}

  void sub_tree::add_arc(const CyA::arc &a) {
    arcs_.push_back(a);

    points_.insert(a.first);
    points_.insert(a.second);
  }

  void sub_tree::add_point(const CyA::point &p) {
    points_.insert(p);
  }

  bool sub_tree::contains(const CyA::point &p) const {
    return points_.find(p) != points_.end();
  }

  void sub_tree::merge(const sub_tree &st, const CyA::weigthed_arc &a) {
    arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
    arcs_.push_back(a.second);

    points_.insert(st.points_.begin(), st.points_.end());

    cost_ += a.first + st.get_cost();
  }
}