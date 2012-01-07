#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    l = new Lienzo();
    setCentralWidget(l);

    //Construimos Delaunay
    dt = new Delaunay();

    //Desactivamos opciones
    ui->actionGuardar_archivo->setEnabled(false);
    ui->actionInsertar_puntos_localizacion->setEnabled(false);
    ui->actionLocalizar_puntos->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
  Evento de salida
  */
void MainWindow::on_actionSalir_triggered()
{
    exit(0);
}

/**
  Evento para insertar puntos
  */
void MainWindow::on_actionInsertar_puntos_toggled(bool arg1)
{
    if(arg1){
        l->setBanderaPuntosTrue();
        statusBar()->showMessage(trUtf8("Inserción de puntos: ACTIVADA"),2000);
    }else{
        l->setBanderaPuntosFalse();
        statusBar()->showMessage(trUtf8("Inserción de puntos: DESACTIVADA"),2000);
    }
}

/**
  Evento para borrar pantalla
  */
void MainWindow::on_actionBorra_pantalla_triggered()
{
    //Opciones de menú
    ui->actionInsertar_puntos->setChecked(false);
    ui->actionInsertar_puntos_localizacion->setChecked(false);

    ui->actionCargar_archivo->setEnabled(true);
    ui->actionGuardar_archivo->setEnabled(false);
    ui->actionInsertar_puntos->setEnabled(true);
    ui->actionTriangular_puntos->setEnabled(true);
    ui->actionInsertar_puntos_localizacion->setEnabled(false);
    ui->actionLocalizar_puntos->setEnabled(false);

    l->setBanderaPuntosFalse();
    l->setBanderaTriangulacionFalse();
    l->setBanderaLocalizacionFalse();

    //Quitamos los puntos de Dalunay
    delete dt;
    dt = new Delaunay();

    l->setBanderaTriangulacionFalse();

    l->puntos->clear();
    l->ejes->clear();
    l->puntosLocalizacion->clear();
    l->zonasLocalizadas->clear();

    statusBar()->showMessage(trUtf8("Pantalla borrada"),2000);
    l->update();
}


/**
  Evento triangulación de Delaunay
  */
void MainWindow::on_actionTriangular_puntos_triggered(){

    if(l->getBanderaTriangulacion() == false){
        //Poner mensaje de error: menos de tres puntos
        statusBar()->showMessage(trUtf8("Error: Triangulación no realizada. Menos de 3 puntos"),5000);
    }else{

        //Habilitamos la localización
        ui->actionGuardar_archivo->setEnabled(true);
        ui->actionInsertar_puntos_localizacion->setEnabled(true);
        ui->actionLocalizar_puntos->setEnabled(true);

        //Borramos la triangulación anterior
        delete dt;
        dt = new Delaunay();
        l->ejes->clear();

        //Hacemos la triangulación
        vector<Point2D> vPoint2D;

        for(unsigned int i = 0; i < l->puntos->size();i++){
            Point2D p = Point2D(l->puntos->at(i).x(),l->puntos->at(i).y());
            vPoint2D.push_back(p);
        }

        vector<Point2D>::iterator begin = vPoint2D.begin();
        vector<Point2D>::iterator end = vPoint2D.end();
        dt->insertarPuntos(begin,end);

        //Realizamos la iteración de los ejes para obtener la triangulación

        list < pair<Point2D,Point2D> > listaEjes;
        listaEjes = dt->iteracionEjes();

        list < pair<Point2D,Point2D> >::iterator ejesBegin = listaEjes.begin();
        list < pair<Point2D,Point2D> >::iterator ejesEnd = listaEjes.end();

        for(;ejesBegin != ejesEnd;ejesBegin++){
            QPoint p1(ejesBegin->first.x(),ejesBegin->first.y());
            QPoint p2(ejesBegin->second.x(),ejesBegin->second.y());
            pair<QPoint,QPoint> par(p1,p2);
            l->ejes->push_back(par);
        }

        l->update();
        statusBar()->showMessage(trUtf8("Triangulación realizada"),2000);
    }
}


void MainWindow::on_actionInsertar_puntos_localizacion_triggered()
{
}


