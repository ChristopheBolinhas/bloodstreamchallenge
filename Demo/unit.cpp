#include "unit.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <deviation.h>
#include <obstacle.h>
#include <caillot.h>
#include <typeinfo>

Unit::Unit(QList<QPixmap *> *_pixmapList, MapSquare *path, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{

    //from Level
    int tile_width = 40;
    int tile_height = 40;
    pixmapList = _pixmapList;


    qDebug() << "Constructing unit";
    currentSquare = path;
    qDebug() << "Path defined, next ? : " << currentSquare->getHasNext();

    setPos(path->getX()*40, path->getY()*40);
    setZValue(3);
    animation = new QPropertyAnimation(this,"pos",this);
    calcultateNextMove();

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
    if(isAlive)
        painter->drawPixmap(0,0,40,40,*pixmapList->first());
}


void Unit::calcultateNextMove()
{
    if(currentSquare->getHasNext())
    {
        xmove = (currentSquare->getNext()->getX() - currentSquare->getX())*4;
        ymove = (currentSquare->getNext()->getY() - currentSquare->getY())*4;

    }
}



//non utilise
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
    /*switch(capaciteUnit)
    {
        case EnumObstacle::deviation:
            currentSquare->getNext()->removePrimary();
            break;

    }*/
}
int Unit::getAbility() const
{
    return ability;
}

void Unit::setAbility(int value)
{
    ability = value;
}

void Unit::die()
{
    //setVisible(false);
    isAlive = false;
}



void Unit::moveUnit()
{
    /*int xmove;
    int ymove;
*/
    if(currentSquare->getNext()->getHasNext() && isAlive)
    {
        if(x() == currentSquare->getNext()->getX()*40 && y() == currentSquare->getNext()->getY()*40)
        {
            currentSquare = currentSquare->getNext();
            //Implémentation obstacles avec currentSquare
            //TODO
            calcultateNextMove();
            //On test que le prochain n'ai pas d'obstacle
            if(currentSquare->getNext()->hasObstacle())
            {
                if(currentSquare->getNext()->getObstacle()->isEnabled())
                {
                    if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Deviation))
                    {
                        if(ability == 1)
                            currentSquare->activateDeviation();
                    }
                    else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Caillot))
                    {
                        if(ability == 2)
                             dynamic_cast<Caillot*>(currentSquare->getNext()->getObstacle())->destroy();
                        else
                            die();
                    }
                }
            }

        }





        moveBy(xmove,ymove);
    }
}
