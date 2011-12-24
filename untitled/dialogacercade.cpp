#include "dialogacercade.h"
#include "ui_dialogacercade.h"

DialogAcercaDe::DialogAcercaDe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAcercaDe)
{
    ui->setupUi(this);
}

DialogAcercaDe::~DialogAcercaDe()
{
    delete ui;
}

void DialogAcercaDe::on_pushButton_clicked()
{
    this->close();
}
