#include "candidats.h"

CANDIDATS::CANDIDATS()
{

}

CANDIDATS::CANDIDATS(int ID_candidat,QString nom,QString prenom,QDate datenaissance,QString niveau,QString email,QString numtel)
{this->ID_candidat=ID_candidat;
    this->nom = nom;
    this->prenom = prenom;
    this->datenaissance = datenaissance;
    this->niveau = niveau;
    this->email = email;
    this->numtel = numtel;

}

  int CANDIDATS::getID_candidat(){return ID_candidat;}
  QString CANDIDATS::getnom(){return nom;}
  QString CANDIDATS::getprenom(){return prenom;}
  QDate CANDIDATS::getdatenaissance(){return datenaissance;}
  QString CANDIDATS::getniveau(){return niveau;}
  QString CANDIDATS::getemail(){return email;}
  QString CANDIDATS::getnumtel(){return numtel;}

  void CANDIDATS::setID_candidat(int ID_candidat){this->ID_candidat=ID_candidat;}
  void CANDIDATS::setnom(QString nom){this->nom=nom;}
  void CANDIDATS::setprenom(QString prenom){this->prenom=prenom;}
  void CANDIDATS::setdatenaissance(QDate datenaissance){this->datenaissance=datenaissance;}
  void CANDIDATS::setniveau(QString niveau ){this->niveau=niveau;}
  void CANDIDATS::setemail(QString email ){this->email=email;}
  void CANDIDATS::setnumtel(QString numtel ){this->numtel=numtel;}

  bool CANDIDATS::ajouter()
  {

      QSqlQuery query;

      query.prepare("INSERT INTO CANDIDATS (ID_candidat,nom,prenom,datenaissance,niveau,email,numtel)"
                    "values(:ID_candidat,:nom,:prenom,:datenaissance,:niveau,:email,:numtel)");
      query.bindValue(":ID_candidat",ID_candidat);
          query.bindValue(":nom",nom);
           query.bindValue(":prenom",prenom);
           query.bindValue(":datenaissance",datenaissance);
           query.bindValue(":niveau",niveau);
           query.bindValue(":email",email);
           query.bindValue(":numtel",numtel);

            return query.exec();

     };

  QSqlQueryModel * CANDIDATS::afficher(){
      QSqlQueryModel * model = new QSqlQueryModel();
      model->setQuery("select * from CANDIDATS");
      model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_candidat"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("datenaissance"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("niveau"));
      model->setHeaderData(5,Qt::Horizontal,QObject::tr("email"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("numtel"));


      return model;
  }

  bool CANDIDATS::supprimer(int ID_candidat)
   {
        QSqlQuery query;
         QString ID_candidatString=QString::number(ID_candidat);
         query.prepare("delete from CANDIDATS where ID_candidat=:ID_candidat");
                       //bindValue ID_candidat =>ID_candidatstring
         query.bindValue(":ID_candidat",ID_candidatString);
                  return query.exec();
   }


  bool CANDIDATS::modifier(int ID_candidat)
  {
  QSqlQuery query;
          int res= ID_candidat;


          query.prepare("UPDATE CANDIDATS SET nom=:nom,prenom=:prenom,datenaissance=:datenaissance,niveau=:niveau,email=:email,numtel=:numtel where ID_candidat=:ID_candidat");
          query.bindValue(":ID_candidat",ID_candidat);
              query.bindValue(":nom",nom);
               query.bindValue(":prenom",prenom);
               query.bindValue(":datenaissance",datenaissance);
               query.bindValue(":niveau",niveau);
               query.bindValue(":email",email);
               query.bindValue(":numtel",numtel);



          return    query.exec();
  }

  QSqlQueryModel* CANDIDATS::selectCANDIDATSById(int ID_candidat)
   {
       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery query;
       query.prepare("SELECT * FROM CANDIDATS WHERE ID_candidat = :ID_candidat");
       query.bindValue(":ID_candidat", ID_candidat);
       if(query.exec())
       {
           model->setQuery(query);
           if(model->rowCount() == 1) // Check if exactly one row is returned
           {
               model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_candidat"));
               model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
               model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
               model->setHeaderData(3, Qt::Horizontal, QObject::tr("datenaissance"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("niveau"));
               model->setHeaderData(5, Qt::Horizontal, QObject::tr("email"));
               model->setHeaderData(6, Qt::Horizontal, QObject::tr("numtel"));
               return model;
           }
           else
           {
               qDebug() << "Error: No row or more than one row returned for ID_candidat:" << ID_candidat;
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


