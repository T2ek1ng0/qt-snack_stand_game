#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = nullptr);
    ~ImageDialog();
    void setContent(const QString &imagePath, const QString &text);

private:
    Ui::ImageDialog *ui;
    QLabel *m_imageLabel;
    QLabel *m_textLabel;
};

#endif // IMAGEDIALOG_H
