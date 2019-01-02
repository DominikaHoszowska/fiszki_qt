#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"fiszki/Game.h"
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

}

void MainWindow::on_addNext_B_clicked()
{

}

 //startLearning:

void MainWindow::on_menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


  //collections:

void MainWindow::on_menu_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
