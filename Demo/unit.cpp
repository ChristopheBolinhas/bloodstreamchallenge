#include "unit.h"
#include <QPropertyAnimation>
#include <QDebug>

Unit::Unit(QList<QPixmap *> *_pixmapList, MapSquare *path, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{

    //from Level
    int tile_width = 40;
    int tile_height = 40;
    pixmapList = _pixmapList;



    currentSquare = path;
    setPos(path->getX()*40, path->getY()*40);
    setZValue(3);
    animation = new QPropertyAnimation(this,"pos",this);
    calcultateNextMove();

    //EN DUR
    capaciteUnit = EnumObstacle::deviation;//Perma activation de la deviation
}

Unit::~Unit()
{

}

QRectF Unit::boundingRect() const
{
    return QRectF (0,0,40, 40);
}

void Unit::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{

    painter->drawPixmap(0,0,40,40,*pixmapList->first());
}


void Unit::calcultateNextMove()
{
    xmove = (currentSquare->getNext()->getX() - currentSquare->getX())*4;
    ymove = (currentSquare->getNext()->getY() - currentSquare->getY())*4;
}


void Unit::advance(int phase)
{

    if(currentSquare->getNext() != 0)
    {

        if(animation->state() == QPropertyAnimation::Stopped)
        {



            animation->setDuration(200);
            animation->setStartValue(QPoint(currentSquare->getX()*40,currentSquare->getY()*40));
            animation->setEndValue(QPoint(currentSquare->getNext()->getX()*40,currentSquare->getNext()->getY()*40));
            //animation->setEasingCurve(QEasingCurve::InBack);

            animation->start();
            currentSquare = currentSquare->getNext();
        }
    }
}


void Unit::unlockObstacle()
{
    switch(capaciteUnit)
    {
        case EnumObstacle::deviation:
            currentSquare->getNext()->removePrimary();
            break;

    }
}



void Unit::moveUnit()
{
    /*int xmove;
    int ymove;
*/
    if(currentSquare->getNext() != 0)
    {
        if(x() == currentSquare->getNext()->getX()*40 && y() == currentSquare->getNext()->getY()*40)
        {
            //On test que le prochain n'ai pas d'obstacle
            if(currentSquare->getNext()->hasObstacle())
            {



            }
            currentSquare = currentSquare->getNext();
            //Implémentation obstacles avec currentSquare
            //TODO
            calcultateNextMove();
        }





        moveBy(xmove,ymove);
    }
}
