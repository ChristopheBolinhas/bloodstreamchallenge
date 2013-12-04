#include "render.h"
#include "map.h"
#include "unit.h"
#include "mapsquare.h"
#include "level.h"

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRect>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QDebug>
#include <QList>


Render::Render(QGraphicsView *_view, Level *level, QWidget *parent) :
    QWidget(parent)
{
    view = _view;

    MapSquare *path = new MapSquare(generatePath(0,7,level),0,7);
    QRectF *sceneRect = new QRectF(0,0,level->getMapWidth()*level->getTileWidth(),level->getMapHeight()*level->getTileHeight());
    scene = new QGraphicsScene(*sceneRect,this);
    //scene->setSceneRect(0,0,960,540);
    //Scene générale
    view->setScene(scene);
    //Génération de la map (Layer 1)
    Map m(scene,level);

    QList<QPixmap*> *pixmapList = new QList<QPixmap*>();
    pixmapList->append(new QPixmap(":/ressources/img/unit.png"));
    listUnit = new QList<Unit*>();
    for(int i = 0;i < 1;i++)
    {
        Unit *unit = new Unit(pixmapList,path);
        scene->addItem(dynamic_cast<QGraphicsItem*>(unit));
        connect(this,SIGNAL(moveUnits()),dynamic_cast<QObject*>(unit),SLOT(moveUnit()));
        listUnit->append(unit);
    }
    mainUnit = listUnit->first();
    //connect(this,SIGNAL(moveUnits()),dynamic_cast<QObject*>(u),SLOT(moveUnit()));
    //view->show();


    //Initialisation du timer
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateCenter()));
    timer->start(1000/120);//60fps
}

MapSquare* Render::generatePath(int currentX, int currentY, Level *level)
{
    int tabPos = currentX+currentY*level->getMapWidth();
    int fleche = *(level->getMapRoad()+tabPos);



    //GESTION OBSTACLES
        //TODO

    int nextX, nextY;
    //On analyse la flèche pour savoir quel est le suivante
    switch(fleche)
    {
        case 381: //Fleche droite
            nextX = currentX+1;
            nextY = currentY;
            break;
        case 382: //Fleche gauche
            nextX = currentX-1;
            nextY = currentY;
            break;
        case 383: //Fleche bas
            nextX = currentX;
            nextY = currentY+1;
            break;
        case 384: //Fleche haut
            nextX = currentX;
            nextY = currentY-1;
            break;
        case 385: //Fleche bas-droite -> haut-gauche
            nextX = currentX-1;
            nextY = currentY-1;
            break;
        case 386: //Fleche bas-gauche -> haut-droite
            nextX = currentX+1;
            nextY = currentY-1;
            break;
        case 387: //Fleche haut-droite -> bas-gauche
            nextX = currentX-1;
            nextY = currentY+1;
            break;
        case 388: //Fleche haut-gauche -> bas-droite
            nextX = currentX+1;
            nextY = currentY+1;
            break;
        default:
            return 0;
    }
    //qDebug() << "SQUARE";
    //On appele la case suivante
    if(nextX >= 0 && nextY >= 0)
    {
        return new MapSquare(generatePath(nextX,nextY,level),nextX,nextY);
    }
    else
    {
        return new MapSquare(0,50,50);
    }
}



MapSquare* Render::generatePath(int currentX, int currentY, int* PathTab, int PathTabSize, int* SecondaryPathTab, int SecondaryPathTabSize, int map_width, int map_height)
{

    int tabPos = currentX+currentY*map_width;
    int fleche = *(PathTab+tabPos);



    //GESTION OBSTACLES
        //TODO

    int nextX, nextY;
    //On analyse la flèche pour savoir quel est le suivante
    switch(fleche)
    {
        case 381: //Fleche droite
            nextX = currentX+1;
            nextY = currentY;
            break;
        case 382: //Fleche gauche
            nextX = currentX-1;
            nextY = currentY;
            break;
        case 383: //Fleche bas
            nextX = currentX;
            nextY = currentY+1;
            break;
        case 384: //Fleche haut
            nextX = currentX;
            nextY = currentY-1;
            break;
        case 385: //Fleche bas-droite -> haut-gauche
            nextX = currentX-1;
            nextY = currentY-1;
            break;
        case 386: //Fleche bas-gauche -> haut-droite
            nextX = currentX+1;
            nextY = currentY-1;
            break;
        case 387: //Fleche haut-droite -> bas-gauche
            nextX = currentX-1;
            nextY = currentY+1;
            break;
        case 388: //Fleche haut-gauche -> bas-droite
            nextX = currentX+1;
            nextY = currentY+1;
            break;
        default:
            return 0;
    }

    //On appele la case suivante
    if(nextX >= 0 && nextY >= 0)
    {
        return new MapSquare(generatePath(nextX,nextY,PathTab,PathTabSize,SecondaryPathTab,SecondaryPathTabSize,map_width,map_height),nextX,nextY);
    }
    else
    {
        return new MapSquare(0,50,50);
    }

}


void Render::updateCenter()
{

    view->centerOn(mainUnit);
    //scene->advance();
    emit moveUnits();
}


