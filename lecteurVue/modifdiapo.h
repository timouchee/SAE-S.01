#ifndef MODIFDIAPO_H
#define MODIFDIAPO_H

#include <QDialog>
using namespace std;

namespace Ui {
class modifDiapo;
}

class modifDiapo : public QDialog
{
    Q_OBJECT

public:
    explicit modifDiapo(QWidget *parent = nullptr);
    ~modifDiapo();
    void setRang(QString);
    void setTitre(QString);
    void setCategorie(QString);
    void setChemin(QString);

    QString getRang();
    QString getTitre();
    QString getCategorie();
    QString getChemin();


private:
    Ui::modifDiapo *ui;
};

#endif // MODIFDIAPO_H
