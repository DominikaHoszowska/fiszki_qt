#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"fiszki/Game.h"
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game_=std::make_unique<Game>();
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//menu:


void MainWindow::on_addFC_B_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_startLearning_B_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}
//addFCC:

void MainWindow::on_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_saveAll_B_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    //TODO
}

void MainWindow::on_addNext_B_clicked()
{

    if(Card::checkCorrectnessW(ui->polishI->text().toStdString())&&Card::checkCorrectnessW(ui->englishI->text().toStdString()))
    {
    }
    else
    {
        QMessageBox::information(this,tr("Błąd"),tr("Wprowadź poprawne dane"));
    }
    //TODO
    ui->polishI->clear();
    ui->englishI->clear();
    ui->stackedWidget->setCurrentIndex(1);

}

 //learningMode:

void MainWindow::on_menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_plEngB_clicked()
{
    this->game_->setLanguage(Game::Language::PL_ENG);
    ui->stackedWidget->setCurrentIndex(4);

}

void MainWindow::on_engPlB_clicked()
{
    this->game_->setLanguage(Game::Language::ENG_PL);
    ui->stackedWidget->setCurrentIndex(4);

}

//collections:

void MainWindow::on_menu_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_addAllFC_clicked()
{
    //TODO
}
//learnignCollection:

void MainWindow::on_menu_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


