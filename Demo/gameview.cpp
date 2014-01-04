#include "gameview.h"
#include <QtGui>
#include <QtWidgets>
#include "abilitybutton.h"
#include "volumebutton.h"
#include "playpausebutton.h"
#include "closebutton.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    //QGridLayout *grid = new QGridLayout(this);
    //QRect geo(240,410,480,130);
    //grid->setGeometry(geo);
    abi1 = new AbilityButton(1,this);
    abi1->setGeometry(240,410,180,130);
    abi1->hide();

    playButton = new PlayPauseButton(this);
    playButton->setGeometry(810,0,50,50);
    playButton->hide();

    volume = new VolumeButton(this);
    volume->setGeometry(860,0,50,50);
    volume->hide();

    closeButton = new CloseButton(this);
    closeButton->setGeometry(910,0,50,50);
    closeButton->hide();

    connect(closeButton, SIGNAL(clicked()),this,SIGNAL(closeRender()));
    connect(abi1,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    //grid->addWidget(abi1,0,0);
}

void GameView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());

    //painter.drawText(300,300,"yolo");
}

void GameView::update()
{
    QGraphicsView::update();
}

//Mode de la vue, permet d'afficher/masquer les bouttons du hud
void GameView::setMode(int mode)
{
    switch(mode)
    {
    case 0:
        abi1->hide();
        volume->hide();
        playButton->hide();
        closeButton->hide();
        break;
    case 1:
        abi1->show();
        volume->show();
        playButton->show();
        closeButton->show();
        break;
    }
}
