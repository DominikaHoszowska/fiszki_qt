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

    void on_addFCButton_clicked();

    void on_startLearningButton_clicked();

//addFCC:
    void on_addFCSaveAllFCButton_clicked();

    void on_menuButton_clicked();

    void on_addNextFCButton_clicked();


 //learningMode:
    void on_menu2Button_clicked();

    void on_plEngButton_clicked();

    void on_engPlButton_clicked();

    void selectCollectionToLearn();

    void on_addNewCollectionButton_clicked();


 //collections:

    void on_menu3Button_clicked();

    void on_addAllFCButton_clicked();


 //addNewCollection:

    void on_AddCollection_clicked();

    void on_menu5Button_clicked();


//learnignCollection:


    void on_menu4Button_clicked();

    void on_learningSelectCollectionButton_clicked();


    void on_menu6Button_clicked();

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
    std::shared_ptr<CardSession> actualCard_;

};
#endif // MAINWINDOW_H
