#include <QtCore/QCoreApplication>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "xml.h"
#include "delaunay.h"

using namespace std;

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
    }

    //-------DELAUNAY

    //Definimos los iteradores para el vector
    vector<Point2D>::iterator begin = vPoint2D.begin();
    vector<Point2D>::iterator end = vPoint2D.end();

    Delaunay d(begin,end);

    //OPERACIONES CON LA TRIANGULACIÓN

    //1.- Definir un Vertex_iterator de vértices y listarlos por pantalla
    vector<Point2D> vertices;
    vertices = d.iteracionVertices();
    cout << "LISTADO DE VERTICES " << endl;
    for(int i = 0;i < vertices.size();i++){
        cout << vertices[i] << endl;
    }

    //2.- Iterar sobre los ejes de la triangulación. Insertarlos en una lista STL
    list < pair<Point2D,Point2D> > ejes;
    ejes = d.iteracionEjes();

    //3.-Iterar por las caras de las triangulación. Introducirlos en un fichero
    vector<float> px;
    vector<float> py;
    d.iteracionCaras(&px,&py);

    //Preparamos XML para escribir
    archivoXML.setRuta("../../data/resultado.xml");
    archivoXML.escribeXml(px,py);

    return 0;
}
