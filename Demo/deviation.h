#ifndef DEVIATION_H
#define DEVIATION_H
#include "obstacle.h"
#include "mapsquare.h"
#include "level.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>

class Deviation : public Obstacle//, public QGraphicsObject
{
public:
    Deviation(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
    //void traitement(MapSquare *square);
    void switchPath(MapSquare *currentSquare);

};




#endif // DEVIATION_H
