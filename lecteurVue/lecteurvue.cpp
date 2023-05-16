#include "lecteurvue.h"
#include "ui_lecteurvue.h"
#include <iostream>
#include <QPixmap>
#include <ctime>
#include <unistd.h>


lecteurVue::lecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lecteurVue)
{
    ui->setupUi(this);
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
    connect(ui->bPrecedent,SIGNAL(clicked()),this,SLOT(rec()));
    connect(ui->bSuivant,SIGNAL(clicked()),this,SLOT(av()));
    connect(ui->bArreterDiaporama,SIGNAL(clicked()),this,SLOT(arreterDiaporama()));
    connect(ui->bLancerDiaporama,SIGNAL(clicked()),this,SLOT(test()));

    connect(ui->actionQuitter_2, &QAction::triggered, this, &lecteurVue::fermertous);

    connect(ui->actionA_propos_de, &QAction::triggered, this, &lecteurVue::aide);

    QObject::connect(&timer, &QTimer::timeout, [&]()
    {
        if (etat==automatique)
        {
            compteur++;
            if (compteur >= 2 )
            {
                compteur=0;
                avancer(0);
            }
            timer.start(1000);
        }

     });

    etat = automatique;
    //etat = manuel;
}



lecteurVue::~lecteurVue()
{
    delete ui;
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

    Image* imageACharger;
    imageACharger = new Image(3, "animal", "Dalmatien", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Alice", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_2.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Bambi", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_3.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Cendrillon", "F:\\ecole\\SAE\\SAE S2.01\\projet-avec-git-S2.01\\cartesDisney\\cartesDisney\\Disney_4.gif");
    _diaporama.push_back(imageACharger);

     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
     // A FAIRE
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
            qDebug() << "avant afficher image";

            //QString chemin = QString::fromStdString(_diaporama[_posImageCourante]->getChemin() );

            //cout <<_diaporama[_posImageCourante]->getChemin()<<endl;

            //ui->lImage->setPixmap(QPixmap(chemin));

            ui->lImage->setPixmap(QPixmap(QString::fromStdString(_diaporama[_posImageCourante]->getChemin() )));

            ui->lTitre->setText(QString::fromStdString(_diaporama[_posImageCourante]->getTitre() ));
            ui->lRang->setText(QString::number(_diaporama[_posImageCourante]->getRang()));

            std::string texte = "mode : " + std::to_string(static_cast<int>(etat));
            ui->bMode->setText(QString::fromStdString(texte));




            qDebug() << "apres afficher image";


            //ui->lImage->show();

            //QPixmap *pixmap_img = new QPixmap("dossier1/dossier2/img.jpg");



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

void lecteurVue::test()
{

    changerDiaporama(1);
    timer.start(1000);
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

void lecteurVue::truc()
{
    timer.start(1000);
    if (etat==automatique)
    {
        compteur++;
        if (compteur >= 2 )
        {
            compteur=0;
            avancer(0);
        }
        truc();
    }
}











