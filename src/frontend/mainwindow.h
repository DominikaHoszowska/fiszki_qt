#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<fiszki/Game.h>
#include<fiszki/Session.h>
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


 //learningMode:
    void on_menu_2_clicked();

    void on_plEngB_clicked();

    void on_engPlB_clicked();

    void selectCollectionToLearn();

    void on_addNewCollection_clicked();


 //collections:

    void on_menu_3_clicked();

    void on_addAllFC_clicked();


 //addNewCollection:

    void on_AddCollection_clicked();

    void on_menu_5_clicked();


//learnignCollection:


    void on_menu_4_clicked();

    void on_selectCollectionB_clicked();


    void on_menu_6_clicked();

    //learningPage:
    void startLearning();
    void showCard();

    void on_goodButton_clicked();

    void on_mediumButton_clicked();

    void on_badButton_clicked();
    void VisibleButtonsAndLabel(bool);


    void on_checkButton_clicked();

    void on_okGoToMenu_clicked();
    void summarise();
private:
    Ui::MainWindow *ui;
    std::unique_ptr<Game> game_;
    std::shared_ptr<Session> session_;
    std::shared_ptr<Card> actualCard_;

};
#endif // MAINWINDOW_H
