#ifndef MODIF_DIAPORAMA_H
#define MODIF_DIAPORAMA_H

#include <QDialog>

namespace Ui {
class modif_diaporama;
}

class modif_diaporama : public QDialog
{
    Q_OBJECT

public:
    explicit modif_diaporama(QWidget *parent = nullptr);
    ~modif_diaporama();

private:
    Ui::modif_diaporama *ui;
};

#endif // MODIF_DIAPORAMA_H
