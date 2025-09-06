#include "foodtotal.h"
#include "ui_foodtotal.h"

foodtotal::foodtotal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::foodtotal)
{
    ui->setupUi(this);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    ui->scrollArea->setGeometry(ui->flabel->geometry());
    ui->flabel->setParent(ui->scrollArea->viewport());
    ui->scrollArea->setWidget(ui->flabel);
    ui->scrollArea->setWidgetResizable(true); // 允许内容自适应
}

foodtotal::~foodtotal()
{
    delete ui;
}
