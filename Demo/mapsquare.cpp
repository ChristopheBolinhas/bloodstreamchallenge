#include "mapsquare.h"
#include "obstacle.h"
#include <QList>

MapSquare::MapSquare(MapSquare *_primary, int _x, int _y, Obstacle *_obstacle)
{
    listNext = new QList<MapSquare*>();
    listNext->append(_primary);
    x = _x;
    y = _y;
    setObstacle(_obstacle);
}

MapSquare::MapSquare(MapSquare *_primary, MapSquare *_secondary, int _x, int _y, Obstacle *_obstacle)
{
    MapSquare(_primary,_x,_y);
    listNext->append(_secondary);
}

void MapSquare::setObstacle(Obstacle *_obstacle)
{
    if(obstacle != 0)
        obstacle = _obstacle;
}


MapSquare* MapSquare::getNext()
{
    return listNext->first();
}

MapSquare MapSquare::removePrimary()
{
    if(listNext->size() > 1)
    {
        listNext->pop_front();
    }
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
