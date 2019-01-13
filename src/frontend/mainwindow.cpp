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


void MainWindow::on_addFCButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_startLearningButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}
//addFCC:

void MainWindow::on_menuButton_clicked()
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
            ui->polishInputLine->clear();
            ui->englishInputLine->clear();
            ui->stackedWidget->setCurrentIndex(0);

        }
    }
    else{
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::on_addFCSaveAllFCButton_clicked()
{

    std::string pl=ui->polishInputLine->text().toStdString();
    std::string eng=ui->englishInputLine->text().toStdString();
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
            ui->polishInputLine->clear();
            ui->englishInputLine->clear();
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

void MainWindow::on_addNextFCButton_clicked()
{
    std::string pl=ui->polishInputLine->text().toStdString();
    std::string eng=ui->englishInputLine->text().toStdString();
    if(Card::checkCorrectnessW(pl)&&Card::checkCorrectnessW(eng))
    {
        this->game_->addCard(pl,eng);
        ui->polishInputLine->clear();
        ui->englishInputLine->clear();
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        QMessageBox::information(this,tr("Błąd"),tr("Wprowadź poprawne dane"));
    }



}

 //learningMode:

void MainWindow::on_menu2Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_plEngButton_clicked()
{
    this->game_->setLanguage(Game::Language::PL_ENG);
    selectCollectionToLearn();
}

void MainWindow::on_engPlButton_clicked()
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

void MainWindow::on_menu3Button_clicked()
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

void MainWindow::on_addAllFCButton_clicked()
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
void MainWindow::on_addNewCollectionButton_clicked()
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

void MainWindow::on_menu5Button_clicked()
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

void MainWindow::on_menu4Button_clicked()
{
       ui->selectCollectionList->clear();
     ui->stackedWidget->setCurrentIndex(0);
}



void MainWindow::on_learningSelectCollectionButton_clicked()
{
    auto* i = ui->selectCollectionList->currentItem();
    if(i)
    {
        std::string c=i->text().toStdString();
        session_=std::make_shared<Session>(game_->getCollection(c));
        if(!session_->getNumberOfCards())
        {
            QMessageBox::information(this,tr("Gratulacje!"),tr("Umiesz już wszystkie karty z tej kolekcji"));
            ui->stackedWidget->setCurrentIndex(0);

        }
        else{
        ui->stackedWidget->setCurrentIndex(6);

        startLearning();
        }

    }
    else{
        QMessageBox::information(this,tr("Błąd"),tr("Wybierz kolekcję"));

    }

}
//learningPage:
void MainWindow::on_menu6Button_clicked()
{
    summarise();
}
void MainWindow:: VisibleButtonsAndLabel(bool b)
{
    ui->goodButton->setVisible(b);
    ui->mediumButton->setVisible(b);
    ui->badButton->setVisible(b);
    ui->goodLabel->setVisible(b);
    ui->mediumLabel->setVisible(b);
    ui->badLebel->setVisible(b);

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
    showCard();




}
void MainWindow::showCard()
{
    actualCard_=session_->giveNextCard();
    if(actualCard_!=nullptr)
    {
        VisibleButtonsAndLabel(false);
        ui->checkButton->setVisible(true);
        if(game_->getLanguage_()==Game::Language::PL_ENG)
        {
            ui->QuestionLabel->setText(QString::fromStdString(actualCard_->getCard_()->getPl_()));

        }
        else
        {
            ui->QuestionLabel->setText(QString::fromStdString(actualCard_->getCard_()->getEng_()));

        }
        ui->AnswerLabel->setText(QString::fromStdString(""));

    }
    else
    {
        summarise();
    }
}
void MainWindow::on_checkButton_clicked()
{
    if(game_->getLanguage_()==Game::Language::PL_ENG)
    {
        ui->AnswerLabel->setText(QString::fromStdString(actualCard_->getCard_()->getEng_()));
    }
    else
    {
        ui->AnswerLabel->setText(QString::fromStdString(actualCard_->getCard_()->getPl_()));

    }
    ui->checkButton->setVisible(false);
    VisibleButtonsAndLabel(true);
}
void MainWindow::on_goodButton_clicked()
{
    session_->takeAnswer(actualCard_,Session::Answer::GOOD);
    showCard();
}

void MainWindow::on_mediumButton_clicked()
{
    session_->takeAnswer(actualCard_,Session::Answer::MEDIUM);
    showCard();

}

void MainWindow::on_badButton_clicked()
{
    session_->takeAnswer(actualCard_,Session::Answer::BAD);
    showCard();

}

void MainWindow:: summarise(){
    ui->stackedWidget->setCurrentIndex(7);
    ui->allCardsNumber->setText(QString::fromStdString(std::to_string(session_->getAllAnswers())));
    ui->goodCardsNumber->setText(QString::fromStdString(std::to_string(session_->getGood_())));
    ui->badCardsNumber->setText(QString::fromStdString(std::to_string(session_->getBad_())));
    ui->mediumCardsNumber->setText(QString::fromStdString(std::to_string(session_->getMedium_())));

}


void MainWindow::on_okGoToMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}



