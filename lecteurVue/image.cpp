#include "image.h"

Image::Image(unsigned int pRang, string pCategorie, string pTitre, string pChemin)
{
    _rang = pRang;
    _categorie = pCategorie;
    _titre = pTitre;
    _chemin = pChemin;
}

unsigned int Image::getRang()
{
    return _rang;
}

string Image::getCategorie()
{
    return _categorie;
}

string Image::getTitre()
{
    return _titre;
}

string Image::getChemin()
{
    return _chemin;
}

void Image::setRang(unsigned int pRang)
{
    _rang = pRang;
}

void Image::setCategorie(string pCategorie)
{
    _categorie = pCategorie;
}

void Image::setTitre(string pTitre)
{
    _titre = pTitre;
}

void Image::setChemin(string pChemin)
{
    _chemin = pChemin;
}

void Image::afficher()
{
    cout << "image( rang:" << getRang() << ", titre:" << getTitre() << ", categorie:"
         << getCategorie() << ", chemin:"<< getChemin() << ")" << endl;
}
