// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/12/2025
// Archivo: point_cloud.h
// Contenido: implementación de la clase nube de puntos que toma el contenido del archivo

#ifndef POINT_CLOUD_H
#define POINT_CLOUD_H

#include <iostream>
#include <vector>
#include <set>

void ModoDeEmpleo();

typedef std::pair<double, double> point_t;
typedef std::pair<point_t, point_t> arc_t;
typedef std::pair<double, arc_t> weighted_arc_t;
typedef std::vector<weighted_arc_t> weighted_arc_vector_t;
typedef std::set<point_t> point_set_t;
typedef std::vector<arc_t> tree_t;

class Point_Cloud {
 public:
  Point_Cloud() {}
  Point_Cloud(const std::string& input);

 private:
  point_set_t points_;
  weighted_arc_vector_t arcs;
  tree_t mst;
};

#endif