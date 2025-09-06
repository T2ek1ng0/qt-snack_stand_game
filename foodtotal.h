#ifndef FOODTOTAL_H
#define FOODTOTAL_H

#include <QDialog>

namespace Ui {
class foodtotal;
}

class foodtotal : public QDialog
{
    Q_OBJECT

public:
    explicit foodtotal(QWidget *parent = 0);
    ~foodtotal();

private:
    Ui::foodtotal *ui;
};

#endif // FOODTOTAL_H
