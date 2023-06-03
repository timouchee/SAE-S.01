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
    monLecteur.afficher();


    monLecteur.show();

    return a.exec();
}



