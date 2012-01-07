#include "xml.h"

/**
   @brief Constructor
   @param r Ruta del archivo
 */
Xml::Xml(QString r){
    ruta = r;
}

/**
   @brief Metodo para leer un archivo xml (nube de puntos)
 */
bool Xml::leerXml(vector<float> *vx,vector<float> *vy){
    vector<float> x;
    vector<float> y;

    QDomDocument documento;

    //Leemos el archivo XML
    QFile archivo(ruta);

    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        cout << "Fallo al abrir archivo: LECTURA" << endl;
        return false;
    }else{
        if(!documento.setContent(&archivo)){ //Leemos contenido del archivo
            cout << "No contiene datos..." << endl;
            return false;
        }
        archivo.close();
    }

    //Leemos la raiz del documento
    QDomElement raiz = documento.firstChildElement();

    QDomNodeList listaPuntos = raiz.elementsByTagName("PUNTO");

    for(int i = 0;i < listaPuntos.count();i++){
       QDomNode nodoPunto = listaPuntos.at(i);

       if(nodoPunto.isElement()){
            QDomElement elementoPunto = nodoPunto.toElement(); //Tenemos elemento
            //cout << "Es elemento" << endl;

            QDomNode nodoX = elementoPunto.elementsByTagName("X").item(0);
            QDomNode nodoY = elementoPunto.elementsByTagName("Y").item(0);

            QDomElement elemX = nodoX.toElement();
            QDomElement elemY = nodoY.toElement();

            QString puntoX = elemX.text();
            QString puntoY = elemY.text();

            //cout << puntoX.toFloat() << " | " << puntoY.toFloat()<< endl;
            x.push_back(puntoX.toFloat());
            y.push_back(puntoY.toFloat());
       }
    }
    *vx = x;
    *vy = y;

    return true;
}

/**
   @brief Metodo para escribir un archibo xml (nube de puntos)
 */
void Xml::escribeXml(vector<float> vx, vector<float> vy){
    QDomDocument documento;

    //Creamos la raiz
    QDomElement raiz = documento.createElement("NUBE");
    documento.appendChild(raiz);

    //Creamos los elementos

    for(unsigned int i = 0;i < vx.size();i++){
        //Creamos un nodo punto
        QDomElement nodoPunto = documento.createElement("PUNTO");

        //Creamos un nodo X y un nodo Y
        QDomElement nodoX = documento.createElement("X");
        QDomText numX = documento.createTextNode(QString::number(vx[i]));
        nodoX.appendChild(numX);

        QDomElement nodoY = documento.createElement("Y");
        QDomText numY = documento.createTextNode(QString::number(vy[i]));
        nodoY.appendChild(numY);

        //Ponemos los hijos X e Y al nodo PUNTO
        nodoPunto.appendChild(nodoX);
        nodoPunto.appendChild(nodoY);

        //Añadimos el hijo PUNTO a la RAIZ (NUBE)
        raiz.appendChild(nodoPunto);
    }

    //Escribimos el documento
    QFile archivo(ruta);

    if(!archivo.open(QIODevice::WriteOnly | QIODevice::Text)){
        cout << "Fallo al abrir archivo: ESCRITURA" << endl;
    }else{
        QTextStream stream(&archivo);
        stream << documento.toString();
        archivo.close();
    }

}

void Xml::setRuta(QString r){
    ruta = r;
}

QString Xml::getRuta(){
    return ruta;
}
