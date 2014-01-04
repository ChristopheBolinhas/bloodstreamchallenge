#include "closebutton.h"
#include <QtWidgets>

CloseButton::CloseButton(QWidget *parent) :
    QPushButton(parent)
{

}

void CloseButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap closeImg("://ressources/img/close.png");
    painter.drawPixmap(0,0,50,50,closeImg);
}
