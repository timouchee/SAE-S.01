#include "modif_diaporama.h"
#include "ui_modif_diaporama.h"

modif_diaporama::modif_diaporama(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modif_diaporama)
{
    ui->setupUi(this);
}

modif_diaporama::~modif_diaporama()
{
    delete ui;
}
