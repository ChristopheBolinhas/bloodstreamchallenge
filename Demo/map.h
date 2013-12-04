#ifndef MAP_H
#define MAP_H

class QRect;
class QGraphicsScene;
class QPoint;
class Level;
class Map
{
public:
    Map(QGraphicsScene *scene, Level *level);
    //Map(QGraphicsScene *scene, Level *level)


private:
    QRect* getRect(int id, Level *level);
    QPoint* getPoint(int id, Level *level);
    int tileset_width;
    int tileset_height;
    int tile_width;
    int tile_height;
    int map_width;
    int map_height;
};

#endif // MAP_H
