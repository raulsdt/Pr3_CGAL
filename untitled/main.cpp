#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include "xml.h"
#include <vector>
#include <list>

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
//typedef CGAL::Triangulation_2<K,Tds> Triangulation;
typedef Delaunay2D::Finite_faces_iterator iterCaras;


//CONSTANTES
#define NUM_PUNTOS 10

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    //Vectore X e Y para almacenar los puntos del fichero XML
    vector<float> vx;
    vector<float> vy;

    //Leemos el fichero nube.xml
    Xml archivoXML("../../data/nube.xml");
    archivoXML.leerXml(&vx,&vy);

    //----------------------------------------------------------------

    //Conversión de vx y vy a Point2D
    vector<Point2D> vPoint2D;

    for(int i = 0; i < vx.size();i++){
        Point2D p = Point2D(vx[i],vy[i]);
        vPoint2D.push_back(p);
        //cout << p;
    }

    //Definimos los iteradores para el vector
    vector<Point2D>::iterator begin = vPoint2D.begin();
    vector<Point2D>::iterator end = vPoint2D.end();

    //----------------------------------------------------------------

    //REALIZAMOS DELAUNAY
    Delaunay2D dt;
    dt.insert(begin, end);

    //OPERACIONES CON LA TRIANGULACIÓN

    //1.- Definir un Vertex_iterator de vértices y listarlos por pantalla
    Delaunay2D::Vertex_iterator iterVertices;

    cout << "*-----------LISTADO DE VÉRTICES -----------*" << endl;

    for(iterVertices = dt.vertices_begin();iterVertices != dt.vertices_end();iterVertices++){
        cout << iterVertices->point() << endl;
    }

    //2.- Iterar sobre los ejes de la triangulación. Insertarlos en una lista STL
    list< pair<Point2D,Point2D> > listaEjes;
    Delaunay2D::Edge_iterator iterEjes;
    Delaunay2D::Edge eje;

    SDG2 sdg;

    cout << "*-----------LISTADO DE EJES -----------*" << endl;

    for(iterEjes = dt.edges_begin();iterEjes != dt.edges_end();iterEjes++){
        eje = *iterEjes;
        Point2D p1 = eje.first->vertex(sdg.ccw(eje.second))->point();
        Point2D p2 = eje.first->vertex(sdg.cw(eje.second))->point();

        //Preparamos el pair de puntos
        pair<Point2D,Point2D> par(p1,p2);

        //Los introducimos en la lista
        listaEjes.push_back(par);

        cout << p1 << " | " << p2 << endl;
    }

    //3.-Iterar por las caras de las triangulación. Introducirlos en un fichero
    iterCaras itc = dt.finite_faces_begin();
    for(;itc != dt.finite_faces_end();itc++){
        //Iterar por las caras
    }

    //*******************************

    cout << "El número de vértices es: " << dt.number_of_vertices() << endl;


    //FIN

    return 0;
}
