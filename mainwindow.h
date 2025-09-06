#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<windows.h>
#include <chrono>
#include<locale>
#include <QThread>
#include<QAction>
#include<QKeyEvent>
#include<QFile>
#include<QString>
#include <QDebug>
#include <QScrollArea>
#include <QMessageBox>
#include<QTimer>
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>
#include <QListView>
#include <QInputDialog>
#include<QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void spaceKeyPressed();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

signals:
    void rightClick();

public:
    QStringList senddata;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_enter1_clicked();

    void on_nextpage1_clicked();

    void on_nextpage2_clicked();

    void on_nextpage3_clicked();

    void on_nextpage4_clicked();

    void on_easy_clicked();

    void on_normal_clicked();

    void on_hard_clicked();

    void on_start_clicked();

    void on_diceyes_clicked();

    void on_diceno_clicked();

    void on_startday_clicked();

    void on_infobutton_clicked();

    void saveAchievementsToFile();

    void loadAchievementsFromFile();

    void infoactionslot();

    void openachievement();

    void lookguest();

    void lookfood1();

    void lookfood2();

    void lookreview();

    void lookpolice();

    void jiangestory();

    void lipustory();

    void lihuastory();

    void lao8story();

    void ladygabastory();

    void handleRestock(int foodIndex, QTableWidget* table);

    void handleExpired(int foodIndex, QTableWidget* table);

    void pauseaction();


    void on_nextpage0_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
