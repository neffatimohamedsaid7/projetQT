#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "candidats.h"
#include "offres_emplois.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Ajouter_clicked();

    void on_pushButton_Supprimer_clicked();
    void on_pushButton_Ajouter2_clicked();
    void on_pushButton_Supprimer2_clicked();
private:
    Ui::MainWindow *ui;
    CANDIDATS C;
    OFFRES_EMPLOIS O;
};

#endif // MAINWINDOW_H
