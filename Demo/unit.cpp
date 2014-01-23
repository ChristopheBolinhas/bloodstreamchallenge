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
    initUnit();
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
    paceMax = 18;//Vitesse de base
    ability = 0;
}

void Unit::destroy()
{
    deathTimer->stop();
    delete(deathTimer);
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
    if(currentSquare->getNext()->getHasNext())
    {
        if(currentSquare->getNext()->getIsEnd() && isAlive)
        {
            finish();
        }
        if(isAlive)
        {


            if(paces == paceMax-speed)
            {

                if(currentSquare->getNext()->hasObstacle())
                {
                    if(currentSquare->getNext()->getObstacle()->isEnabled())
                    {
                        Obstacle *obs = currentSquare->getNext()->getObstacle();
                        if(typeid(*(obs)) == typeid(Caillot))
                        {
                            if(ability == 1)
                            {
                                use();
                                obs->disable();
                            }
                            else
                            {
                                die();
                            }
                        }
                        else if(typeid(*(obs)) == typeid(Bacterie))
                        {
                            if(ability == 2)
                            {
                                use();
                                obs->disable();
                            }
                            else
                            {
                                die();

                            }
                        }
                        else if(typeid(*(obs)) == typeid(Deviation))
                        {
                            if(ability == 3)
                            {
                                use();
                                dynamic_cast<Deviation*>(obs)->switchPath(currentSquare->getNext());

                            }
                        }
                        else if(typeid(*(obs)) == typeid(Boost))
                        {
                            if(ability == 4)
                            {
                                use();
                                obs->disable();
                            }
                            else
                            {
                                if(speed < 12) speed++;
                            }

                        }
                        else if(typeid(*(obs)) == typeid(Chute))
                        {
                            if(ability == 5)
                            {
                                use();
                                obs->disable();
                            }
                            else
                            {
                                die();
                            }

                        }
                    }
                }
                currentSquare = currentSquare->getNext();
                calcultateNextMove(speed, paceMax);
            }
            if(paces > 0)
            {
                paces--;
                moveBy(xmove,ymove);
            }
            else
            {
                paces = paceMax-speed;
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
    emit switchNext(0);
    deathTimer->start();

}
void Unit::use()
{

    isAlive = false;
    deathMode = false;
    emit switchNext(ability);
    deathTimer->start();
}

void Unit::finish()
{
    isAlive = false;
    emit switchNext(10);
    emit winUnit(this);
}

void Unit::initUnit()
{
    isAlive = true;
    won = false;
    paceMax = 15;
}
