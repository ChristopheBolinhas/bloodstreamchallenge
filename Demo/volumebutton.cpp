#include "volumebutton.h"
#include <QtWidgets>

VolumeButton::VolumeButton(QWidget *parent) :
    QPushButton(parent)
{
    setGeometry(0,0,50,50);
    muteImg = new QPixmap("://ressources/img/volumemute.png");
    unmuteImg = new QPixmap("://ressources/img/volumeunmute.png");
}

void VolumeButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(sound)
    {
        painter.drawPixmap(0,0,50,50,*muteImg);

    }
    else
    {
        painter.drawPixmap(0,0,50,50,*unmuteImg);
    }

}

void VolumeButton::mousePressEvent(QMouseEvent *e)
{
    sound = sound ? false : true;
    emit setSound(sound);
}
