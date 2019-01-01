#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_menu_clicked();

    void on_menu_2_clicked();

    void on_addFC_B_clicked();

    void on_startLearning_B_clicked();

    void on_saveAll_B_clicked();

    void on_menu_3_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
