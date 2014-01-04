#ifndef BOOST_H
#define BOOST_H


#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>

class Boost : public Obstacle, public QGraphicsObject
{
public:
    Boost();
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // BOOST_H
