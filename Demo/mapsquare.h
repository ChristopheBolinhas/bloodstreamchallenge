#ifndef MAPSQUARE_H
#define MAPSQUARE_H
#include <QList>

class Obstacle;
class MapSquare
{
public:
    MapSquare(MapSquare *_primary = 0, int _x = 0, int _y = 0, Obstacle *_obstacle = 0);
    MapSquare(MapSquare *_primary = 0, MapSquare *_secondary = 0, int x = 0, int y = 0, Obstacle *_obstacle = 0);
    MapSquare(MapSquare *_primary, int _x, int _y, Obstacle *_obstacle, bool _isEnd);


    MapSquare* getNext();
    int getX();
    int getY();
    Obstacle *getObstacle();
    bool hasObstacle();
    void activateDeviation();
    bool getHasNext();
    bool getIsEnd();

private:
    MapSquare *primaryNext;
    MapSquare *secondaryNext;
    bool hasSecondary;
    bool takeSecondary;
    int x;
    int y;
    Obstacle *obstacle;
    bool hasNext;
    bool isEnd;
    void setObstacle(Obstacle *_obstacle);

    void initVariables();

};

#endif // MAPSQUARE_H
