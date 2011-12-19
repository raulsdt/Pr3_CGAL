#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    l = new Lienzo();
    setCentralWidget(l);
}

MainWindow::~MainWindow()
{
    delete ui;
}
