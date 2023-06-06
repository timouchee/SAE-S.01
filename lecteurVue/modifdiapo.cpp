#include "modifdiapo.h"
#include "ui_modifdiapo.h"

modifDiapo::modifDiapo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifDiapo)
{
    ui->setupUi(this);
}

modifDiapo::~modifDiapo()
{
    delete ui;
}

void modifDiapo::setRang(QString rang)
{
    ui->eRang->setText(rang);
}

void modifDiapo::setTitre(QString titre)
{
    ui->eTitre->setText(titre);
}

void modifDiapo::setCategorie(QString categorie)
{
    ui->eCategorie->setText(categorie);
}

void modifDiapo::setChemin(QString chemin)
{
    ui->eChemin->setText(chemin);
}

QString modifDiapo::getRang()
{
    return ui->eRang->text();
}

QString modifDiapo::getTitre()
{
    return ui->eTitre->text();
}

QString modifDiapo::getCategorie()
{
    return ui->eCategorie->text();
}

QString modifDiapo::getChemin()
{
    return ui->eChemin->text();
}
