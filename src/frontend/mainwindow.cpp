#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"fiszki/Game.h"
#include <string>
#include <QMessageBox>
#include<QIcon>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game_=std::make_unique<Game>();
    session_=nullptr;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    sqlite3* db;
    sqlite3_open("baza.db",&db);
    game_->setDb_(db);
    setlocale( LC_ALL, "polish" );

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
    if(!game_->ifCardsToAddIsEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Czy na pewno chcesz wrócić do menu?");
        msgBox.setInformativeText(" Zostaną utracone wszystkie niezapisane zmiany");
        QAbstractButton *myYesButton=msgBox.addButton("Tak",QMessageBox::YesRole);
        msgBox.addButton("Nie",QMessageBox::NoRole);
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

        msgBox.exec();
        if(msgBox.clickedButton()==myYesButton)
        {
            game_->clearCardsToAdd();
            ui->polishI->clear();
            ui->englishI->clear();
            ui->stackedWidget->setCurrentIndex(0);

        }
    }
    else{
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_saveAll_B_clicked()
{

    std::string pl=ui->polishI->text().toStdString();
    std::string eng=ui->englishI->text().toStdString();
    if(pl.empty()||eng.empty())
    {
        if(game_->ifCardsToAddIsEmpty()){
            QMessageBox::information(this,tr("Błąd"),tr("Brak kart do dodania"));
            ui->stackedWidget->setCurrentIndex(0);
        }
        else{
            ui->stackedWidget->setCurrentIndex(3);
            std::vector<std::string> collections=this->game_->getCollections();

            for(auto& str : collections)
            {
                ui->listWidget->addItem(QString::fromStdString(str));
            }

        }
    }
    else{
        if(Card::checkCorrectnessW(pl)&&Card::checkCorrectnessW(eng))
        {
            this->game_->addCard(pl,eng);
            ui->polishI->clear();
            ui->englishI->clear();
            ui->stackedWidget->setCurrentIndex(3);
            std::vector<std::string> collections=this->game_->getCollections();

            for(auto& str : collections)
            {
                ui->listWidget->addItem(QString::fromStdString(str));
            }
        }
        else
        {
            QMessageBox::information(this,tr("Błąd"),tr("Wprowadź poprawne dane"));
        }


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
    selectCollectionToLearn();
}

void MainWindow::on_engPlB_clicked()
{
    this->game_->setLanguage(Game::Language::ENG_PL);
    selectCollectionToLearn();
}
void MainWindow::selectCollectionToLearn()
{
    ui->stackedWidget->setCurrentIndex(5);

    std::vector<std::string> collections=this->game_->getCollections();

    for(auto& str : collections)
    {
        ui->selectCollectionList->addItem(QString::fromStdString(str));
    }


}

//collections:

void MainWindow::on_menu_3_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("Czy na pewno chcesz wrócić do menu? ");
    msgBox.setInformativeText("Zostaną utracone wszystkie niezapisane zmiany");
    QAbstractButton *myYesButton=msgBox.addButton("Tak",QMessageBox::YesRole);
    msgBox.addButton("Nie",QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    msgBox.exec();
    if(msgBox.clickedButton()==myYesButton)
    {
        game_->clearCardsToAdd();
        ui->listWidget->clear();
        ui->stackedWidget->setCurrentIndex(0);

    }


}

void MainWindow::on_addAllFC_clicked()
{
    auto* i = ui->listWidget->currentItem();
    if(i)
    {
        game_->addCardsToCollection(i->text().toStdString());
        ui->listWidget->clear();
        ui->stackedWidget->setCurrentIndex(0);

    }
    else{
        QMessageBox::information(this,tr("Błąd"),tr("Wybierz kolekcję"));

    }

}
void MainWindow::on_addNewCollection_clicked()
{
    ui->listWidget->clear();
    ui->stackedWidget->setCurrentIndex(4);

}
//addNewCollection:

void MainWindow::on_AddCollection_clicked()
{
    std::string c=ui->newCollectionName->text().toStdString();
    if(Collection::checkCorrectnessC(c))
    {
        if(game_->ifCollectionNameUnique(c)){
            this->game_->addCollection(c);
            ui->stackedWidget->setCurrentIndex(3);
            ui->listWidget->clear();
            std::vector<std::string> collections=this->game_->getCollections();

            for(auto& str : collections)
            {
                ui->listWidget->addItem(QString::fromStdString(str));
            }
        }
        else{
            QMessageBox::information(this,tr("Błąd"),tr("Nazwa kolekcji musi być unikalna"));

        }
    }
    else
    {
        QMessageBox::information(this,tr("Błąd"),tr("Wprowadź poprawne dane"));
    }


}

void MainWindow::on_menu_5_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Czy na pewno chcesz wrócić do menu? ");
    msgBox.setInformativeText("Zostaną utracone wszystkie niezapisane zmiany");
    QAbstractButton *myYesButton=msgBox.addButton("Tak",QMessageBox::YesRole);
    msgBox.addButton("Nie",QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    msgBox.exec();
    if(msgBox.clickedButton()==myYesButton)
    {
        game_->clearCardsToAdd();
        ui->listWidget->clear();
        ui->stackedWidget->setCurrentIndex(0);
    }
}


//learnignCollection:

void MainWindow::on_menu_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_selectCollectionB_clicked()
{
    auto* i = ui->selectCollectionList->currentItem();
    if(i)
    {

        ui->listWidget->clear();
        ui->stackedWidget->setCurrentIndex(6);
        std::string c=i->text().toStdString();
        session_=std::make_shared<Session>(game_->getCollection(c));
        startLearning();
    }
    else{
        QMessageBox::information(this,tr("Błąd"),tr("Wybierz kolekcję"));

    }

}
//learningPage:
void MainWindow::on_menu_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::startLearning()
{

    QPixmap ok("OK.png");
    QIcon ButtonIcon(ok);
    ui->goodButton->setIcon(ButtonIcon);
    ui->goodButton->setIconSize(ok.rect().size());
    QPixmap bad("BAD.png");
    QIcon ButtonIconBad(bad);
    ui->badButton->setIcon(ButtonIconBad);
    ui->badButton->setIconSize(bad.rect().size());
    QPixmap medium("medium.png");
    QIcon ButtonIconM(medium);
    ui->mediumButton->setIcon(ButtonIconM);
    ui->mediumButton->setIconSize(medium.rect().size());
    std::shared_ptr<Card> c;
    c=session_->giveNextCard();
        showCard(c);



}
void MainWindow::showCard(std::shared_ptr<Card> c)
{
    if(game_->getLanguage_()==Game::Language::PL_ENG)
    {
        ui->QuestionLabel->setText(QString::fromStdString(c->getPl_()));
    }
}
