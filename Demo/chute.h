#ifndef CHUTE_H
#define CHUTE_H

#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>

class Level;
class Chute : public Obstacle
{

public:
    Chute(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
};

#endif // CHUTE_H
