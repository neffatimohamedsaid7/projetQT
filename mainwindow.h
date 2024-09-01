#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "candidats.h"
#include "offres_emplois.h"
#include "NotificationLayout.h"
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

    void on_pushButton_Recherche_clicked();

    void on_pushButton_Recherche_2_clicked();

    void on_pushButton_refrech_clicked();

    void on_pushButton_refrech_2_clicked();

    void on_pushButton_Tri_clicked();

    void on_pushButton_Tri_2_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_PDF_2_clicked();

    void on_qrcodegen_clicked();

    void on_pushButton_success_clicked();
    void on_pushButtonModifier_success_clicked();
    void on_pushButtonSupprimer_success_clicked();

private:
    Ui::MainWindow *ui;
    CANDIDATS C;
    OFFRES_EMPLOIS O;
    NotificationLayout notificationLayout;
};

#endif // MAINWINDOW_H
