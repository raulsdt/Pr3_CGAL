#include "delaunay.h"

Delaunay::Delaunay(){

}

Delaunay::Delaunay(vector<Point2D>::iterator begin,vector<Point2D>::iterator end){
    dt.insert(begin, end);
}


void Delaunay::insertarPuntos(vector<Point2D>::iterator begin,vector<Point2D>::iterator end){
    dt.insert(begin, end);
}

vector<Point2D> Delaunay::iteracionVertices(){
    vector<Point2D> puntos;
    Delaunay2D::Vertex_iterator iterVertices;

    for(iterVertices = dt.vertices_begin();iterVertices != dt.vertices_end();iterVertices++){
        puntos.push_back(iterVertices->point());
    }
    return puntos;
}

list< pair<Point2D,Point2D> > Delaunay::iteracionEjes(){
    list< pair<Point2D,Point2D> > listaEjes;
    Delaunay2D::Edge_iterator iterEjes;
    Delaunay2D::Edge eje;

    SDG2 sdg;

    for(iterEjes = dt.edges_begin();iterEjes != dt.edges_end();iterEjes++){
        eje = *iterEjes;
        Point2D p1 = eje.first->vertex(sdg.ccw(eje.second))->point();
        Point2D p2 = eje.first->vertex(sdg.cw(eje.second))->point();

        //Preparamos el pair de puntos
        pair<Point2D,Point2D> par(p1,p2);

        //Los introducimos en la lista
        listaEjes.push_back(par);
    }
    return listaEjes;
}

void Delaunay::iteracionCaras(vector<float> *vx,vector<float> *vy){
    iterCaras itc = dt.finite_faces_begin();

    for(;itc != dt.finite_faces_end();itc++){
        //Iterar por las caras
        Point2D p1 = dt.triangle(itc)[0];
        Point2D p2 = dt.triangle(itc)[1];
        Point2D p3 = dt.triangle(itc)[2];

        vx->push_back(p1[0]);
        vx->push_back(p2[0]);
        vx->push_back(p3[0]);

        vy->push_back(p1[1]);
        vy->push_back(p2[1]);
        vy->push_back(p3[1]);
    }
}
