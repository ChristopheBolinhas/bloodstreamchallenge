#include "chute.h"

Chute::Chute()
{
}

QRectF Chute::boundingRect() const
{
    return QRectF (0,0,40, 40);
}
void Chute::destroy()
{
    enabled = false;
}

void Chute::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    painter->fillRect(0,0,40,40,Qt::blue);

}
