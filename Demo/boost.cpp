#include "boost.h"

Boost::Boost()
{
}

QRectF Boost::boundingRect() const
{
    return QRectF (0,0,40, 40);
}


void Boost::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    painter->fillRect(0,0,40,40,Qt::yellow);

}
