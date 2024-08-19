#include "offres_emplois.h"

OFFRES_EMPLOIS::OFFRES_EMPLOIS()
{

}
OFFRES_EMPLOIS::OFFRES_EMPLOIS(int ID_OffreEmploi,QString titre,QString description,QDate datepublication,int nbrplace,QString lieu,int ID_candidat)
{this->ID_OffreEmploi=ID_OffreEmploi;
    this->titre = titre;
    this->description = description;
    this->datepublication = datepublication;
    this->nbrplace = nbrplace;
    this->lieu = lieu;
    this->ID_candidat = ID_candidat;

}

  int OFFRES_EMPLOIS::getID_OffreEmploi(){return ID_OffreEmploi;}
  QString OFFRES_EMPLOIS::gettitre(){return titre;}
  QString OFFRES_EMPLOIS::getdescription(){return description;}
  QDate OFFRES_EMPLOIS::getdatepublication(){return datepublication;}
  int OFFRES_EMPLOIS::getnbrplace(){return nbrplace;}
  QString OFFRES_EMPLOIS::getlieu(){return lieu;}
  int OFFRES_EMPLOIS::getID_candidat(){return ID_candidat;}


  void OFFRES_EMPLOIS::setID_OffreEmploi(int ID_OffreEmploi){this->ID_OffreEmploi=ID_OffreEmploi;}
  void OFFRES_EMPLOIS::settitre(QString titre){this->titre=titre;}
  void OFFRES_EMPLOIS::setdescription(QString description){this->description=description;}
  void OFFRES_EMPLOIS::setdatepublication(QDate datepublication){this->datepublication=datepublication;}
  void OFFRES_EMPLOIS::setnbrplace(int nbrplace ){this->nbrplace=nbrplace;}
  void OFFRES_EMPLOIS::setlieu(QString lieu ){this->lieu=lieu;}
  void OFFRES_EMPLOIS::setID_candidat(int ID_candidat ){this->ID_candidat=ID_candidat;}

  bool OFFRES_EMPLOIS::ajouter()
  {

      QSqlQuery query;

      query.prepare("INSERT INTO OFFRES_EMPLOIS (ID_OffreEmploi,titre,description,datepublication,nbrplace,lieu,ID_candidat)"
                    "values(:ID_OffreEmploi,:titre,:description,:datepublication,:nbrplace,:lieu,:ID_candidat)");
      query.bindValue(":ID_OffreEmploi",ID_OffreEmploi);
          query.bindValue(":titre",titre);
           query.bindValue(":description",description);
           query.bindValue(":datepublication",datepublication);
           query.bindValue(":nbrplace",nbrplace);
           query.bindValue(":lieu",lieu);
           query.bindValue(":ID_candidat",ID_candidat);

            return query.exec();

     };

  QSqlQueryModel * OFFRES_EMPLOIS::afficher(){
      QSqlQueryModel * model = new QSqlQueryModel();
      model->setQuery("select * from OFFRES_EMPLOIS");
      model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_OffreEmploi"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("titre"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("datepublication"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("nbrplace"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("lieu"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("ID_candidat"));


      return model;
  }

  bool OFFRES_EMPLOIS::supprimer(int ID_OffreEmploi)
   {
        QSqlQuery query;
         QString ID_OffreEmploiString=QString::number(ID_OffreEmploi);
         query.prepare("delete from OFFRES_EMPLOIS where ID_OffreEmploi=:ID_OffreEmploi");
                       //bindValue ID_OffreEmploi =>ID_OffreEmploistring
         query.bindValue(":ID_OffreEmploi",ID_OffreEmploiString);
                  return query.exec();
   }


  bool OFFRES_EMPLOIS::modifier(QString ID_OffreEmploi)
  {
  QSqlQuery query;
          QString res= ID_OffreEmploi;


          query.prepare("UPDATE OFFRES_EMPLOIS SET titre=:titre,description=:description,datepublication=:datepublication,nbrplace=:nbrplace,lieu=:lieu,ID_candidat=:ID_candidat where ID_OffreEmploi=:ID_OffreEmploi");
          query.bindValue(":ID_OffreEpmloi",ID_OffreEmploi);
              query.bindValue(":titre",titre);
               query.bindValue(":description",description);
               query.bindValue(":datepublication",datepublication);
               query.bindValue(":nbrplace",nbrplace);
               query.bindValue(":lieu",lieu);
               query.bindValue(":ID_candidat",ID_candidat);



          return    query.exec();
  }

  QSqlQueryModel* OFFRES_EMPLOIS::selectOFFRES_EMPLOISById(int ID_OffreEmploi)
   {
       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery query;
       query.prepare("SELECT * FROM OFFRES_EMPLOIS WHERE ID_OffreEmploi = :ID_OffreEmploi");
       query.bindValue(":ID_OffreEmploi", ID_OffreEmploi);
       if(query.exec())
       {
           model->setQuery(query);
           if(model->rowCount() == 1) // Check if exactly one row is returned
           {
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_OffreEmploi"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("datepublication"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("nbrplace"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("lieu"));
               model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_candidat"));
               return model;
           }
           else
           {
               qDebug() << "Error: No row or more than one row returned for ID_OffreEmploi:" << ID_OffreEmploi;
               delete model;
               return nullptr;
           }
       }
       else
       {
           qDebug() << "Query execution failed.";
           delete model;
           return nullptr;
       }
   }
