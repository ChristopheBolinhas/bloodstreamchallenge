#include "unit.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <deviation.h>
#include <obstacle.h>
#include <caillot.h>
#include <boost.h>
#include <typeinfo>

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
void Unit::moveUnit()
{
    if(currentSquare->getNext()->getHasNext() && isAlive && animation->state() == QPropertyAnimation::Stopped)
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
                    {
                        currentSquare->activateDeviation();
                        ability = 0;
                    }
                }
                else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Caillot))
                {
                    if(ability == 2)
                    {
                        dynamic_cast<Caillot*>(currentSquare->getNext()->getObstacle())->destroy();
                        ability = 0;
                        speed++;//TEMP
                    }
                    /*else
                        die();*/
                }
                else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Boost))
                {
                    dynamic_cast<Boost*>(currentSquare->getNext()->getObstacle())->disable();
                    //speed++;
                }
            }
        }
        animation->setDuration(200-speed*40);
        animation->setStartValue(QPoint(currentSquare->getX()*40,currentSquare->getY()*40));
        animation->setEndValue(QPoint(currentSquare->getNext()->getX()*40,currentSquare->getNext()->getY()*40));
        //animation->setEasingCurve(QEasingCurve::OutInQuart);
        connect(animation,SIGNAL(finished()),this,SLOT(moveUnit()));
        animation->start();

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



/*void Unit::moveUnit()
{
    /*int xmove;
    int ymove;

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
                        {
                            currentSquare->activateDeviation();
                            ability = 0;
                        }
                    }
                    else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Caillot))
                    {
                        if(ability == 2)
                        {
                            dynamic_cast<Caillot*>(currentSquare->getNext()->getObstacle())->destroy();
                            ability = 0;
                        }
                        else
                            die();
                    }
                }
            }

        }





        moveBy(xmove,ymove);
    }
}
*/
