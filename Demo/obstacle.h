#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "enumobstacle.h"

class Obstacle
{

public:
    explicit Obstacle();
    bool isEnabled();
    EnumObstacle::TypeObstacle getTypeObstacle();

protected:
    bool enabled;
    EnumObstacle::TypeObstacle typeobstacle;
private:

};

#endif // OBSTACLE_H
