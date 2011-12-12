#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <iostream>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

//Librerías de CGAL

#include </usr/include/CGAL/Exact_predicates_inexact_constructions_kernel.h> // Kernel inexacto -- calculos más rápido
#include </usr/include/CGAL/Triangulation_euclidean_traits_2.h>              // Trait 2D
#include </usr/include/CGAL/Delaunay_triangulation_2.h>                      // Triangulación 2D
#include </usr/include/CGAL/Point_2.h>
#include </usr/include/CGAL/IO/Color.h>
#include </usr/include/CGAL/Triangulation_data_structure_2.h>

#include </usr/include/CGAL/Segment_Delaunay_graph_2.h>
#include </usr/include/CGAL/Segment_Delaunay_graph_traits_2.h>

//2D
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_euclidean_traits_2<K> Tr;
typedef CGAL::Delaunay_triangulation_2<Tr> Delaunay2D;
typedef K::Point_2 Point2D; //Punto 2D



//Definiciones de las estructuras para iterar
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef Tds::Vertex_iterator iterVertices;
    //Utilizado para los ejes
typedef CGAL::Segment_Delaunay_graph_traits_2<K> Gt;
typedef CGAL::Segment_Delaunay_graph_2<Gt> SDG2;
    //Utilizado para las caras
typedef Delaunay2D::Finite_faces_iterator iterCaras;



/**
  CLASE DELAUNAY
  */
class Delaunay{
private:
    Delaunay2D dt;
public:
    Delaunay(vector<Point2D>::iterator begin,vector<Point2D>::iterator end);

    //Operaciones
    vector<Point2D> iteracionVertices();
    list< pair<Point2D,Point2D> > iteracionEjes();
    void iteracionCaras(vector<float> *vx,vector<float> *vy);
};

#endif // DELAUNAY_H
