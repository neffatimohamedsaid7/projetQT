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
        OFFRES_EMPLOIS(int,QString,QString,QDate,int,QString,int);

//getters
        int getID_OffreEmploi();
        QString gettitre();
        QString getdescription();
        QDate getdatepublication();
        int getnbrplace();
        QString getlieu();
        int getID_candidat();


        void setID_OffreEmploi(int);
        void settitre(QString);
        void setdescription(QString );
        void setdatepublication(QDate);
        void setnbrplace(int );
        void setlieu(QString );
        void setID_candidat(int );


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(int);



        QSqlQueryModel* selectOFFRES_EMPLOISById(int ID_OFFRE_EMPLOI);
        bool idDisponible(int);
        bool rech(QString);
        bool tri(QString);

private:
    int ID_OffreEmploi;
    QString titre;
    QString description;
    QDate datepublication;
    int nbrplace;
    QString lieu;
    int ID_candidat;

};

#endif // OFFRES_EMPLOIS_H
