#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    ui->lVertion->setText("vertion : 4.0");
    ui->lDateCration->setText("date de création : 18/05/2023");
    ui->lAuteur->setText("auteur : Juliard Timéo / Da Silva Hugo");
}

info::~info()
{
    delete ui;
}