/**
  Evento para insertar puntos de localización
  */
void MainWindow::on_actionInsertar_puntos_localizacion_toggled(bool arg1)
{
    //Cuando pulsamos para localizar deshabilitamos la inserción de puntos
    ui->actionCargar_archivo->setEnabled(false);
    ui->actionInsertar_puntos->setEnabled(false);
    ui->actionTriangular_puntos->setEnabled(false);
    l->setBanderaPuntosFalse();

    if(arg1){
        l->setBanderaLocalizacionTrue();
        statusBar()->showMessage(trUtf8("Inserción de puntos de localización ACTIVADA"),2000);
    }else{
        l->setBanderaLocalizacionFalse();
        statusBar()->showMessage(trUtf8("Inserción de puntos de localización DESACTIVAD"),2000);
    }
}

/**
  Evento para localizar los puntos de localización insertados
  */
void MainWindow::on_actionLocalizar_puntos_triggered()
{
    l->zonasLocalizadas->clear();

    vector<Point2D> triangulo;

    for(unsigned int i = 0; i < l->puntosLocalizacion->size(); i++){
        Point2D punto(l->puntosLocalizacion->at(i).x(),l->puntosLocalizacion->at(i).y());

        triangulo = dt->localizacion(punto);

        if(triangulo.size() != 0){
            QPolygon poli;
            poli.setPoint(1,triangulo[0].x(),triangulo[0].y());
            poli.setPoint(2,triangulo[1].x(),triangulo[1].y());
            poli.setPoint(3,triangulo[2].x(),triangulo[2].y());

            l->zonasLocalizadas->push_back(poli);
        }
    }

    statusBar()->showMessage(trUtf8("Localización realizada"),2000);
    l->update();
}

void MainWindow::on_actionInformaci_n_triggered()
{
    DialogAcercaDe *acerca = new DialogAcercaDe(this);
    acerca->exec(); //Dialogo MODAL
}

/**
  @brief Abre un archivo XML de puntos para realizar triangulación
  */
bool MainWindow::abrirXML(){
    QString fileName = QFileDialog::getOpenFileName(this,trUtf8("Cargar triangulación"),".xml",trUtf8("XML (*.xml)"));
    if(fileName.isEmpty()){
        return false;
    }else{
        //Habilitamos triangulación
        l->setBanderaTriangulacionTrue();

        //Abrimos el archivo y pintamos los puntos
        Xml archivo(fileName);
        vector<float> vx;
        vector<float> vy;

        archivo.leerXml(&vx,&vy);

        for(unsigned int i = 0; i < vx.size();i++){
            l->puntos->push_back(QPoint((int)vx[i],(int)vy[i]));
        }

        l->update();

        //Activamos la triangulación
        l->setBanderaTriangulacionTrue();

        return true;
    }
}

/**
  @brief Guarda una archivo XML de puntos resultante de una triangulación
  */
bool MainWindow::guardarXML(){
    QString fileName = QFileDialog::getSaveFileName(this,trUtf8("Guardar puntos de la triangulación"),".xml",trUtf8("XML (*.xml)"));
    if(fileName.isEmpty()){
        return false;
    }else{
        //Guardamos archivo
        Xml archivo(fileName);
        vector<float> vx;
        vector<float> vy;

        for(unsigned int i = 0; i< l->puntos->size();i++){
            vx.push_back(l->puntos->at(i).x());
            vy.push_back(l->puntos->at(i).y());
        }

        archivo.escribeXml(vx,vy);
        return true;
    }

}

void MainWindow::on_actionGuardar_archivo_triggered()
{
    if(guardarXML()){
        statusBar()->showMessage(trUtf8("Archivo guardado correctamente"),5000);
    }else{
        statusBar()->showMessage(trUtf8("Error al guardar el archivo"),5000);
    }
}

void MainWindow::on_actionCargar_archivo_triggered()
{
    if(abrirXML()){
        statusBar()->showMessage(trUtf8("Archivo cargado correctamente"),5000);
    }else{
        statusBar()->showMessage(trUtf8("Error al cargar el archivo"),5000);
    }
}
