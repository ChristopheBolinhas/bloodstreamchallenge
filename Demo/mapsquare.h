#ifndef MAPSQUARE_H
#define MAPSQUARE_H
#include <QList>

class Obstacle;
class MapSquare
{
public:
    MapSquare(MapSquare *_primary = 0, int _x = 0, int _y = 0, Obstacle *_obstacle = 0);
    MapSquare(MapSquare *_primary = 0, MapSquare *_secondary = 0, int x = 0, int y = 0, Obstacle *_obstacle = 0);



    MapSquare* getNext();
    int getX();
    int getY();
    Obstacle *getObstacle();
    bool hasObstacle();
    void activateDeviation();
    MapSquare removePrimary();
private:
    QList<MapSquare*> *listNext;
    int x;
    int y;
    Obstacle *obstacle = 0;
    void setObstacle(Obstacle *_obstacle);
};

#endif // MAPSQUARE_H
