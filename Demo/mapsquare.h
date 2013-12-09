#ifndef MAPSQUARE_H
#define MAPSQUARE_H
#include <QList>

class Obstacle;
class MapSquare
{
public:
    MapSquare(MapSquare *_primary = 0, int x = 0, int y = 0);
    MapSquare(MapSquare *_primary = 0, MapSquare *_secondary = 0, int x = 0, int y = 0);



    MapSquare* getNext();
    int getX();
    int getY();
    Obstacle *getObstacle();
    bool hasObstacle();
    void activateDeviation();

private:
    QList<MapSquare*> *listNext;
    int x;
    int y;
    Obstacle *obstacle = 0;

};

#endif // MAPSQUARE_H
