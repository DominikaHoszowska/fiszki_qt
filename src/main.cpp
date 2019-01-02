#include "frontend/mainwindow.h"
#include <QApplication>

#include <fiszki/Game.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Game game=Game();
    w.show();

    return a.exec();
}
