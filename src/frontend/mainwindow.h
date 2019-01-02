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
//menu:

    void on_addFC_B_clicked();

    void on_startLearning_B_clicked();

//addFCC:
    void on_saveAll_B_clicked();
    void on_menu_clicked();
    void on_addNext_B_clicked();


 //startLearning:

    void on_menu_2_clicked();


  //collections:

    void on_menu_3_clicked();


private:
    Ui::MainWindow *ui;
    std::unique_ptr<Game> game_;
};

#endif // MAINWINDOW_H
