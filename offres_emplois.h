#ifndef OFFRES_EMPLOIS_H
#define OFFRES_EMPLOIS_H


#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlQuery>
#include <QDateTime>
#include <QFile>
#include <QDebug>
class OFFRES_EMPLOIS
{
    public:
        OFFRES_EMPLOIS();
        OFFRES_EMPLOIS(int,QString,QString,QString,int,QString,int);

//getters
        int getID_OffreEmploi();
        QString gettitre();
        QString getdescription();
        QDate getdatepublication();
        int getnbrplace();
        QString getlieu();
        int getID_condidat();


        void setID_OffreEmploi(int);
        void settitre(QString);
        void setdescription(QString );
        void setdatepublication(QDate);
        void setnbrplace(int );
        void setlieu(QString );
        void setID_candidat(int );


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(QString);
        bool modifier(QString);
        bool checkIfIdExists(QString);


        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *trier(QString);

private:
    QString ID_OffreEmploi;
    QString titre;
    QString description;
    QDate datepublication;
    QString place;
    QString lieu;
    QString ID_candidat;

};

#endif // OFFRES_EMPLOIS_H
