// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/12/2025
// Archivo: point_types.cc
// Contenido: declaración de los tipos de datos a usar en posteriores archivos

#ifndef POINT_TYPES_H
#define POINT_TYPES_H

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <vector>
#include <cmath>
#include <set>

#define MAX_SZ 3
#define MAX_PREC 0

namespace CyA {
typedef std::pair<double, double> point;

  typedef std::pair<point, point> line;
  typedef std::vector<point> point_vector;

  typedef std::pair<point, point> arc;
  typedef std::pair<double, arc> weigthed_arc;
  typedef std::vector<weigthed_arc> arc_vector;

  typedef std::set<point> point_collection;

  typedef std::vector<arc> tree;
}

std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);

std::istream& operator>>(std::istream& is, CyA::point_vector& ps);
std::istream& operator>>(std::istream& is, CyA::point& ps);

#endif