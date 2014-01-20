#include "mainwindow.h"
#include "gui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gui = new Gui(this);
    setCentralWidget(gui);
}

MainWindow::~MainWindow()
{

}
