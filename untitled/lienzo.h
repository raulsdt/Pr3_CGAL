#ifndef LIENZO_H
#define LIENZO_H

#include <QWidget>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <vector>

using namespace std;

namespace Ui {
    class Lienzo;
}

class Lienzo : public QWidget
{
    Q_OBJECT

public:
    explicit Lienzo(QWidget *parent = 0);
    ~Lienzo();
    vector<QPoint> *puntos; /**Array que contiene los puntos de la triangulación*/
    list < pair<QPoint,QPoint> > *ejes; /**Ejes de la triangulación*/
    vector<QPolygon> *zonasLocalizadas; /**Array de triangulo con las localizaciones*/
    vector<QPoint> *puntosLocalizacion; /**Array que contiene los puntos de localización*/

    bool getBanderaPuntos();
    void setBanderaPuntosTrue();
    void setBanderaPuntosFalse();

    bool getBanderaTriangulacion();
    void setBanderaTriangulacionTrue();
    void setBanderaTriangulacionFalse();

    void setBanderaLocalizacionTrue();
    void setBanderaLocalizacionFalse();

    int convCoordX(int x);
    int convCoordY(int y);
    int InversaConvCoordX(int x);
    int InversaConvCoordY(int y);

private:
    Ui::Lienzo *ui;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);


    //Habilitación de escritura de puntos
    bool ponerPuntos;
    bool hacerTriangulacion;
    bool hacerLocalizaciones;
};

#endif // LIENZO_H
