#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lienzo.h"
#include "delaunay.h"
#include "dialogacercade.h"
#include "xml.h"

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

    void on_actionInsertar_puntos_localizacion_triggered();

    void on_actionInsertar_puntos_localizacion_toggled(bool arg1);

    void on_actionLocalizar_puntos_triggered();

    void on_actionInformaci_n_triggered();

    void on_actionGuardar_archivo_triggered();

    void on_actionCargar_archivo_triggered();

private:
    Ui::MainWindow *ui;
    Lienzo *l;

    //Delaunay
    Delaunay *dt;

    //Abrir archivo XML de puntos
    bool abrirXML();
    //Guardar archivo XML de puntos
    bool guardarXML();
};

#endif // MAINWINDOW_H
