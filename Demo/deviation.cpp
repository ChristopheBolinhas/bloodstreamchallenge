#include "deviation.h"

Deviation::Deviation(int dev)
{
    enabled = true;
    typeobstacle = EnumObstacle::deviation;
    setOrientation(dev);
}

void Deviation::setOrientation(int _orientation)
{
    orientation = _orientation;
}


void Deviation::switchPath(MapSquare *currentSquare)
{
    if(enabled)
        currentSquare->activateDeviation();
}
