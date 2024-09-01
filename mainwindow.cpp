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
#include "QrCode.hpp"
using namespace qrcodegen;
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
        // Réinitialisez les étiquettes d'erreur à vide
            ui->label_ID_candidat->setText("");
            ui->label_nom->setText("");
            ui->label_prenom->setText("");
            ui->label_datenaissance->setText("");
            ui->label_niveau->setText("");
            ui->label_email->setText("");
            ui->label_numtel->setText("");

        int ID_candidat=ui->lineEdit_ID_candidat->text().toInt();
        QString nom=ui->lineEdit_nom->text();
        QString prenom=ui->lineEdit_prenom->text();
        QDate datenaissance = ui->lineEdit_datenaissance->date();
        QString niveau=ui->comboBox_niveaucandidat->currentText();
        QString email=ui->lineEdit_email->text();
        QString numtel=ui->lineEdit_numtel->text();
        bool isValid = true;
        QString ID_candidatString = QString::number(ID_candidat);
        if (ID_candidatString.isEmpty()) {
                ui->label_ID_candidat->setText("<font color='red'>ID_candidat ne peut pas être vide!!!!</font>");
                isValid = false;
            }

            if (nom.isEmpty()) {
                ui->label_nom->setText("<font color='red'>nom ne peut pas être vide!!!</font>");
                isValid = false;
            }

            if (prenom.isEmpty()) {
                ui->label_prenom->setText("<font color='red'>prenom ne peut pas être vide!!!</font>");
                isValid = false;
            }
            QString datenaissanceString = datenaissance.toString("yyyy-MM-dd");
            if (datenaissanceString.isEmpty()) {
                ui->label_datenaissance->setText("<font color='red'>datenaissance ne peut pas être vide!!!</font>");
                isValid = false;
            }
            if (niveau.isEmpty()) {
                ui->label_niveau->setText("<font color='red'>niveau ne peut pas être vide!!!</font>");
                isValid = false;
            }
            if (email.isEmpty()) {
                ui->label_email->setText("<font color='red'>email ne peut pas être vide!!!</font>");
                isValid = false;
            }
            if (numtel.isEmpty()) {
                ui->label_numtel->setText("<font color='red'>numtel ne peut pas être vide!!!</font>");
                isValid = false;
            }

            QSqlQuery checkQuery;
            checkQuery.prepare("SELECT ID_candidat FROM CANDIDATS WHERE ID_candidat = :ID_candidat");
            checkQuery.bindValue(":ID_candidat", ID_candidat);
            if (checkQuery.exec() && checkQuery.next()) {
                ui->label_ID_candidat->setText("<font color='red'>ID_candidat existe déjà!!!!</font>");
                isValid = false;
            }


            if (isValid) {
                // Si l'entrée est valide et que l'ID_candidat n'existe pas, procédez à l'ajout de CANDIDATS
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
         ui->lineEdit_numtel->clear();

         ui->label_ID_candidat->clear();
         ui->label_nom->clear();
         ui->label_prenom->clear();
         ui->label_email->clear();
         ui->label_numtel->clear();
         ui->label_ID_candidat_2->clear();
         on_pushButton_success_clicked();
        }


        else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("ajout non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
    }
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
         on_pushButtonSupprimer_success_clicked();
      }
       else
         QMessageBox::critical(nullptr, QObject::tr("not ok"),
         QObject::tr("suppression non effectué.\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);


    }

void MainWindow::on_pushButton_Ajouter2_clicked()
{
    // Réinitialisez les étiquettes d'erreur à vide
    ui->label_ID_OffreEmploi->setText("");
    ui->label_titre->setText("");
    ui->label_description->setText("");
    ui->label_datepublication->setText("");
    ui->label_nbrplace->setText("");
    ui->label_lieu->setText("");
    ui->label_ID_candidat_2->setText("");

    // Récupérer les valeurs des champs
    QString ID_OffreEmploiStr = ui->lineEdit_ID_OffreEmploi->text();
    QString titre = ui->lineEdit_titre->text();
    QString description = ui->lineEdit_description->text();
    QDate datepublication = ui->lineEdit_datepublication->date();  // Utilisez dateEdit au lieu de lineEdit
    QString nbrplaceStr = ui->lineEdit_nbrplace->text();
    QString lieu = ui->comboBox_lieuOffreEmploi->currentText();
    QString ID_candidat_2Str = ui->lineEdit_ID_candidat_2->text();

    bool isValid = true;

    // Validation des champs
    if (ID_OffreEmploiStr.isEmpty()) {
        ui->label_ID_OffreEmploi->setText("<font color='red'>ID_OffreEmploi ne peut pas être vide!!!!</font>");
        isValid = false;
    }

    if (titre.isEmpty()) {
        ui->label_titre->setText("<font color='red'>titre ne peut pas être vide!!!</font>");
        isValid = false;
    }

    if (description.isEmpty()) {
        ui->label_description->setText("<font color='red'>description ne peut pas être vide!!!</font>");
        isValid = false;
    }

    QString datepublicationStr = datepublication.toString("yyyy-MM-dd");
    if (datepublicationStr.isEmpty()) {
        ui->label_datepublication->setText("<font color='red'>Date de publication ne peut pas être vide!!!</font>");
        isValid = false;
    }

    if (nbrplaceStr.isEmpty()) {
        ui->label_nbrplace->setText("<font color='red'>Nombre de places ne peut pas être vide!!!</font>");
        isValid = false;
    }

    if (lieu.isEmpty()) {
        ui->label_lieu->setText("<font color='red'>Lieu ne peut pas être vide!!!</font>");
        isValid = false;
    }

    if (ID_candidat_2Str.isEmpty()) {
        ui->label_ID_candidat_2->setText("<font color='red'>ID Candidat ne peut pas être vide!!!</font>");
        isValid = false;
    }
    int ID_OffreEmploi = ID_OffreEmploiStr.toInt();
    int nbrplace = nbrplaceStr.toInt();
    int ID_candidat_2 = ID_candidat_2Str.toInt();
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ID_OffreEmploi FROM OFFRES_EMPLOIS WHERE ID_OffreEmploi = :ID_OffreEmploi");
    checkQuery.bindValue(":ID_OffreEmploi", ID_OffreEmploi);

    if (!checkQuery.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête: " << checkQuery.lastError().text();
    } else if (checkQuery.next()) {
        qDebug() << "ID exists: " << checkQuery.value(0).toString();  // Debug output
        ui->label_ID_OffreEmploi->setText("<font color='red'>ID Offre Emploi existe déjà!!!!</font>");
        return; // Retourne ici si l'ID existe déjà pour éviter d'exécuter le reste du code
    }

    // Si tous les champs sont valides, vérifiez l'existence de l'ID dans la base de données
    if (isValid) {



        // Si l'ID n'existe pas, ajouter l'offre
        OFFRES_EMPLOIS O(ID_OffreEmploi, titre, description, datepublication, nbrplace, lieu, ID_candidat_2);
        bool test = O.ajouter();
        if (test) {
            ui->tableView_OffresEmplois->setModel(O.afficher());

            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("Ajout effectué.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

            // Réinitialiser les champs après un ajout réussi
            ui->lineEdit_ID_OffreEmploi->clear();
            ui->lineEdit_titre->clear();
            ui->lineEdit_description->clear();
            ui->lineEdit_nbrplace->clear();
            ui->comboBox_lieuOffreEmploi->setCurrentIndex(0);
            ui->lineEdit_ID_candidat_2->clear();

            // Effacer les labels d'erreur
            ui->label_ID_OffreEmploi->clear();
            ui->label_titre->clear();
            ui->label_description->clear();
            ui->label_datepublication->clear();
            ui->label_nbrplace->clear();
            ui->label_lieu->clear();
            ui->label_ID_candidat_2->clear();
        } else {
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                  QObject::tr("Ajout non effectué.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }
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
        ui->lineEdit_nbrplace->setText(QString::number(nbrplace));
        ui->comboBox_lieuOffreEmploi->currentText();
        ui->lineEdit_ID_candidat_2->setText(QString::number(ID_candidat_2));
}

void MainWindow::on_pushButton_Modifier_clicked()
{
    int ID_candidat=ui->lineEdit_ID_OffreEmploi->text().toInt();
    QString nom=ui->lineEdit_titre->text();
    QString prenom=ui->lineEdit_description->text();
    QDate datenaissance = ui->lineEdit_datepublication->date();
    QString niveau=ui->lineEdit_nbrplace->text();
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
    ui->lineEdit_numtel->clear();
    on_pushButtonModifier_success_clicked();
    }


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
        int nbrplace=ui->lineEdit_nbrplace->text().toInt();
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
         ui->lineEdit_nbrplace->clear();
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

void MainWindow::on_pushButton_Recherche_clicked()
{
    CANDIDATS C;

    int index = ui->comboBox_recherche->currentIndex();
    QString wh;
    QSqlQueryModel* model = new QSqlQueryModel();
    QString k = ui->lineEdit_recherche->text().trimmed(); // Trimmed to remove leading and trailing whitespace

    if (k.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Empty field.\nClick Cancel to exit."), QMessageBox::Cancel);
        return;
    }

    if (index == 0) {
        if (!C.idDisponible(k.toInt())) {
            wh = "ID_candidat=" + k;
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("ID_candidat unavailable.\nClick Cancel to exit."), QMessageBox::Cancel);
            return;
        }
    } else if (index == 1) {
        wh = "prenom='" + k + "'";
    } else if (index == 2) {
        wh = "niveau='" + k + "'";
    }

    if (C.rech(wh)) {
        model->setQuery("SELECT * FROM CANDIDATS WHERE " + wh);
        ui->tableView_CANDIDATS->setModel(model);

        if (model->rowCount() == 0) {
            QMessageBox::information(nullptr, QObject::tr("No Results"), QObject::tr("No candidates found.\nClick Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("Search performed.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Search failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_Recherche_2_clicked()
{
    OFFRES_EMPLOIS O;

        int index = ui->comboBox_recherche_2->currentIndex();
        QString wh;
        QSqlQueryModel* model = new QSqlQueryModel();
        QString k = ui->lineEdit_recherche_2->text().trimmed(); // Trimmed to remove leading and trailing whitespace

        if (k.isEmpty()) {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Empty field.\nClick Cancel to exit."), QMessageBox::Cancel);
            return;
        }

        if (index == 0) {
            if (!O.idDisponible(k.toInt())) {
                QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("ID_OffreEmploi unavailable.\nClick Cancel to exit."), QMessageBox::Cancel);
                return;
            }
            wh = "ID_OffreEmploi=" + k;
        } else if (index == 1) {
            wh = "titre='" + k + "'";
        } else if (index == 2) {
            wh = "lieu='" + k + "'";
        }
        if (O.rech(wh)) {
            QMessageBox::information(nullptr, QObject::tr("Success"), QObject::tr("Search performed.\nClick Cancel to exit."), QMessageBox::Cancel);
            model->setQuery("SELECT * FROM OFFRES_EMPLOIS WHERE " + wh);
            ui->tableView_OffresEmplois->setModel(model);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Search failed.\nClick Cancel to exit."), QMessageBox::Cancel);
        }

}

void MainWindow::on_pushButton_refrech_clicked()
{
    ui->tableView_CANDIDATS->setModel(C.afficher());
}

void MainWindow::on_pushButton_refrech_2_clicked()
{
    ui->tableView_OffresEmplois->setModel(O.afficher());

}


void MainWindow::on_pushButton_Tri_clicked()
{
    int index=ui->comboBox_Tri->currentIndex();
           QString orderByClause;
           QSqlQueryModel* model=new QSqlQueryModel();
           if (index == 0) {
                       orderByClause = " ORDER BY ID_candidat DESC ";
                   } else if (index == 1) {
                       orderByClause = " ORDER BY prenom ";
                   } else if (index == 2) {
                       orderByClause = " ORDER BY niveau ";
                   }

           if (C.tri(orderByClause)) {
               QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
                model->setQuery("SELECT *  FROM CANDIDATS"+orderByClause);
               ui->tableView_CANDIDATS->setModel(model);
           } else {
              QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
           }
}

void MainWindow::on_pushButton_Tri_2_clicked()
{
    int index=ui->comboBox_Tri_2->currentIndex();
           QString orderByClause;
           QSqlQueryModel* model=new QSqlQueryModel();
           if (index == 0) {
                       orderByClause = " ORDER BY ID_OffreEmploi DESC ";
                   } else if (index == 1) {
                       orderByClause = " ORDER BY titre ";
                   } else if (index == 2) {
                       orderByClause = " ORDER BY nbrplace ";
                   }

           if (O.tri(orderByClause)) {
               QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Tri effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
                model->setQuery("SELECT *  FROM OFFRES_EMPLOIS"+orderByClause);
               ui->tableView_OffresEmplois->setModel(model);
           } else {
              QMessageBox::critical(nullptr,QObject::tr(" not ok"),QObject::tr("tri non effectue \n""Click cancel to exit ."),QMessageBox::Cancel);
           }
}

void MainWindow::on_pushButton_PDF_clicked()
{
    QPdfWriter pdf("C:/Users/msn26/Desktop/PROJET QT/Atelier_Connexion/Atelier_Connexion/list-CANDIDATS.pdf");

            QPainter painter(&pdf);
                   int i = 4000;
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Book Script", 20, QFont::Bold));
                   painter.drawText(2500, 1400, "LISTE DES CANDIDATS");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Time New Roman", 10));
                   painter.drawRect(100, 100, 9200, 2700);
                   painter.drawRect(100, 3000, 9200, 500);

                   painter.drawText(300,3300,"ID_candidat");
                   painter.drawText(1500,3300,"nom");
                   painter.drawText(2500,3300,"prenom");
                   painter.drawText(3500,3300,"datenaissance");
                   painter.drawText(5300,3300,"niveau");
                   painter.drawText(6500,3300,"email");
                   painter.drawText(8300,3300,"numtel");
                   QImage image("C:/Users/msn26/Desktop/PROJET QT/Atelier_Connexion/Atelier_Connexion/logoEsprit.jpg");
                   painter.drawImage(QRectF(200, 200, 2000, 2000), image);
                   QImage image1("C:/Users/msn26/Desktop/PROJET QT/Atelier_Connexion/Atelier_Connexion/click_taf_recrutement.png");
                   painter.drawImage(QRectF(7000, 200, 2000, 2000), image1);
                   painter.drawRect(100, 3700, 9200, 9000);
                   QSqlQuery query;
                   query.prepare("select * from CANDIDATS");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(300, i, query.value(0).toString());
                       painter.drawText(1300, i, query.value(1).toString());
                       painter.drawText(2500, i, query.value(2).toString());
                       painter.drawText(3500, i, query.value(3).toString());
                       painter.drawText(5300, i, query.value(4).toString());
                       painter.drawText(6500, i, query.value(5).toString());
                       painter.drawText(8300, i, query.value(6).toString());
                       i = i + 350;
                   }
                   QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                       QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_PDF_2_clicked()
{
    QPdfWriter pdf("C:/Users/msn26/Desktop/PROJET QT/Atelier_Connexion/Atelier_Connexion/list-OFFRES_EMPLOIS.pdf");

            QPainter painter(&pdf);
                   int i = 4000;
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Book Script", 20, QFont::Bold));
                   painter.drawText(2500, 1400, "LISTE OFFRES_EMPLOIS");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Time New Roman", 10));
                   painter.drawRect(100, 100, 9200, 2700);
                   painter.drawRect(100, 3000, 9200, 500);

                   painter.drawText(300,3300,"ID_OffreEmploi");
                   painter.drawText(1500,3300,"titre");
                   painter.drawText(2500,3300,"description");
                   painter.drawText(3500,3300,"datepublication");
                   painter.drawText(5300,3300,"nbrplace");
                   painter.drawText(6500,3300,"lieu");
                   painter.drawText(8300,3300,"number");
                   QImage image("C:/Users/msn26/Desktop/PROJET QT/Atelier_Connexion/Atelier_Connexion/logoEsprit.jpg");
                   painter.drawImage(QRectF(200, 200, 2000, 2000), image);
                   QImage image1("C:/Users/msn26/Desktop/PROJET QT/Atelier_Connexion/Atelier_Connexion/click_taf_recrutement.png");
                   painter.drawImage(QRectF(7000, 200, 2000, 2000), image1);
                   painter.drawRect(100, 3700, 9200, 9000);
                   QSqlQuery query;
                   query.prepare("select * from OFFRES_EMPLOIS");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(300, i, query.value(0).toString());
                       painter.drawText(1300, i, query.value(1).toString());
                       painter.drawText(2500, i, query.value(2).toString());
                       painter.drawText(3500, i, query.value(3).toString());
                       painter.drawText(5300, i, query.value(4).toString());
                       painter.drawText(6500, i, query.value(5).toString());
                       painter.drawText(8300, i, query.value(6).toString());
                       i = i + 350;
                   }
                   QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                       QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_qrcodegen_clicked()
{
    QString value = ui->lineEdit_qrcode->text();

        QSqlQuery qry;
        qry.prepare("SELECT * FROM CANDIDATS WHERE ID_candidat = :ID_candidat");
        qry.bindValue(":ID_candidat", value);
        qry.exec();

        if (qry.next()) {
            // ID_candidat exists in the database
            QString ID_candidat = qry.value(0).toString();
            QString nom = qry.value(1).toString();
            QString prenom = qry.value(2).toString();
            QString datenaissance = qry.value(3).toString();
            QString niveau = qry.value(4).toString();
            QString email = qry.value(5).toString();
            QString numtel = qry.value(6).toString();

            QString text = "ID_candidat " + ID_candidat + "\n" + "nom " + nom + "\n" + "prenom " + prenom + "\n" +
                           "datenaissance " + datenaissance + "\n" + "niveau " + niveau+ "\n" + "email " + email+ "\n" + "numtel " + numtel;

            // Create the QR Code object
            QrCode qr = QrCode::encodeText(text.toUtf8().data(), QrCode::Ecc::MEDIUM);

            qint32 sz = qr.getSize();
            QImage im(sz, sz, QImage::Format_RGB32);
            QRgb black = qRgb(191, 112, 105);
            QRgb white = qRgb(255, 255, 255);

            for (int y = 0; y < sz; y++) {
                for (int x = 0; x < sz; x++) {
                    im.setPixel(x, y, qr.getModule(x, y) ? black : white);
                }
            }

            ui->qrcodecommande->setPixmap(QPixmap::fromImage(im.scaled(200, 200, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));
        } else {
            // ID does not exist in the database
            QMessageBox::critical(nullptr, QObject::tr("ID_candidat introuvable"),
                QObject::tr("L'ID que vous avez saisi n'existe pas.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

#include "Result.h"
#include "Operation.h"
#include "NotificationWidget.h"
#include "NotificationLayout.h"
void MainWindow::on_pushButton_success_clicked()
{

    NotificationParams params;
    params.title = "CANDIDATS a été ajoutée avec succées";
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    params.detailsButtonText = "Try again";
    notificationLayout.AddNotificationWidget(this, params);
}
void MainWindow::on_pushButtonModifier_success_clicked()
{

    NotificationParams params;
    params.title = "CANDIDATS a été modifiée avec succées";
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    params.detailsButtonText = "Try again";
    notificationLayout.AddNotificationWidget(this, params);
}
void MainWindow::on_pushButtonSupprimer_success_clicked()
{

    NotificationParams params;
    params.title = "CANDIDATS a été supprimée avec succées";
    params.message = Operation::DoSomething(Result::RESULT_SUCCESS);
    params.detailsButtonText = "Try again";
    notificationLayout.AddNotificationWidget(this, params);
}
