#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Gui;
class EndGameInfos;
class EndGameScreen;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Gui *gui;
    EndGameInfos *endGameInfos;
    EndGameScreen *endGame;
};

#endif // MAINWINDOW_H
