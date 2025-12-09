// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 11: Algoritmos Voraces
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/12/2025
// Archivo: subtree.h
// Contenido: implementación de la clase sub_tree que toma el contenido del archivo

#ifndef SUBTREE_H
#define SUBTREE_H

#include "point_types.h"

void ModoDeEmpleo();
void Ayuda();

namespace EMST
{
    class sub_tree
    {
    private:
        CyA::tree arcs_;
        CyA::point_collection points_;
        double cost_;

    public:
        sub_tree(void);
        ~sub_tree(void);

        void add_arc(const CyA::arc &a);
        void add_point(const CyA::point &p);
        bool contains(const CyA::point &p) const;
        void merge(const sub_tree &st, const CyA::weigthed_arc &a);

        inline const CyA::tree& get_arcs(void) const { return arcs_; }
        inline double get_cost(void) const { return cost_; }
    };

    typedef std::vector<sub_tree> sub_tree_vector;
}

#endif