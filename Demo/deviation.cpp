#include "deviation.h"
#include "level.h"

Deviation::Deviation(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level) : Obstacle(_x,_y,_orientation)
{

}


void Deviation::switchPath(MapSquare *currentSquare)
{
    if(enabled)
        currentSquare->activateDeviation();
}

void Deviation::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    painter->fillRect(0,0,40,40,Qt::red);

}
