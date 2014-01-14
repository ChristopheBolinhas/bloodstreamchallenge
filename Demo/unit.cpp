#include "unit.h"
#include <QPropertyAnimation>
#include <QDebug>
#include "deviation.h"
#include "obstacle.h"
#include "caillot.h"
#include "boost.h"
#include "bacterie.h"
#include "chute.h"
#include <typeinfo>

Unit::Unit(QList<QPixmap *> *_pixmapList, MapSquare *path, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{

    pixmapList = _pixmapList;
    currentSquare = path;
    speed = 0;
    paces = 0;
    setPos(path->getX()*40, path->getY()*40);
    setZValue(3);
    animation = new QPropertyAnimation(this,"pos",this);
    //calcultateNextMove();

}

Unit::~Unit()
{
    delete(this);
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


void Unit::calcultateNextMove(int _speed, int _paces)
{
    if(currentSquare->getHasNext())
    {
        xmove = (currentSquare->getX()*40 - pos().x())/_paces;
        ymove = (currentSquare->getY()*40 - pos().y())/_paces;

    }
}




void Unit::moveUnit()
{
    int paceMax = 20;
    QPoint point();
    qreal xMove = 0;
    qreal yMove = 0;

    //if(currentSquare->getNext()->getHasNext() && isAlive && animation->state() == QPropertyAnimation::Stopped)
    if(currentSquare->getNext()->getHasNext() && isAlive)
    {
        if(paces > 0)
        {
            paces--;
            moveBy(xmove,ymove);
        }
        else
        {
            paces = paceMax;
        }

        if(paces == paceMax)
        {
            currentSquare = currentSquare->getNext();
            //Implémentation obstacles avec currentSquare
            //TODO
            calcultateNextMove(speed, paceMax);
            //On test que le prochain n'ai pas d'obstacle
            if(currentSquare->getNext()->hasObstacle())
            {
                if(currentSquare->getNext()->getObstacle()->isEnabled())
                {

                    if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Caillot))
                    {
                        if(ability == 1)
                        {
                            currentSquare->getNext()->getObstacle()->disable();
                            ability = 0;

                        }
                        else
                        {
                            //die();
                        }
                    }
                    else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Bacterie))
                    {
                        if(ability == 2)
                        {
                            use();
                            currentSquare->getNext()->getObstacle()->disable();
                            ability = 0;
                        }
                        else
                        {
                            //die();

                        }
                    }
                    else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Deviation))
                    {
                        if(ability == 3)
                        {
                            use();
                            currentSquare->activateDeviation();
                            ability = 0;
                        }
                    }
                    else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Boost))
                    {
                        if(ability == 4)
                        {
                            use();
                            currentSquare->getNext()->getObstacle()->disable();
                            ability = 0;
                        }
                        else
                        {
                            speed++;
                        }

                    }
                    else if(typeid(*(currentSquare->getNext()->getObstacle())) == typeid(Chute))
                    {
                        if(ability == 5)
                        {
                            use();
                            currentSquare->getNext()->getObstacle()->disable();
                            ability = 0;
                        }
                        else
                        {
                            //die();
                            qDebug() << "Chute BOOM";
                        }

                    }
                }
            }
            xMove = ((currentSquare->getNext()->getX()*40)-pos().x())/(paceMax-2*speed);
            yMove = ((currentSquare->getNext()->getY()*40)-pos().y())/(paceMax-2*speed);
        }


        //Remplacement animation
        /*animation->setDuration(200-speed*40);
        animation->setStartValue(QPoint(currentSquare->getX()*40,currentSquare->getY()*40));
        animation->setEndValue(QPoint(currentSquare->getNext()->getX()*40,currentSquare->getNext()->getY()*40));
        animation->setEasingCurve(QEasingCurve::OutBounce);*/
        //connect(animation,SIGNAL(finished()),this,SLOT(moveUnit()));
        //animation->start();

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

    isAlive = false;
    emit killUnit(this);
}
void Unit::use()
{

    isAlive = false;
    emit useUnit(this);
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
