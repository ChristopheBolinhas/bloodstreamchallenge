#include "closebutton.h"
#include <QtWidgets>

CloseButton::CloseButton(QWidget *parent) :
    QPushButton(parent)
{
    closeImg = new QPixmap(":/hud/ressources/img/HUD_Icon/exit.png");
}

void CloseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,40,40,*closeImg);
}
