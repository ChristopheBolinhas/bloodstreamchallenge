#include "obstacle.h"
#include <QtGui>

Obstacle::Obstacle(int _x, int _y, int _orientation)
{
    enabled = true;
    orientation = _orientation;
    switch(_orientation)
    {


        case 1:
        case 9:
            rotation = 2;
        case 3:
        case 7:
            rotation++;
            x = _x-1;
            y = _y-1;
            width = 120;
            height = 120;
            rotation = 1;

            break;
        case 2:
        case 8:
            x = _x-1;
            y = _y;
            height = 40;
            width = 120;
            break;
        case 4:
        case 6:
            x = _x;
            y = _y-1;
            height = 120;
            width = 40;
            break;
    }
}

bool Obstacle::isEnabled()
{
    return enabled;
}

Obstacle::~Obstacle()
{

}

int Obstacle::getOrientation()
{
    return orientation;
}

QRectF Obstacle::boundingRect() const
{
    return QRectF (0,0, width, height);
}


void Obstacle::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    //QPixmap *currentPixmap = images->at(etat);

    //painter->rotate(45*Obstacle::rotation);
    //currentPixmap->transformed(t);
    //painter->drawPixmap(0,0,width,height, *currentPixmap);
    painter->fillRect(0,0,40,40,Qt::red);

}



