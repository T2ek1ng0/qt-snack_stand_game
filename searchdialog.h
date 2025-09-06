#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(const QStringList &data, QWidget *parent = nullptr);
    QString selectedItem() const;
    ~SearchDialog();

private slots:
    void filterItems(const QString &text);
    void onItemSelected(QListWidgetItem *item);

private:
    Ui::SearchDialog *ui;
    QLineEdit *m_lineEdit;
    QListWidget *m_listWidget;
    QString m_selectedItem;
    QStringList m_allItems;
};

#endif // SEARCHDIALOG_H
