#include <QtGui/QApplication>
#include <QSplashScreen>
#include <unistd.h> /* anyadir esta cabecera en los *nix para la función sleep() */
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "mainwindow.h"

#include "xml.h"
#include "delaunay.h"

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    //Creamos un splash
    QSplashScreen * splash = new QSplashScreen;
    splash->setPixmap(QPixmap("../untitled/iconos/cgal_splash.jpeg"));
    splash->show();

    Qt::Alignment bottomRight = Qt::AlignRight | Qt::AlignBottom;

    MainWindow interfaz;

    splash->showMessage(QObject::tr("Cargando interfaz..."),bottomRight,Qt::red);

    sleep(4);// Retardo de 4 segundos

    interfaz.show();

    //--
    splash->finish(&interfaz);
    delete splash;

    return a.exec();
}
