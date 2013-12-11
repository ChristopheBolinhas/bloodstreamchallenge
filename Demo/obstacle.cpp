#include "obstacle.h"

Obstacle::Obstacle()
{
    enabled = true;
}

bool Obstacle::isEnabled()
{
    return enabled;
}

EnumObstacle::TypeObstacle Obstacle::getTypeObstacle()
{
    return typeobstacle;
}

