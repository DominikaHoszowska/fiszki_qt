#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<fiszki/Game.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//MENU:

    void on_addFC_B_clicked();

    void on_startLearning_B_clicked();



    void on_menu_clicked();

    void on_menu_2_clicked();


    void on_saveAll_B_clicked();

    void on_menu_3_clicked();


    void on_addNext_B_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Game> game_;
};

#endif // MAINWINDOW_H
