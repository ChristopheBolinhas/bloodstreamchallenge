#ifndef CAILLOT_H
#define CAILLOT_H

#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
class Level;
class Caillot : public Obstacle
{
public:
    Caillot(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
};

#endif // CAILLOT_H
