#include "mainwindow.h"
#include "gui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("Bloodstream Challenge");
    //Chargement de la fenêtre principal gérant le jeu
    gui = new Gui(this);
    setCentralWidget(gui);
    icon = new QIcon("://ressources/img/icon.png");
    setWindowIcon(*icon);
}

MainWindow::~MainWindow()
{

}
