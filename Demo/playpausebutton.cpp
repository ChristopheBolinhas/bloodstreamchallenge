#include "playpausebutton.h"
#include <QtWidgets>


PlayPauseButton::PlayPauseButton(QWidget *parent) :
    QPushButton(parent)
{
    playImg = new QPixmap("://ressources/img/play.png");
    pauseImg = new QPixmap("://ressources/img/pause.png");

}

void PlayPauseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(play)
    {
        painter.drawPixmap(0,0,50,50,*pauseImg);
    }
    else
    {
        painter.drawPixmap(0,0,50,50,*playImg);
    }

}

void PlayPauseButton::mousePressEvent(QMouseEvent *e)
{
    play = play ? false : true;
    emit setPlayPause(play);
}
