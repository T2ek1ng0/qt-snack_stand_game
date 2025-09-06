#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent):QDialog(parent),ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    setWindowTitle("传记详情");
}
void ImageDialog::setContent(const QString &imagePath, const QString &text)
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    ui->scrollArea->setGeometry(ui->mainlabel->geometry());
    ui->mainlabel->setParent(ui->scrollArea->viewport());
    ui->scrollArea->setWidget(ui->mainlabel);
    ui->scrollArea->setWidgetResizable(true); // 允许内容自适应
    QImage img;
    img.load(imagePath);
    ui->mypic->setPixmap(QPixmap::fromImage(img));
    ui->mainlabel->setText(text);
}

ImageDialog::~ImageDialog()
{
    delete ui;
}
