#include "chute.h"
#include "level.h"

Chute::Chute(int _x, int _y, int _orientation, QList<QPixmap*> *_images, Level *level) : Obstacle(_x,_y,_orientation)
{
}

Chute::~Chute()
{

}

void Chute::destroy()
{
    enabled = false;
}

void Chute::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    painter->fillRect(0,0,40,40,Qt::blue);

}
