#ifndef CHUTE_H
#define CHUTE_H

#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>

class Level;
class Chute : public Obstacle//, public QGraphicsObject
{
public:
    Chute(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
    ~Chute();
    //QRectF boundingRect() const override;

   // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void destroy();


};

#endif // CHUTE_H
