#include "mainwindow.h"
#include "gui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setFixedSize(960,540);
    gui = new Gui(this);
    setCentralWidget(gui);

}

MainWindow::~MainWindow()
{

}
