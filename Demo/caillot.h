#ifndef CAILLOT_H
#define CAILLOT_H

#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
class Level;
class Caillot : public Obstacle//, public QGraphicsObject
{
public:
    Caillot(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void destroy();



};

#endif // CAILLOT_H
