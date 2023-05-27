#include "lecteurvue.h"
#include "ui_lecteurvue.h"
#include <iostream>
#include <QPixmap>
#include <ctime>
#include <unistd.h>
#include <QSqlQuery>
#include <QSqlQueryModel>


lecteurVue::lecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lecteurVue)
{
    ui->setupUi(this);
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
    connect(ui->bPrecedent,SIGNAL(clicked()),this,SLOT(rec()));
    connect(ui->bSuivant,SIGNAL(clicked()),this,SLOT(av()));
    connect(ui->bArreterDiaporama,SIGNAL(clicked()),this,SLOT(arreterDiaporama()));
    connect(ui->bLancerDiaporama,SIGNAL(clicked()),this,SLOT(lancerDiaporama()));
    connect(ui->bCatgorie,SIGNAL(clicked()),this,SLOT(changerMode()));

    connect(ui->actionQuitter_2, &QAction::triggered, this, &lecteurVue::fermertous);
    connect(ui->actionA_propos_de, &QAction::triggered, this, &lecteurVue::aide);
    connect(ui->actioncharger_diaporama_2, &QAction::triggered, this, &lecteurVue::chargerdiapo1);
    connect(ui->actionenlever_diaporama_2, &QAction::triggered, this, &lecteurVue::enleverdiapo1);
    connect(ui->actionvitesse_de_d_filement, &QAction::triggered, this, &lecteurVue::defile);

    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        if (_numDiaporamaCourant!=0)
        {
            if (etat==automatique)
            {
                compteur++;
                if (compteur >= vitesse_defilement )
                {
                    compteur=0;
                    avancer(0);
                }
                timer.start(1000);
            }
        }
     });

    etat = automatique;
    db = new database();
    bool ouvertureOK = db->openDatabase();
    db->closeDatabase();
    cout << "la connexion est faite ? : " << ouvertureOK  << endl;





}



lecteurVue::~lecteurVue()
{
    delete ui;
}

void lecteurVue::lancer()
{
    etat=automatique;
    timer.start(1000);
}



void lecteurVue::avancer(int prov)
{
    qDebug() << "avancer";
    if (prov==1)
        {etat=manuel;}

    if (_posImageCourante +1 > nbImages()-1 )
        {_posImageCourante = _posImageCourante +1 - nbImages();}
    else
        {_posImageCourante ++;}

    cout << _diaporama[_posImageCourante]->getCategorie() << "....." << CategorieImageCourant << endl;
    if (_diaporama[_posImageCourante]->getCategorie() != CategorieImageCourant and CategorieImageCourant != "tous")
        {avancer(0);}
    afficher();

}

void lecteurVue::reculer(int prov)
{
    if (prov==1)
    {etat=manuel;}

    if (_posImageCourante  == 0 )
    {_posImageCourante =  nbImages()-1;}
    else
    {_posImageCourante--;}
    if (_diaporama[_posImageCourante]->getCategorie() != CategorieImageCourant and CategorieImageCourant != "tous")
    {
        reculer(0);
    }
    afficher();
}

void lecteurVue::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant

    }

}

