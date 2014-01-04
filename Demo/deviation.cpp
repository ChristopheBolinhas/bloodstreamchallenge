#include "deviation.h"

Deviation::Deviation(int dev)
{

    setOrientation(dev);
}

void Deviation::setOrientation(int _orientation)
{
    orientation = _orientation;
}

int Deviation::getOrientation()
{
    return orientation;
}


void Deviation::switchPath(MapSquare *currentSquare)
{
    if(enabled)
        currentSquare->activateDeviation();
}

