#include "playpausebutton.h"
#include <QtWidgets>


PlayPauseButton::PlayPauseButton(QWidget *parent) :
    QPushButton(parent)
{
    playImg = new QPixmap(":/hud/ressources/img/HUD_Icon/start.png");
    pauseImg = new QPixmap(":/hud/ressources/img/HUD_Icon/pause.png");

}

void PlayPauseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(play)
    {
        painter.drawPixmap(0,0,40,40,*pauseImg);
    }
    else
    {
        painter.drawPixmap(0,0,40,40,*playImg);
    }

}

void PlayPauseButton::mousePressEvent(QMouseEvent *e)
{
    play = play ? false : true;
    emit setPlayPause(play);
}
