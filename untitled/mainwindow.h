#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lienzo.h"
#include "delaunay.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSalir_triggered();

    void on_actionInsertar_puntos_toggled(bool arg1);

    void on_actionBorra_pantalla_triggered();

    void on_actionTriangular_puntos_triggered();

private:
    Ui::MainWindow *ui;
    Lienzo *l;

    //Delaunay
    Delaunay *dt;

};

#endif // MAINWINDOW_H
