#ifndef CANDIDATS_H
#define CANDIDATS_H


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
class CANDIDATS
{
    public:
        CANDIDATS();
        CANDIDATS(int,QString,QString,QDate,QString,QString,QString);

//getters
        int getID_candidat();
        QString getnom();
        QString getprenom();
        QDate getdatenaissance();
        QString getniveau();
        QString getemail();
        QString getnumtel();


        void setID_candidat(int);
        void setnom(QString);
        void setprenom(QString );
        void setdatenaissance(QDate);
        void setniveau(QString );
        void setemail(QString );
        void setnumtel(QString );


        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(int);
        bool modifier(int);
        bool checkIfIdExists(QString);


        QSqlQueryModel *rechercher(QString);
        QSqlQueryModel *trier(QString);
        QSqlQueryModel* selectCANDIDATSById(int ID_candidat);
private:
    int ID_candidat;
    QString nom;
    QString prenom;
    QDate datenaissance;
    QString niveau;
    QString email;
    QString numtel;

};


#endif // CANDIDATS_H
