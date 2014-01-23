#include "map.h"
#include "level.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QRect>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>


Map::Map(QGraphicsScene *scene, Level *level)
{
    //Loading du tileset
    QPixmap p(level->getPathTileSet());
    //Generation de la map
    finalBackground = new QPixmap(level->getMapWidth()*level->getTileWidth(),level->getMapHeight()*level->getTileHeight());
    finalDecors = new QPixmap(level->getMapWidth()*level->getTileWidth(),level->getMapHeight()*level->getTileHeight());
    finalForeground = new QPixmap(level->getMapWidth()*level->getTileWidth(),level->getMapHeight()*level->getTileHeight());
    finalForeground->fill(Qt::transparent);
    finalDecors->fill(Qt::transparent);


    QPainter painterBackground(finalBackground);
    QPainter painterDecors(finalDecors);
    QPainter painterForeground(finalForeground);

    for(int i = 0;i < level->getMapWidth()*level->getMapHeight();i++)
    {
        painterBackground.drawPixmap(*getPoint(i,level),p.copy(*getRect(*(level->getMapBackground()+i)-1,level)));
        if(*(level->getMapForeground()+i)-1 > 0)
        {
            painterForeground.drawPixmap(*getPoint(i,level),p.copy(*getRect(*(level->getMapForeground()+i)-1,level)));
        }
        if(*(level->getMapDecors()+i)-1 > 0)
        {
            painterDecors.drawPixmap(*getPoint(i,level),p.copy(*getRect(*(level->getMapDecors()+i)-1,level)));
        }

        if(*(level->getMapObstacle()+i) == 365)
        {
            startPoint = new QPoint(i%level->getMapWidth(),i/level->getMapWidth());
        }
    }


    //Generation du foreground Z = 5
    QGraphicsItem *it = scene->addPixmap(*finalBackground);

    it->setZValue(1);

    it = scene->addPixmap(*finalDecors);
    it->setZValue(2);


    it = scene->addPixmap(*finalForeground);
    it->setZValue(4);


}

Map::~Map()
{
    delete(finalBackground);
    delete(finalDecors);
    delete(finalForeground);
}

QPoint* Map::getStartPoint()
{
    return startPoint;
}

QPoint* Map::getPoint(int id, Level *level)
{
    int x = id%level->getMapWidth()*level->getTileWidth();
    int y = id/level->getMapWidth()*level->getTileHeight();
    return new QPoint(x,y);
}


QRect* Map::getRect(int id, Level *level)
{
    int x = id%(level->getTileSetWidth()/level->getTileWidth())*level->getTileWidth();
    int y = id/(level->getTileSetWidth()/level->getTileWidth())*level->getTileHeight();

    return new QRect(x,y,level->getTileWidth(),level->getTileHeight());
}
