#include "closebutton.h"
#include <QtWidgets>

CloseButton::CloseButton(QWidget *parent) :
    QPushButton(parent)
{

}

void CloseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap closeImg(":/hud/ressources/img/HUD_Icon/exit.png");
    painter.drawPixmap(0,0,40,40,closeImg);
}
