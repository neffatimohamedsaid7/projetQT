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
    void on_tableViewCANDIDATS_clicked(const QModelIndex &index);
    void on_tableView_OffresEmplois_clicked(const QModelIndex &index);
    void on_pushButton_Modifier_clicked();

    void on_pushButton_Modifier2_clicked();

    void on_tableView_CANDIDATS_clicked(const QModelIndex &index);

    void on_Statistique_clicked();

    void on_Statistique2_clicked();

private:
    Ui::MainWindow *ui;
    CANDIDATS C;
    OFFRES_EMPLOIS O;
};

#endif // MAINWINDOW_H
