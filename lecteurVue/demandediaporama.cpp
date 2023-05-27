#include "demandediaporama.h"
#include "ui_demandediaporama.h"

demandeDiaporama::demandeDiaporama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::demandeDiaporama)
{
    ui->setupUi(this);
}

demandeDiaporama::~demandeDiaporama()
{
    delete ui;
}

QString demandeDiaporama::recupTexte()
{
    return ui->eDiapoAPrendre->text();
}
