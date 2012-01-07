#include "lienzo.h"
#include "ui_lienzo.h"

/**
  @brief Constructor
  */
Lienzo::Lienzo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lienzo)
{
    ui->setupUi(this);

    puntos = new vector<QPoint>();
    ejes = new list < pair<QPoint,QPoint> >();
    zonasLocalizadas = new vector<QPolygon>();
    puntosLocalizacion = new vector<QPoint>();

    ponerPuntos = false;
    hacerTriangulacion = false;
    hacerLocalizaciones = false;
}

/**
  @brief Destructor pos defecto
  */
Lienzo::~Lienzo()
{
    //Elimiunar estructuras

    delete ui;
}

/**
  @brief Evento de dibujo, realiza la graficación de los objetos en pantalla
  */
void Lienzo::paintEvent(QPaintEvent *){
    QPainter pintor(this);

    //Dibujamos ejes
    int ejeY = (this->width() - 0) / 2;
    int ejeX = (this->height() - 0) / 2;

    pintor.drawLine(ejeY,0,ejeY,height());
    pintor.drawLine(0,ejeX,width(),ejeX);


    //Dibujamos puntos
    QPen estilo(Qt::black,5,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
    pintor.setPen(estilo);

    for(int i = 0;i < puntos->size();i++){
        pintor.drawPoint(convCoordX((*puntos)[i].x()),convCoordY((*puntos)[i].y()));
    }

    //Dibujamos ejes de la Triangulación
    list < pair<QPoint,QPoint> >::iterator  begin = ejes->begin();
    list < pair<QPoint,QPoint> >::iterator  end = ejes->end();

    QPen estiloLinea(Qt::red,1,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
    pintor.setPen(estiloLinea);

    for(;begin!=end;begin++){
        pintor.drawLine(convCoordX(begin->first.x()),convCoordY(begin->first.y()),convCoordX(begin->second.x()),convCoordY(begin->second.y()));
    }

    //Dibujamos zonas de localización
    QBrush estiloZona(Qt::yellow,Qt::DiagCrossPattern);
    pintor.setBrush(estiloZona);

    for(int i = 0; i < zonasLocalizadas->size();i++){

        QPoint p1 = (*zonasLocalizadas)[i].point(1);
        QPoint p2 = (*zonasLocalizadas)[i].point(2);
        QPoint p3 = (*zonasLocalizadas)[i].point(3);

        QPolygon poli;
        poli << QPoint(convCoordX(p1.x()),convCoordY(p1.y()));
        poli << QPoint(convCoordX(p2.x()),convCoordY(p2.y()));
        poli << QPoint(convCoordX(p3.x()),convCoordY(p3.y()));

        pintor.drawPolygon(poli);
    }

    //Dibujamos los puntos de localización
    QPen estiloPuntoLocalizado(Qt::darkBlue,5,Qt::SolidLine,Qt::RoundCap,Qt::MiterJoin);
    pintor.setPen(estiloPuntoLocalizado);

    for(int i = 0;i < puntosLocalizacion->size();i++){
        pintor.drawPoint(convCoordX((*puntosLocalizacion)[i].x()),convCoordY((*puntosLocalizacion)[i].y()));
    }

}

/**
  @brief Eventos de pulsación sobre el lienzo definido para pintar
  */
void Lienzo::mousePressEvent(QMouseEvent *event){
    if(ponerPuntos && !hacerLocalizaciones){
        //Guardamos punto de la triangulación
        int coordX = InversaConvCoordX(event->pos().x());
        int coordY = InversaConvCoordY(event->pos().y());

        QPoint p(coordX,coordY);
        puntos->push_back(p);

        if(puntos->size() >= 3){
            hacerTriangulacion = true;
        }
    }

    if(hacerLocalizaciones){
        //Guardamos puntos de localización
        int coordX = InversaConvCoordX(event->pos().x());
        int coordY = InversaConvCoordY(event->pos().y());

        QPoint p(coordX,coordY);
        puntosLocalizacion->push_back(p);
    }

    update();
}


/*Convertidores de coordenadas*/

/**
  @brief Convierte coordenadas de mundo a coordenadas de pantalla (Coodenada X)
  */
int Lienzo::convCoordX(int x){
    return ( (x * width() ) / (2 * 100) + (width() / 2) );
}

/**
  @brief Convierte coordenadas de mundo a coordenadas de pantalla (Coodenada Y)
  */
int Lienzo::convCoordY(int y){
    return ((height() - ( (y * height() ) / ( 2 * 100) + (height() / 2))));
}

/**
  @brief Convierte coordenadas de pantalla a coordenadas de mundo (Coodenada X)
  */
int Lienzo::InversaConvCoordX(int x){
    return ((x *200 - 100*width()) /width());
}

/**
  @brief Convierte coordenadas de pantalla a coordenadas de mundo(Coodenada Y)
  */
int Lienzo::InversaConvCoordY(int y){
    return ( ( (-1 * y + height()) * 400 - 200 * height()) / (2 * height()) );
}


//Habilitación de la bandera de puntos

/**
  @brief Devuelve el valor de la bandera de inserción de puntos de la triangulación
  */
bool Lienzo::getBanderaPuntos(){
    return ponerPuntos;
}

/**
  @brief Pone a TRUE el valor de la bandera de inserción de puntos de la triangulación
  */
void Lienzo::setBanderaPuntosTrue(){
    ponerPuntos = true;
}

/**
  @brief Pone a FALSE el valor de la bandera de inserción de puntos de la triangulación
  */
void Lienzo::setBanderaPuntosFalse(){
    ponerPuntos = false;
}

/**
  @brief Devuelve el valor de la bandera de realizar triangulación
  */
bool Lienzo::getBanderaTriangulacion(){
    return hacerTriangulacion;
}

/**
  @brief Pone a TRUE el valor de la bandera de realizar triangulación
  */
void Lienzo::setBanderaTriangulacionTrue(){
    hacerTriangulacion = true;
}

/**
  @brief Pone a FALSE el valor de la bandera de realizar triangulación
  */
void Lienzo::setBanderaTriangulacionFalse(){
    hacerTriangulacion = false;
}

/**
  @brief Pone a TRUE el valor de la bandera de localización
  */
void Lienzo::setBanderaLocalizacionTrue(){
    hacerLocalizaciones = true;
}

/**
  @brief Pone a False el valor de la bandera de localización
  */
void Lienzo::setBanderaLocalizacionFalse(){
    hacerLocalizaciones = false;
}
