#include "deviation.h"
#include "level.h"


Deviation::Deviation(int _x, int _y, int _orientationPrimary,int _orientationSecondary, QList<QPixmap *> *_images, Level *level) : Obstacle(_x,_y, _orientationPrimary, _images, level)
{
    secondaryOrientation = _orientationSecondary;
    deviationTimer=new QTimer(this);
    connect(deviationTimer,SIGNAL(timeout()),this,SLOT(animation()));
    deviationTimer->setInterval(100);
    deviationTimer->start();
    anim = 0;
    setPos(_x*level->getTileWidth(),_y*level->getTileHeight());
}

void Deviation::animation()
{
    if(anim < 3)
    {
        anim++;
    }
    else
    {
        anim=0;
    }
}

void Deviation::switchPath(MapSquare *currentSquare)
{
    if(enabled)
    {
        currentSquare->activateDeviation();
        enabled = false;
    }
}


int Deviation::angleFromOrientation(int orientation)
{
    switch(orientation)
    {
        case 1:
            return -45;
        case 3:
            return 45;
        case 4:
            return -90;
        case 6:
            return 90;
        case 7:
            return -135;
        case 8:
            return 180;
        case 9:
            return 135;
        default:
            return 0;

    }
}

void Deviation::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(images != 0)
    {
        QPixmap *currentPixmap = images->at(anim);
        QTransform t;

        int oriUse;
        if(!enabled)
            oriUse = secondaryOrientation;
        else
            oriUse = orientation;
        if(etat == 0)
        {
            t.rotate(angleFromOrientation(oriUse));
        }
        else
        {
            t.rotate((angleFromOrientation(secondaryOrientation) - angleFromOrientation(orientation))/3*etat);
        }
        painter->drawPixmap(0,0,40,40, currentPixmap->transformed(t));
    }
    else
    {
        painter->fillRect(0,0,40,40,Qt::red);
    }
}


