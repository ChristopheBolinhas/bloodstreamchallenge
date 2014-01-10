#include "caillot.h"
#include "level.h"

Caillot::Caillot(int _x, int _y, int _orientation, QList<QPixmap*> *_images, Level *level) : Obstacle(_x,_y,_orientation)
{

}

void Caillot::destroy()
{
    enabled = false;
}

void Caillot::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    painter->fillRect(0,0,40,40,Qt::red);

}


