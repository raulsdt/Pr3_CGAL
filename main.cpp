#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
using namespace std;

//Librerías de CGAL

#include </usr/include/CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include </usr/include/CGAL/Exact_predicates_exact_constructions_kernel.h>
#include </usr/include/CGAL/Triangulation_euclidean_traits_xy_3.h>
#include </usr/include/CGAL/Delaunay_triangulation_2.h>



typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_euclidean_traits_xy_3<K>  Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;

typedef K::Point_3   Point;


int main(int argc, char *argv[]){

    //QCoreApplication a(argc, argv);

    ifstream in("../../data/terrain.cin");
    istream_iterator<Point> begin(in);
    istream_iterator<Point> end;

    Delaunay dt;
    dt.insert(begin, end);
    cout << dt.number_of_vertices() << endl;
    return 0;
}
