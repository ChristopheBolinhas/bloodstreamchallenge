#include "caillot.h"

Caillot::Caillot()
{

}

QRectF Caillot::boundingRect() const
{
    return QRectF (0,0,40, 40);
}
void Caillot::destroy()
{
    enabled = false;
}

void Caillot::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    painter->fillRect(0,0,40,40,Qt::red);

}


