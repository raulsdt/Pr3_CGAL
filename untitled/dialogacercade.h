#ifndef DIALOGACERCADE_H
#define DIALOGACERCADE_H

#include <QDialog>

namespace Ui {
    class DialogAcercaDe;
}

class DialogAcercaDe : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAcercaDe(QWidget *parent = 0);
    ~DialogAcercaDe();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogAcercaDe *ui;
};

#endif // DIALOGACERCADE_H
