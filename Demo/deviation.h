#ifndef DEVIATION_H
#define DEVIATION_H
#include "obstacle.h"
#include "mapsquare.h"
#include "enumobstacle.h"

class Deviation : public Obstacle
{
public:
    Deviation(int dev);
    //void traitement(MapSquare *square);
    void switchPath(MapSquare *currentSquare);
private:
    int orientation;
    void setOrientation(int _orientation);
};




#endif // DEVIATION_H
