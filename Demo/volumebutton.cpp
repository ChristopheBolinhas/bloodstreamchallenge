#include "volumebutton.h"
#include <QtWidgets>

VolumeButton::VolumeButton(QWidget *parent) :
    QPushButton(parent)
{
    muteImg = new QPixmap(":/hud/ressources/img/HUD_Icon/volume_off.png");
    unmuteImg = new QPixmap(":/hud/ressources/img/HUD_Icon/volume_on.png");
    setMode(true);
}

void VolumeButton::setMode(bool _sound)
{
    sound = _sound;
}

void VolumeButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(sound)
    {
        painter.drawPixmap(0,0,40,40,*muteImg);

    }
    else
    {
        painter.drawPixmap(0,0,40,40,*unmuteImg);
    }

}

void VolumeButton::mousePressEvent(QMouseEvent *e)
{
    sound = sound ? false : true;
    emit setSound(sound);
}
