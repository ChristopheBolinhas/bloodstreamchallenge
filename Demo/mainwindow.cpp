#include "mainwindow.h"

#include "gui.h"
#include "endgamescreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setFixedSize(960,540);
    gui = new Gui(this);
    setCentralWidget(gui);
    //gui
    /*endGameInfos = new EndGameInfos(this);
    setCentralWidget(endGameInfos);
    endGameInfos->show();*/
    /*EndGameScreen* endGame2 = new EndGameScreen(this);
    endGame2->setStyleSheet("background-color:red;");
    setCentralWidget(endGame2);*/
    /*QWidget* YOLO = new QWidget(this);
    setCentralWidget(YOLO);
    YOLO->setStyleSheet("background-color:red;");*/
}

MainWindow::~MainWindow()
{

}
