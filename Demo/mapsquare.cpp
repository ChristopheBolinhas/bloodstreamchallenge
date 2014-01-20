#include "mapsquare.h"
#include "obstacle.h"
#include <QList>
#include <QDebug>

MapSquare::MapSquare(MapSquare *_primary, int _x, int _y, Obstacle *_obstacle)
{
    initVariables();
    x = _x;
    y = _y;
    if(_primary != 0)
    {
        primaryNext = _primary;
        hasNext = true;
    }
    setObstacle(_obstacle);
}

MapSquare::MapSquare(MapSquare *_primary, int _x, int _y, Obstacle *_obstacle, bool _isEnd)
{
    initVariables();
    x = _x;
    y = _y;
    if(_primary != 0)
    {
        primaryNext = _primary;
        hasNext = true;
    }
    setObstacle(_obstacle);
    isEnd = _isEnd;
}


MapSquare::MapSquare(MapSquare *_primary, MapSquare *_secondary, int _x, int _y, Obstacle *_obstacle)
{
    initVariables();
    x = _x;
    y = _y;
    if(_primary != 0)
    {
        primaryNext = _primary;
        hasNext = true;
    }

    if(_secondary != 0)    
    {
        secondaryNext = _secondary;
        hasSecondary = true;

    }
    setObstacle(_obstacle);

}


void MapSquare::setObstacle(Obstacle *_obstacle)
{
    if(_obstacle != 0)
        obstacle = _obstacle;
    else
    {
        obstacle = 0;
    }
}

void MapSquare::initVariables()
{
    hasSecondary = false;
    takeSecondary = false;
    obstacle = 0;
    hasNext = false;
    isEnd = false;
}


MapSquare* MapSquare::getNext()
{
    if(takeSecondary)
    {
        return secondaryNext;
    }
    else
    {
        return primaryNext;
    }
}


bool MapSquare::getHasNext()
{
    return hasNext;
}

bool MapSquare::getIsEnd()
{
    return isEnd;
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
    if(hasSecondary)
    {
        takeSecondary = true;
    }
}