void lecteurVue::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */

    //QSqlQuery maRequete("select Article.reference,Article.descriptif,Article.prixHT,Categorie.libelle FROM Article join Categorie on Article.CodeCategorie=Categorie.CodeCategorie");
    //maRequete.value(0).toString()
    //for (int i=0;maRequete.next(); i++)

    /*
     *quelle diaporama ? (nom ou ID) (Diaporamas) #FAIT
     *recup la vitesse depuis quelle diapo (Diaporamas) #FAIT
     *recup l'id des diapo qui a partienent a diaporama choisit (diaposDansDiaporama)
     *recup au passage leurs rangs(diaposDansDiaporama)
     * ensuite on recuppour les ID diapo choisit leurs ID titre famille et URL (Diapo)
     * puis on recup pour chaque diapo la famille a partir de leur ID famille (Familles)
     * importe le tous
     *
     */
    QString larequete = "select vitesseDefilement from Diaporamas where idDiaporama =" + QString::number(_numDiaporamaCourant);
    QSqlQuery maRequete1(larequete);
    maRequete1.next();
    vitesse_defilement = maRequete1.value(0).toInt();

    larequete = "select idDiapo,rang from DiaposDansDiaporama where idDiaporama =" + QString::number(_numDiaporamaCourant);
    QSqlQuery maRequete2(larequete);
    Image* imageACharger;

    for (int i=0;maRequete2.next(); i++)
    {
        imageACharger = new Image();
        imageACharger->setRang(maRequete2.value(1).toUInt());
        larequete = "select titrePhoto,idFam,uriPhoto from Diapos where idphoto =" + maRequete2.value(0).toString();
        QSqlQuery maRequete3(larequete);
        maRequete3.next();
        imageACharger->setTitre((maRequete3.value(0).toString()).toStdString());
        imageACharger->setChemin(chemin+(maRequete3.value(2).toString()).toStdString());
        larequete = "select nomFamille from Familles where idFamille =" + maRequete3.value(1).toString();
        QSqlQuery maRequete4(larequete);
        maRequete4.next();
        imageACharger->setCategorie((maRequete4.value(0).toString()).toStdString());
        _diaporama.push_back(imageACharger);
    }
    delete imageACharger;

    /*

    Image* imageACharger;
    imageACharger = new Image(3, "animal", "Dalmatien", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Alice", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Bambi", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_3.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Cendrillon", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_4.gif");
    _diaporama.push_back(imageACharger);
    */

     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
    for (unsigned int i = 0; i < nbImages() - 1; i++)
    {
        for (unsigned int j = 0; j < nbImages() - i - 1; j++)
        {
            // Comparaison des deux éléments adjacents
            if (_diaporama[j]->getRang() > _diaporama[j+1]->getRang())
            {
                // Échange des deux éléments
                Image* temp = _diaporama[j];
                _diaporama[j] = _diaporama[j+1];
                _diaporama[j+1] = temp;
            }
        }
    }
    _posImageCourante = 0;
    cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
    cout << nbImages() << " images chargees dans le diaporama" << endl;


    afficher();
    avancer(0);




}

void lecteurVue::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void lecteurVue::afficher()
{
    /* affiche les information sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    //nb d'image charger
    //num di diaporama
    //l'image courant
    if (_numDiaporamaCourant == 0)
    {
        cout << "lecteur vide" <<endl;
    }
    else
    {
        if (_numDiaporamaCourant > 0)
        {
            cout << "Diaporama num."<< _numDiaporamaCourant<<endl;
            _diaporama[_posImageCourante]->afficher() ;
            //=================================            

            ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin() )));

            ui->lTitre->setText(QString::fromStdString(_diaporama[_posImageCourante]->getTitre() ));
            ui->lRang->setText(QString::number(_diaporama[_posImageCourante]->getRang()));

            string lemode;
            if (etat==manuel)
            {
                lemode="manuel";
            }
            else
            {
                lemode="automatique";
            }
            std::string texte = "mode : " + lemode;
            ui->bMode->setText(QString::fromStdString(texte));

        }
        else
        {
            cout << "diaporama vide" <<endl;
        }
    }


}


unsigned int lecteurVue::nbImages()
{
    return _diaporama.size();
}

Image *lecteurVue::imageCourante()
{

    if (numDiaporamaCourant() == 0 || nbImages() == 0)
    {
        return nullptr; // retourne un pointeur nul si le lecteur est vide ou si le diaporama courant n'a pas d'images
    }
    else
    {
        return _diaporama[_posImageCourante]; // retourne un pointeur vers l'image courante
    }
}

unsigned int lecteurVue::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}

void lecteurVue::lancerDiaporama()
{
    if (_numDiaporamaCourant != 0)
    {lancer();}


}

void lecteurVue::av()
{
    avancer(1);
}

void lecteurVue::rec()
{
    reculer(1);
}

void lecteurVue::arreterDiaporama()
{
    etat=manuel;
}

void lecteurVue::fermertous()
{
    this->close();
}

void lecteurVue::aide()
{
    info *fen_aide= new info();
    fen_aide->exec();
}

void lecteurVue::chargerdiapo1()
{
    demandeDiaporama *fen_demandeDiapo= new demandeDiaporama();
    fen_demandeDiapo->exec();
    changerDiaporama(fen_demandeDiapo->recupTexte().toInt());
}

void lecteurVue::enleverdiapo1()
{
    viderDiaporama();
    _numDiaporamaCourant =0;
}

void lecteurVue::defile()
{
    vit *fen_defile= new vit();
    fen_defile->setSpine(vitesse_defilement);
    fen_defile->exec();
    vitesse_defilement=fen_defile->valueSpine();
}

void lecteurVue::changerMode()
{
    if (cat_actuelle +1 > 3 )
    {
        cat_actuelle = 0;
    }
    else
    {cat_actuelle ++;}
    string lemode=lst_categorie[cat_actuelle];
    CategorieImageCourant=lemode;
    std::string texte = "type catégorie : " + lemode;
    ui->bCatgorie->setText(QString::fromStdString(texte));
}









