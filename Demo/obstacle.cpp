#include "obstacle.h"
#include "level.h"
#include <QtGui>

Obstacle::Obstacle(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level)
{
    enabled = true;
    orientation = _orientation;
    images = _images;
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
    timerAnim = new QTimer(this);
    timerAnim->setInterval(200);
    connect(timerAnim, SIGNAL(timeout()),this,SLOT(disableAnim()));
    setPos(x*level->getTileWidth(),y*level->getTileHeight());
    setZValue(3);

}


Obstacle::~Obstacle()
{
    timerAnim->stop();
    delete(timerAnim);
}


bool Obstacle::isEnabled()
{
    return enabled;
}

void Obstacle::disable()
{
    timerAnim->start();
    enabled = false;

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
    if(images != 0)
    {
        QTransform t;
        t.rotate(180);
        if(orientation == 8)
        {
            QPixmap *currentPixmap = images->at(etat);
            painter->drawPixmap(0,0,width,height, *currentPixmap);
        }
        else if(orientation == 2)
        {
            QPixmap *currentPixmap = images->at(etat);
            painter->drawPixmap(0,0,width,height, currentPixmap->transformed(t));
        }
        else if(orientation == 4)
        {
            QPixmap *currentPixmap = images->at(etat+4);
            painter->drawPixmap(0,-5,width,height, currentPixmap->transformed(t));
        }
        else if(orientation == 6)
        {
            QPixmap *currentPixmap = images->at(etat+4);
            painter->drawPixmap(0,0,width,height, *currentPixmap);
        }
    }
    else
    {
        painter->fillRect(0,0,40,40,Qt::red);
    }

}

void Obstacle::disableAnim()
{
    if(enabled)
    {
        etat = 0;
    }
    else
    {
        if(etat < 3) etat++;
        update(this->boundingRect());
        if(etat >= 3) timerAnim->stop();

    }
}



