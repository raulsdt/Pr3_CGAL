#ifndef XML_H
#define XML_H

#include <QtCore>
#include <QtXml>
#include <iostream>
#include <vector>

using namespace std;

class Xml{    
private:
    QString ruta;
public:
    Xml(QString ruta);
    bool leerXml(vector<float> *vx,vector<float> *vy);
    void escribeXml(vector<float> vx, vector<float> vy);
};

#endif // XML_H
