#include "lecteurvue.h"
#include <iostream>
#include "lecteurvue.h"
#include "image.h"

using namespace std;

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lecteurVue monLecteur;
    monLecteur.afficher();    /*
    monLecteur.afficher();

    cout << endl << "Test avancer() : 4 fois " << endl;
    // on avance 4 fois, pour vérifier que avancer() fonctionne correctement
    for (unsigned int i = 1 ; i <= 4; i++)
    {
        monLecteur.avancer();
        cout << "avancer() : " << endl;
        monLecteur.afficher();
    }

    cout << endl << "Test reculer() : 5 fois " << endl;
    // on recule 5 fois, pour vérifier que reculer() fonctionne correctement
    for (unsigned int i = 1 ; i <= 5; i++)
    {
        monLecteur.reculer();
        cout << "reculer() : " << endl;
        monLecteur.afficher();
    }

     // on enlève le diaporama du lecteur, et affichage du nouvel état du lecteur
      cout << endl << "Enlever le diaporama courant = Choisir diaporama 0" << endl;
        monLecteur.changerDiaporama(0);
        monLecteur.afficher();    
    //lecteurVue w; */
    monLecteur.show();
    //monLecteur.changerDiaporama(1);
    return a.exec();
}



