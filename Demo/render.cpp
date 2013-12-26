#include "render.h"
#include "map.h"
#include "unit.h"
#include "mapsquare.h"
#include "level.h"
#include "obstacle.h"
#include "deviation.h"

#include <typeinfo>
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
    QGraphicsScene(parent)
{
    view = _view;

    MapSquare *path = generatePath(0,7,level);

    //QRectF *sceneRect = new QRectF(0,0,level->getMapWidth()*level->getTileWidth(),level->getMapHeight()*level->getTileHeight());
    //scene = new QGraphicsScene(*sceneRect,this);
    //this->setSceneRect(0,0,960,540);
    //Scene générale
    view->setScene(this);

    //Génération de la map (Layer 1)
    Map m(this,level);
    QList<QPixmap*> *pixmapList = new QList<QPixmap*>();
    pixmapList->append(new QPixmap(":/ressources/img/unit.png"));
    listUnit = new QList<Unit*>();
    for(int i = 0;i < 1;i++)
    {
        Unit *unit = new Unit(pixmapList,path);
        this->addItem(dynamic_cast<QGraphicsItem*>(unit));
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
    if(currentX >= 0 && currentY >=0 && currentY < level->getMapHeight() && currentX < level->getMapWidth())
    {

        int tabPos = currentX+currentY*level->getMapWidth();
        int fleche = *(level->getMapRoad()+tabPos);
        int orientationPrimary = 0;
        int obstacle = *(level->getMapObstacle()+tabPos);

        Obstacle *SquareObstacle = 0;
        MapSquare *PrimaryNextSquare = 0;
        MapSquare *SecondaryNextSquare = 0;

        //On vérifie que le square que l'on souhaite connecté n'existe pas deja
        /*foreach (MapSquare* existingSquare, existingSquares) {
            if(existingSquare->getX() == currentX && existingSquare->getY() == currentY)
            {
                qDebug() << "Square exists";
                return existingSquare;
            }
        }*/

        //GESTION OBSTACLES

        //On analyse la flèche pour savoir quelle est son orientation
        if(fleche!=0)
        {
            switch(fleche)
            {
                case 381: //Fleche droite
                    orientationPrimary = 6;
                    break;
                case 382: //Fleche gauche
                    orientationPrimary = 4;
                    break;
                case 383: //Fleche bas
                    orientationPrimary = 8;
                    break;
                case 384: //Fleche haut
                    orientationPrimary = 2;
                    break;
                case 385: //Fleche haut-gauche
                    orientationPrimary = 1;
                    break;
                case 386: //Fleche haut-droite
                    orientationPrimary = 3;
                    break;
                case 387: //Fleche bas-gauche
                    orientationPrimary = 7;
                    break;
                case 388: //Fleche bas-droite
                    orientationPrimary = 9;
                    break;
                default:
                    return PrimaryNextSquare;
            }
        }
        else
        {
            return PrimaryNextSquare;
        }

        switch(obstacle)
        {
            case 389:
                SquareObstacle = new Deviation(6);
                break;
            case 390:
                SquareObstacle = new Deviation(4);
                break;
            case 391:
                SquareObstacle = new Deviation(8);
                break;
            case 392:
                SquareObstacle = new Deviation(2);
                break;
            case 393:
                SquareObstacle = new Deviation(1);
                break;
            case 394:
                SquareObstacle = new Deviation(3);
                break;
            case 395:
                SquareObstacle = new Deviation(7);
                break;
            case 396:
                SquareObstacle = new Deviation(9);
                break;
        }

        //Si l'obstacle est != 0 on va devoir traiter le cas de deviation
        if(SquareObstacle != 0)
        {
            //qDebug() << "OBSTACLE JEUNE BLANC";
            //Si l'obstacle est une déviation

            if(typeid(*SquareObstacle) == typeid(Deviation))
            {
                //qDebug() << "DEVIATION YES !";
                //Vu que l'objet est une déviation, il faut traiter le chemin secondaire
                //On génére donc le chemin alternatif que l'on génère ici
                SecondaryNextSquare = generatePath(xFromOrientation(currentX,dynamic_cast<Deviation*>(SquareObstacle)->getOrientation()),yFromOrientation(currentY,dynamic_cast<Deviation*>(SquareObstacle)->getOrientation()),level);

            }
            //TODO Implémentation des autres obstacles
        }

        //Il faut maintenant lancer la generation récursive du principal et retourner l'objet actuel MapSquare

            PrimaryNextSquare = generatePath(xFromOrientation(currentX,orientationPrimary),yFromOrientation(currentY,orientationPrimary),level);
            MapSquare *square;
            if(SecondaryNextSquare != 0)
            {
                square = new MapSquare(PrimaryNextSquare,SecondaryNextSquare,currentX,currentY,SquareObstacle);
            }
            else
            {
                square = new MapSquare(PrimaryNextSquare,currentX,currentY,SquareObstacle);

            }

            return square;



    }
    return 0;
}



void Render::keyPressEvent(QKeyEvent *event)
{
       qDebug() << "key pressed !";
    switch(event->key())
    {
            case Qt::Key_1:
                mainUnit->setAbility(1);
            break;
    }



}

int Render::xFromOrientation(int x, int orientation)
{
    switch(orientation)
    {
        case 1:
        case 4:
        case 7:
            return x-1;
        case 2:
        case 5:
        case 8:
            return x;
        case 3:
        case 6:
        case 9:
            return x+1;
    }
    qDebug() << "END X, -1";
    return 0;
}

int Render::yFromOrientation(int y, int orientation)
{
    switch(orientation)
    {
        case 1:
        case 2:
        case 3:
            return y-1;
        case 4:
        case 6:
            return y;
        case 7:
        case 8:
        case 9:
            return y+1;
    }
    return 0;
}


void Render::updateCenter()
{
    view->centerOn(mainUnit);
    //scene->advance();
    emit moveUnits();
}



