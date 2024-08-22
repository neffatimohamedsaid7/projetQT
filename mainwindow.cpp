#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCameraViewfinder>
#include<QCameraImageCapture>
#include<QVBoxLayout>
#include<QMenu>
#include<QAction>
#include<QFileDialog>
#include "qmessagebox.h"
#include "connection.h"
#include <QIntValidator>
#include <QTableView>
#include <QMessageBox>
#include <QPixmap>
#include<QPrinter>
#include<QPainter>
#include<QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPdfWriter>
#include <QtCharts>
#include <QDesktopServices>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPieSlice>
#include <QPieSeries>
#include <QChartView>
#include <QPrintDialog>
#include <QFileDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QChartView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_CANDIDATS->setModel(C.afficher());//refresh
    ui->tableView_OffresEmplois->setModel(O.afficher());//refresh
}

MainWindow::~MainWindow()
{
    delete ui;
}


    void MainWindow::on_pushButton_Ajouter_clicked()
    {

        int ID_candidat=ui->lineEdit_ID_candidat->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString prenom=ui->lineEdit_prenom->text();
        QDate datenaissance = ui->lineEdit_datenaissance->date();
        QString niveau=ui->comboBox_niveaucandidat->currentText();
        QString email=ui->lineEdit_email->text();
        QString numtel=ui->lineEdit_numtel->text();
        CANDIDATS C(ID_candidat,nom, prenom, datenaissance, niveau,email,numtel);
        bool test=C.ajouter();
        if(test)
       {
            ui->tableView_CANDIDATS->setModel(C.afficher());

          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr("ajout effectué.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);

         ui->lineEdit_ID_candidat->clear();
         ui->lineEdit_nom->clear();
         ui->lineEdit_prenom->clear();
         ui->lineEdit_email->clear();
         ui->lineEdit_numtel->clear(); }


        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    }



void MainWindow::on_pushButton_Supprimer_clicked()
{
    QModelIndexList selectedRows = ui->tableView_CANDIDATS->selectionModel()->selectedRows();
        if (selectedRows.isEmpty()) {
            QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                                 tr("Veuillez sélectionner une ligne à supprimer."),
                                 QMessageBox::Ok);
            return;
        }


        int ID_candidat = selectedRows.at(0).data().toInt();
       CANDIDATS C;

       bool test=C.supprimer(ID_candidat);
       if(test)
      {

         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->tableView_CANDIDATS->setModel(C.afficher());//refresh

      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

    }

void MainWindow::on_pushButton_Ajouter2_clicked()
{

    int ID_OffreEmploi=ui->lineEdit_ID_OffreEmploi->text().toInt();
    QString titre=ui->lineEdit_titre->text();
    QString description=ui->lineEdit_description->text();
    QDate datepublication = ui->lineEdit_datepublication->date();
    int nbrplace=ui->lineEdit_ID_nbrplace->text().toInt();
    QString lieu=ui->comboBox_lieuOffreEmploi->currentText();
    int ID_candidat=ui->lineEdit_ID_candidat_2->text().toInt();
    OFFRES_EMPLOIS O(ID_OffreEmploi,titre, description, datepublication, nbrplace,lieu,ID_candidat);
    bool test=O.ajouter();
    if(test)
   {
        ui->tableView_OffresEmplois->setModel(O.afficher());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("ajout effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->lineEdit_ID_OffreEmploi->clear();
     ui->lineEdit_titre->clear();
     ui->lineEdit_datepublication->clear();
     ui->lineEdit_ID_nbrplace->clear();
     ui->lineEdit_ID_candidat_2->clear(); }


    else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("ajout non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pushButton_Supprimer2_clicked()
{
QModelIndexList selectedRows = ui->tableView_OffresEmplois->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                             tr("Veuillez sélectionner une ligne à supprimer."),
                             QMessageBox::Ok);
        return;
    }


    int ID_OffreEmploi = selectedRows.at(0).data().toInt();
   OFFRES_EMPLOIS O;

   bool test=O.supprimer(ID_OffreEmploi);
   if(test)
  {

     QMessageBox::information(nullptr, QObject::tr("ok"),
     QObject::tr("suppression effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
     ui->tableView_OffresEmplois->setModel(O.afficher());//refresh

  }
   else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("suppression non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);

}
void MainWindow::on_tableViewCANDIDATS_clicked(const QModelIndex &index)
{


       // Get data from the selected index
        int ID_candidat = index.sibling(index.row(), 0).data().toInt();
        QString nom = index.sibling(index.row(), 1).data().toString();
        QString prenom = index.sibling(index.row(), 2).data().toString();
        QDate datenaissance = index.sibling(index.row(), 3).data().toDate();
        QString niveau = index.sibling(index.row(), 4).data().toString();
        QString email = index.sibling(index.row(), 5).data().toString();
        QString numtel = index.sibling(index.row(), 6).data().toString();

        // Populate line edit fields with the retrieved data
        ui->lineEdit_ID_candidat->setText(QString::number(ID_candidat));
        ui->lineEdit_nom->setText(nom);
        ui->lineEdit_prenom->setText(prenom);
        ui->lineEdit_datenaissance->setDate(datenaissance);
        ui->comboBox_niveaucandidat->currentText();
        ui->lineEdit_email->setText(email);
        ui->lineEdit_numtel->setText(numtel);
}

void MainWindow::on_tableView_OffresEmplois_clicked(const QModelIndex &index)
{


       // Get data from the selected index
        int ID_OffreEmploi = index.sibling(index.row(), 0).data().toInt();
        QString titre = index.sibling(index.row(), 1).data().toString();
        QString description = index.sibling(index.row(), 2).data().toString();
        QDate datepublication = index.sibling(index.row(), 3).data().toDate();
        int nbrplace = index.sibling(index.row(), 4).data().toInt();
        QString lieu = index.sibling(index.row(), 5).data().toString();
        int ID_candidat_2 = index.sibling(index.row(), 6).data().toInt();

        // Populate line edit fields with the retrieved data
        ui->lineEdit_ID_OffreEmploi->setText(QString::number(ID_OffreEmploi));
        ui->lineEdit_titre->setText(titre);
        ui->lineEdit_description->setText(description);
        ui->lineEdit_datepublication->setDate(datepublication);
        ui->lineEdit_ID_nbrplace->setText(QString::number(nbrplace));
        ui->comboBox_lieuOffreEmploi->currentText();
        ui->lineEdit_ID_candidat_2->setText(QString::number(ID_candidat_2));
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    int ID_candidat=ui->lineEdit_ID_OffreEmploi->text().toInt();
    QString nom=ui->lineEdit_titre->text();
    QString prenom=ui->lineEdit_description->text();
    QDate datenaissance = ui->lineEdit_datepublication->date();
    QString niveau=ui->lineEdit_ID_nbrplace->text();
    QString email=ui->comboBox_lieuOffreEmploi->currentText();
    QString numtel=ui->lineEdit_ID_candidat_2->text();
    CANDIDATS C(ID_candidat,nom, prenom, datenaissance, niveau,email,numtel);
    bool test=C.modifier(ID_candidat);
    if(test)
   {
        ui->tableView_CANDIDATS->setModel(O.afficher());

      QMessageBox::information(nullptr, QObject::tr("ok"),
      QObject::tr("modification effectué.\n"
                   "Click Cancel to exit."), QMessageBox::Cancel);

     ui->lineEdit_ID_candidat->clear();
     ui->lineEdit_nom->clear();
     ui->lineEdit_prenom->clear();
     ui->lineEdit_datenaissance->clear();
     ui->lineEdit_email->clear();
    ui->lineEdit_numtel->clear();}


    else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("modification non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_Modifier2_clicked()
{


        int ID_OffreEmploi=ui->lineEdit_ID_OffreEmploi->text().toInt();
        QString titre=ui->lineEdit_titre->text();
        QString description=ui->lineEdit_description->text();
        QDate datepublication = ui->lineEdit_datepublication->date();
        int nbrplace=ui->lineEdit_ID_nbrplace->text().toInt();
        QString lieu=ui->comboBox_lieuOffreEmploi->currentText();
        int ID_candidat=ui->lineEdit_ID_candidat_2->text().toInt();
        OFFRES_EMPLOIS O(ID_OffreEmploi,titre, description, datepublication, nbrplace,lieu,ID_candidat);
        bool test=O.modifier(ID_OffreEmploi);
        if(test)
       {
            ui->tableView_OffresEmplois->setModel(O.afficher());

          QMessageBox::information(nullptr, QObject::tr("ok"),
          QObject::tr("modification effectué.\n"
                       "Click Cancel to exit."), QMessageBox::Cancel);

         ui->lineEdit_ID_OffreEmploi->clear();
         ui->lineEdit_titre->clear();
         ui->lineEdit_description->clear();
         ui->lineEdit_datepublication->clear();
         ui->lineEdit_ID_nbrplace->clear();
         ui->lineEdit_ID_candidat_2->clear(); }


        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("modification non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    }


void MainWindow::on_tableView_CANDIDATS_clicked(const QModelIndex &index)
{
    // Get data from the selected index
            int ID_candidat = index.sibling(index.row(), 0).data().toInt();
            QString nom = index.sibling(index.row(), 1).data().toString();
            QString prenom = index.sibling(index.row(), 2).data().toString();
            QDate datenaissance = index.sibling(index.row(), 3).data().toDate();;
            QString niveau = index.sibling(index.row(), 4).data().toString();
            QString email = index.sibling(index.row(), 5).data().toString();
            QString numtel = index.sibling(index.row(), 5).data().toString();

            // Populate line edit fields with the retrieved data
            ui->lineEdit_ID_candidat->setText(QString::number(ID_candidat));
            ui->lineEdit_nom->setText(nom);
            ui->lineEdit_prenom->setText(prenom);
           // ui->lineEdit_datenaissance->setDate(datenaissance);
            ui->comboBox_niveaucandidat->currentText();
            ui->lineEdit_email->setText(email);
            ui->lineEdit_numtel->setText(numtel);

}

void MainWindow::on_Statistique_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery("SELECT * FROM CANDIDATS WHERE niveau='debutant'");
            float dispo = model->rowCount();

            model->setQuery("SELECT * FROM CANDIDATS WHERE niveau='intermediaire'");
            float dispo1 = model->rowCount();

            model->setQuery("SELECT * FROM CANDIDATS WHERE niveau='avance'");
            float dispo2 = model->rowCount();


            float total = dispo + dispo1 + dispo2;
            QString a = QString("debutant  " + QString::number((dispo * 100) / total, 'f', 2) + "%");
            QString b = QString("intermediaire  " + QString::number((dispo1 * 100) / total, 'f', 2) + "%");
            QString c = QString("avance  " + QString::number((dispo2 * 100) / total, 'f', 2) + "%");

            QPieSeries *series = new QPieSeries();
            series->append(a, dispo);
            series->append(b, dispo1);
            series->append(c, dispo2);

            if (dispo != 0)
            {
                QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());
            }

            if (dispo1 != 0)
            {
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setLabelVisible();
            }

            if (dispo2 != 0)
            {
                QPieSlice *slice2 = series->slices().at(2);
                slice2->setLabelVisible();
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("niveau candidat : nombre de candidats" + QString::number(total));

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000, 500);
            chartView->show();


            }



void MainWindow::on_Statistique2_clicked()
{
    QSqlQueryModel * model = new QSqlQueryModel();
            model->setQuery("SELECT * FROM Offres_Emplois WHERE lieu='Tunis'");
            float dispo = model->rowCount();

            model->setQuery("SELECT * FROM Offres_Emplois WHERE lieu='Sfax'");
            float dispo1 = model->rowCount();

            model->setQuery("SELECT * FROM Offres_Emplois WHERE lieu='Sousse'");
            float dispo2 = model->rowCount();


            float total = dispo + dispo1 + dispo2;
            QString a = QString("Tunis  " + QString::number((dispo * 100) / total, 'f', 2) + "%");
            QString b = QString("Sfax  " + QString::number((dispo1 * 100) / total, 'f', 2) + "%");
            QString c = QString("Sousse  " + QString::number((dispo2 * 100) / total, 'f', 2) + "%");

            QPieSeries *series = new QPieSeries();
            series->append(a, dispo);
            series->append(b, dispo1);
            series->append(c, dispo2);

            if (dispo != 0)
            {
                QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());
            }

            if (dispo1 != 0)
            {
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setLabelVisible();
            }

            if (dispo2 != 0)
            {
                QPieSlice *slice2 = series->slices().at(2);
                slice2->setLabelVisible();
            }

            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("lieu OffreEmploi : nombre des OffreEmplois" + QString::number(total));

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000, 500);
            chartView->show();


}
