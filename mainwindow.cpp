#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_CANDIDATS->setModel(C.afficher());//refresh
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
        QString niveau=ui->lineEdit_niveau->text();
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
         ui->lineEdit_niveau->clear();
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
          ui->tableView_CANDIDATS->setModel(C.selectCANDIDATSById(ID_candidat));//refresh
         QMessageBox::information(nullptr, QObject::tr("ok"),
         QObject::tr("suppression effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView_CANDIDATS->setModel(C.selectCANDIDATSById(ID_candidat));//refresh
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
    QString lieu=ui->lineEdit_lieu->text();
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
     ui->lineEdit_lieu->clear();
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
      ui->tableView_OffresEmplois->setModel(O.selectOFFRES_EMPLOISById(ID_OffreEmploi));//refresh
     QMessageBox::information(nullptr, QObject::tr("ok"),
     QObject::tr("suppression effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);
ui->tableView_OffresEmplois->setModel(O.selectOFFRES_EMPLOISById(ID_OffreEmploi));//refresh
  }
   else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
     QObject::tr("suppression non effectué.\n"
                 "Click Cancel to exit."), QMessageBox::Cancel);

}
