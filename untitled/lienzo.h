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

private:
    vector<QPoint> puntos;
    Ui::Lienzo *ui;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    int convCoordX(int x);
    int convCoordY(int y);
    int InversaConvCoordX(int x);
    int InversaConvCoordY(int y);
};

#endif // LIENZO_H
