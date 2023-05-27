#ifndef DEMANDEDIAPORAMA_H
#define DEMANDEDIAPORAMA_H

#include <QDialog>

namespace Ui {
class demandeDiaporama;
}

class demandeDiaporama : public QDialog
{
    Q_OBJECT

public:
    explicit demandeDiaporama(QWidget *parent = nullptr);
    ~demandeDiaporama();
    QString recupTexte();

private:
    Ui::demandeDiaporama *ui;
};

#endif // DEMANDEDIAPORAMA_H
