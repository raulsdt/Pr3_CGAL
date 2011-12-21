#include "lienzo.h"
#include "ui_lienzo.h"

Lienzo::Lienzo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lienzo)
{
    ui->setupUi(this);

    ponerPuntos = false;
    hacerTriangulacion = false;
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


    for(int i = 0;i < puntos.size();i++){
        QPen estilo(Qt::black,5,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
        pintor.setPen(estilo);
        pintor.drawPoint(convCoordX(puntos[i].x()),convCoordY(puntos[i].y()));
    }

    list < pair<QPoint,QPoint> >::iterator  begin = ejes.begin();
    list < pair<QPoint,QPoint> >::iterator  end = ejes.end();

    for(;begin!=end;begin++){
        //Estilo
        QPen estiloLinea(Qt::red,1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
        pintor.setPen(estiloLinea);
        pintor.drawLine(convCoordX(begin->first.x()),convCoordY(begin->first.y()),convCoordX(begin->second.x()),convCoordY(begin->second.y()));
    }

}


void Lienzo::mousePressEvent(QMouseEvent *event){
    if(ponerPuntos){
        //Guardamos punto
        int coordX = InversaConvCoordX(event->pos().x());
        int coordY = InversaConvCoordY(event->pos().y());

        QPoint p(coordX,coordY);
        puntos.push_back(p);
        update();

        if(puntos.size() >= 3){
            hacerTriangulacion = true;
        }
    }
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
