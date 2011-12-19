#include "lienzo.h"
#include "ui_lienzo.h"

Lienzo::Lienzo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lienzo)
{
    ui->setupUi(this);
    puntos = vector<QPoint>(100);
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

}


void Lienzo::mousePressEvent(QMouseEvent *event){
    cout << event->pos().x() << " | ";
    cout << event->pos().y() << endl;

    //Guardamos punto
    int coordX = InversaConvCoordX(event->pos().x());
    int coordY = InversaConvCoordY(event->pos().y());

    QPoint p(coordX,coordY);
    puntos.push_back(p);
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
