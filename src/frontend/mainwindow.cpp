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
    int src;
    sqlite3* db;
    src=sqlite3_open("baza.db",&db);
    game_->setDb_(db);
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

    std::string pl=ui->polishI->text().toStdString();
    std::string eng=ui->englishI->text().toStdString();
    if(Card::checkCorrectnessW(pl)&&Card::checkCorrectnessW(eng))
    {
        this->game_->addCard(pl,eng);
    }

    ui->stackedWidget->setCurrentIndex(3);
    std::vector<std::pair<int,std::string>> collections=this->game_->getCollections();

    for(std::vector<std::pair<int,std::string>>::iterator i=collections.begin();i!=collections.end();++i)
    {
        ui->listWidget->addItem(QString::fromStdString(i->second));
    }

}

void MainWindow::on_addNext_B_clicked()
{
    std::string pl=ui->polishI->text().toStdString();
    std::string eng=ui->englishI->text().toStdString();
    if(Card::checkCorrectnessW(pl)&&Card::checkCorrectnessW(eng))
    {
        this->game_->addCard(pl,eng);
        ui->polishI->clear();
        ui->englishI->clear();
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        QMessageBox::information(this,tr("Błąd"),tr("Wprowadź poprawne dane"));
    }



}

 //learningMode:

void MainWindow::on_menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_plEngB_clicked()
{
    this->game_->setLanguage(Game::Language::PL_ENG);
    ui->stackedWidget->setCurrentIndex(5);

}

void MainWindow::on_engPlB_clicked()
{
    this->game_->setLanguage(Game::Language::ENG_PL);
    ui->stackedWidget->setCurrentIndex(5);

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
void MainWindow::on_addNewCollection_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

}

//learnignCollection:

void MainWindow::on_menu_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_AddCollection_clicked()
{
    std::string c=ui->newCollectionName->text().toStdString();
    if(Card::checkCorrectnessW(c))
    {
        this->game_->addCollection(c);
    }
    ui->stackedWidget->setCurrentIndex(3);
    ui->listWidget->clear();
    std::vector<std::pair<int,std::string>> collections=this->game_->getCollections();

    for(std::vector<std::pair<int,std::string>>::iterator i=collections.begin();i!=collections.end();++i)
    {
        ui->listWidget->addItem(QString::fromStdString(i->second));
    }
}
