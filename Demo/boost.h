#ifndef BOOST_H
#define BOOST_H


#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
class Level;
class Boost : public Obstacle
{
public:
    Boost(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
};

#endif // BOOST_H
