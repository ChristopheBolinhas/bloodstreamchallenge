#include "mapsquare.h"

MapSquare::MapSquare(MapSquare *_next, int _x, int _y)
{

    next = _next;
    x = _x;
    y = _y;
}

MapSquare* MapSquare::getNext()
{
    return next;
}

int MapSquare::getX()
{
    return x;
}

int MapSquare::getY()
{
    return y;
}
