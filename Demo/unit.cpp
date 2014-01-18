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
    deathAnimationState = 0;
    deathTimer = new QTimer(this);
    deathTimer->setInterval(100);
    connect(deathTimer,SIGNAL(timeout()),this,SLOT(animateDeath()));
    paceMax = 25;
    ability = 0;
    //calcultateNextMove();

}

void Unit::destroy()
{
    deathTimer->stop();

    delete(deathTimer);
    qDebug() << "Destroy unit";
    //delete(this);

}

Unit::~Unit()
{
    destroy();
}

QRectF Unit::boundingRect() const
{
    return QRectF (0,0,40, 40);
}

void Unit::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    if(isAlive)
    {
        painter->drawPixmap(0,0,40,40,*pixmapList->at(0+ability*6));
    }
    else if(deathAnimationState < 6)
    {
        painter->drawPixmap(0,0,40,40,*pixmapList->at(deathAnimationState+ability*6));
    }
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
    //if(currentSquare->getNext()->getHasNext() && isAlive && animation->state() == QPropertyAnimation::Stopped)

    if(currentSquare->getNext()->getHasNext())
    {
        if(currentSquare->getNext()->getIsEnd() && isAlive)
        {
            finish();
        }
        if(isAlive)
        {
            if(paces > 0)
            {
                paces--;
                moveBy(xmove,ymove);
            }
            else
            {
                paces = paceMax-speed;
            }

            if(paces == paceMax-speed)
            {

                //On test que le prochain n'ai pas d'obstacle
                if(currentSquare->getNext()->hasObstacle())
                {
                    if(currentSquare->getNext()->getObstacle()->isEnabled())
                    //if(currentSquare->getObstacle()->isEnabled())
                    {
                        Obstacle *obs = currentSquare->getNext()->getObstacle();
                        //Obstacle *obs = currentSquare->getObstacle();
                        if(typeid(*(obs)) == typeid(Caillot))
                        {
                            if(ability == 1)
                            {
                                use();
                                obs->disable();
                                //ability = 0;

                            }
                            else
                            {
                                //die();
                            }
                        }
                        else if(typeid(*(obs)) == typeid(Bacterie))
                        {
                            if(ability == 2)
                            {
                                use();
                                obs->disable();
                                //ability = 0;
                            }
                            else
                            {
                                //die();

                            }
                        }
                        else if(typeid(*(obs)) == typeid(Deviation))
                        {
                            if(ability == 3)
                            {
                                use();
                                dynamic_cast<Deviation*>(obs)->switchPath(currentSquare->getNext());
                                //currentSquare->getNext()->activateDeviation();
                                //ability = 0;
                            }
                        }
                        else if(typeid(*(obs)) == typeid(Boost))
                        {
                            if(ability == 4)
                            {
                                use();
                                obs->disable();
                                //ability = 0;
                            }
                            else
                            {
                                speed++;
                            }

                        }
                        else if(typeid(*(obs)) == typeid(Chute))
                        {
                            if(ability == 5)
                            {
                                use();
                                obs->disable();
                                //ability = 0;
                            }
                            else
                            {
                                //die();
                            }

                        }
                    }
                }
                currentSquare = currentSquare->getNext();
                //Implémentation obstacles avec currentSquare
                calcultateNextMove(speed, paceMax);
            }
        }
    }
}

void Unit::animateDeath()
{
    if(deathAnimationState < 6)
    {
        deathAnimationState++;
        update();
    }
    else
    {
        if(deathMode)
            emit killUnit(this);
        else
            emit useUnit(this);
        deathTimer->stop();
    }
}

int Unit::getAbility() const
{
    return ability;
}

void Unit::setAbility(int value)
{
    if(ability == 0)
        ability = value;
}

void Unit::die()
{

    isAlive = false;
    deathMode = true;
    emit switchNext();
    deathTimer->start();

}
void Unit::use()
{

    isAlive = false;
    deathMode = false;
    emit switchNext();
    deathTimer->start();
    //emit useUnit(this);
}

void Unit::finish()
{
    isAlive = false;
    emit switchNext();
    emit winUnit(this);
}
