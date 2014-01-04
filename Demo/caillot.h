#ifndef CAILLOT_H
#define CAILLOT_H

#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
class Caillot : public Obstacle, public QGraphicsObject
{
public:
    Caillot();
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void destroy();



};

#endif // CAILLOT_H
