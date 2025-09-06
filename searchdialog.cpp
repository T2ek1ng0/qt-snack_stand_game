#include "Searchdialog.h"
#include "ui_Searchdialog.h"

// Searchdialog.cpp
#include "Searchdialog.h"

SearchDialog::SearchDialog(const QStringList &data, QWidget *parent):QDialog(parent), m_allItems(data)
{
    setWindowTitle("删除菜品");
    QVBoxLayout *layout = new QVBoxLayout(this);
    // 创建输入框
    m_lineEdit = new QLineEdit(this);
    layout->addWidget(m_lineEdit);
    // 创建列表
    m_listWidget = new QListWidget(this);
    layout->addWidget(m_listWidget);
    // 连接信号槽
    connect(m_lineEdit, &QLineEdit::textChanged,this, &SearchDialog::filterItems);
    connect(m_listWidget, &QListWidget::itemDoubleClicked,this, &SearchDialog::onItemSelected);
    // 初始显示全部项目
    filterItems("");
    connect(m_lineEdit, &QLineEdit::returnPressed, [this]()
    {
        if(m_listWidget->count()>0) onItemSelected(m_listWidget->item(0));
    });
}

void SearchDialog::filterItems(const QString &text)
{
    m_listWidget->clear();
    for(const QString &item:m_allItems)
    {
        if(item.contains(text, Qt::CaseInsensitive)) m_listWidget->addItem(item);
    }
}

void SearchDialog::onItemSelected(QListWidgetItem *item)
{
    m_selectedItem = item->text();
    accept(); // 关闭对话框
}

QString SearchDialog::selectedItem() const
{
    return m_selectedItem;
}
SearchDialog::~SearchDialog()
{
    delete ui;
}
