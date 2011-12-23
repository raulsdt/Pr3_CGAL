#include "lienzo.h"
#include "ui_lienzo.h"

Lienzo::Lienzo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lienzo)
{
    ui->setupUi(this);

    ponerPuntos = false;
    hacerTriangulacion = false;
    hacerLocalizaciones = false;
}

Lienzo::~Lienzo()
{
    delete ui;
}

void Lienzo::paintEvent(QPaintEvent *){
    QPainter pintor(this);

    //Dibujamos ejes
    int ejeY = (this->width() - 0) / 2;
    int ejeX = (this->height() - 0) / 2;

    pintor.drawLine(ejeY,0,ejeY,height());
    pintor.drawLine(0,ejeX,width(),ejeX);


    //Dibujamos puntos
    for(int i = 0;i < puntos.size();i++){
        QPen estilo(Qt::black,5,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
        pintor.setPen(estilo);
        pintor.drawPoint(convCoordX(puntos[i].x()),convCoordY(puntos[i].y()));
    }

    //Dibujamos ejes
    list < pair<QPoint,QPoint> >::iterator  begin = ejes.begin();
    list < pair<QPoint,QPoint> >::iterator  end = ejes.end();

    for(;begin!=end;begin++){
        //Estilo
        QPen estiloLinea(Qt::red,1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
        pintor.setPen(estiloLinea);
        pintor.drawLine(convCoordX(begin->first.x()),convCoordY(begin->first.y()),convCoordX(begin->second.x()),convCoordY(begin->second.y()));
    }

    //Dibujamos zonas de localización
    for(int i = 0; i < zonasLocalizadas.size();i++){
        QBrush estiloZona(Qt::yellow,Qt::DiagCrossPattern);
        pintor.setBrush(estiloZona);
        QPoint p1 = zonasLocalizadas[i].point(1);
        QPoint p2 = zonasLocalizadas[i].point(2);
        QPoint p3 = zonasLocalizadas[i].point(3);

        cout << p1.x() << "|" << p1.y();
        cout << p2.x() << "|" << p2.y();
        cout << p3.x() << "|" << p3.y();

        QPolygon poli;
        poli << QPoint(convCoordX(p1.x()),convCoordY(p1.y()));
        poli << QPoint(convCoordX(p2.x()),convCoordY(p2.y()));
        poli << QPoint(convCoordX(p3.x()),convCoordY(p3.y()));

        pintor.drawPolygon(poli);
    }

    //Dibujamos los puntos de localización
    for(int i = 0;i < puntosLocalizacion.size();i++){
        QPen estiloPuntoLocalizado(Qt::darkBlue,5,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
        pintor.setPen(estiloPuntoLocalizado);
        pintor.drawPoint(convCoordX(puntosLocalizacion[i].x()),convCoordY(puntosLocalizacion[i].y()));
    }

}


void Lienzo::mousePressEvent(QMouseEvent *event){
    if(ponerPuntos && !hacerLocalizaciones){
        //Guardamos punto
        int coordX = InversaConvCoordX(event->pos().x());
        int coordY = InversaConvCoordY(event->pos().y());

        QPoint p(coordX,coordY);
        puntos.push_back(p);

        if(puntos.size() >= 3){
            hacerTriangulacion = true;
        }
    }

    if(hacerLocalizaciones){
        //Guardamos punto
        int coordX = InversaConvCoordX(event->pos().x());
        int coordY = InversaConvCoordY(event->pos().y());

        QPoint p(coordX,coordY);
        puntosLocalizacion.push_back(p);
    }

    update();
}


/*Convertidores de coordenadas*/

int Lienzo::convCoordX(int x){
    return ( (x * width() ) / (2 * 100) + (width() / 2) );
}

int Lienzo::convCoordY(int y){
    return ((height() - ( (y * height() ) / ( 2 * 100) + (height() / 2))));
}

int Lienzo::InversaConvCoordX(int x){
    return ((x *200 - 100*width()) /width());
}

int Lienzo::InversaConvCoordY(int y){
    return ( ( (-1 * y + height()) * 400 - 200 * height()) / (2 * height()) );
}


//Habilitación de la bandera de puntos

bool Lienzo::getBanderaPuntos(){
    return ponerPuntos;
}

void Lienzo::setBanderaPuntosTrue(){
    ponerPuntos = true;
}

void Lienzo::setBanderaPuntosFalse(){
    ponerPuntos = false;
}

bool Lienzo::getBanderaTriangulacion(){
    return hacerTriangulacion;
}

void Lienzo::setBanderaTriangulacionFalse(){
    hacerTriangulacion = false;
}

void Lienzo::setBanderaLocalizacionTrue(){
    hacerLocalizaciones = true;
}

void Lienzo::setBanderaLocalizacionFalse(){
    hacerLocalizaciones = false;
}
