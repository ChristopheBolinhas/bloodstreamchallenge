#include "mapsquare.h"
#include "obstacle.h"
#include <QList>

MapSquare::MapSquare(MapSquare *_primary, int _x, int _y)
{
    listNext = new QList<MapSquare*>();
    listNext->append(_primary);
    x = _x;
    y = _y;
}

MapSquare::MapSquare(MapSquare *_primary,MapSquare *_secondary, int _x, int _y)
{
    MapSquare(_primary,_x,_y);
    listNext->append(_secondary);
}

MapSquare* MapSquare::getNext()
{
    return listNext->first();
}



int MapSquare::getX()
{
    return x;
}

int MapSquare::getY()
{
    return y;
}

Obstacle *MapSquare::getObstacle()
{
    return obstacle;
}

bool MapSquare::hasObstacle()
{
    if(obstacle != 0)
        return true;
    else
        return false;
}

void MapSquare::activateDeviation()
{
    if(listNext->size() > 1)
        listNext->takeFirst();
}
