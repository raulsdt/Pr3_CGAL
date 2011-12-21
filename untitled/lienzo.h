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
    vector<QPoint> puntos; //Array de puntos
    list < pair<QPoint,QPoint> > ejes;

    bool getBanderaPuntos();
    void setBanderaPuntosTrue();
    void setBanderaPuntosFalse();

    bool getBanderaTriangulacion();
    void setBanderaTriangulacionFalse();

private:
    Ui::Lienzo *ui;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    int convCoordX(int x);
    int convCoordY(int y);
    int InversaConvCoordX(int x);
    int InversaConvCoordY(int y);

    //Habilitación de escritura de puntos
    bool ponerPuntos;
    bool hacerTriangulacion;
};

#endif // LIENZO_H
