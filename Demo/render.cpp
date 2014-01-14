#include "render.h"
#include "map.h"
#include "unit.h"
#include "mapsquare.h"
#include "level.h"
#include "obstacle.h"
#include "deviation.h"
#include "caillot.h"
#include "chute.h"
#include "boost.h"
#include "abilitybutton.h"
#include "gameview.h"

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
#include <QLabel>
#include <QGraphicsProxyWidget>

Render::Render(GameView *_view, Level *level, QWidget *parent) :
    QGraphicsScene(parent)
{
    view = _view;
    connect(view,SIGNAL(sendAbility(int)),this,SLOT(setAbilitySlot(int)));
    loadImages();
    view->scale(0.8,0.8);


    //Génération de la map (Layer 1)
    Map m(this,level);
    MapSquare *path = generatePath(m.getStartPoint()->x(),m.getStartPoint()->y(),level);

    view->setScene(this);

    QList<QPixmap*> *pixmapList = new QList<QPixmap*>();
    pixmapList->append(new QPixmap(":/ressources/img/unit.png"));
    //unitCount = level.getNbUnits();
    unitCount = 5;
    unitToInit = unitCount;
    unitMinima = 1;
    listUnit = new QList<Unit*>();
    for(int i = 0;i < unitCount;i++)
    {
        Unit *unit = new Unit(pixmapList,path);
        this->addItem(dynamic_cast<QGraphicsItem*>(unit));
        listUnit->append(unit);
        qDebug() << "units2";
        connect(unit,SIGNAL(killUnit(Unit*)),this,SLOT(unitDie(Unit*)));
        connect(unit,SIGNAL(useUnit(Unit*)),this,SLOT(unitUse(Unit*)));
    }

    mainUnit = listUnit->first();
    //connect(this,SIGNAL(moveUnits()),dynamic_cast<QObject*>(u),SLOT(moveUnit()));
    //view->show();
    connect(this, SIGNAL(updateScore(QString)),view,SIGNAL(setScore(QString)));
    connect(this, SIGNAL(updateUnitCount(QString)),view,SIGNAL(setUnitCount(QString)));
    QGraphicsTextItem *test = new QGraphicsTextItem();
    test->setPlainText("QGraphicsTextItem");
    addItem(test);

    qDebug() << "yolo3";
    startTimer = new QTimer(this);
    connect(startTimer,SIGNAL(timeout()),this,SLOT(startGame()));
    //Initialisation du timer
    mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(updateCenter()));
    startTimer->start(1000);
}

Render::~Render()
{

}

void Render::initializeGame()
{
    //connect(this,SIGNAL(moveUnits()),dynamic_cast<QObject*>(unit),SLOT(moveUnit()));
}


void Render::loadImages()
{
    //Boost images
    boostImages = new QList<QPixmap*>();
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/trap_on.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/trap_anim1.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/trap_anim2.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/trap_anim3.png"));


}




void Render::setAbilitySlot(int id)
{
    mainUnit->setAbility(id);
}

MapSquare* Render::generatePath(int currentX, int currentY, Level *level)
{
    if(currentX >= 0 && currentY >=0 && currentY < level->getMapHeight() && currentX < level->getMapWidth())
    {

        int tabPos = currentX+currentY*level->getMapWidth();
        int fleche = *(level->getMapRoad()+tabPos);
        int orientationPrimary = 0;
        int obstacle = *(level->getMapObstacle()+tabPos);
        bool isEndSquare = false;

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
        //Boost - Rouge - 361
        //Caillot - Jaune - 362
        //Bacterie - Vert - 363
        //Pont - Bleu - 364
        //Start - Blanc - 365
        //End - Violet - 366


        switch(obstacle)
        {
            case 361:
                SquareObstacle = new Boost(currentX, currentY,orientationPrimary,boostImages, level);
                break;
            case 362:
                SquareObstacle = new Caillot(currentX,currentY,orientationPrimary,0,level);
                break;
            case 363:

            break;
            case 364:
                SquareObstacle = new Chute(currentX,currentY,orientationPrimary,0,level);
                break;
            case 366:
                isEndSquare = true;
                break;
            case 389:
                SquareObstacle = new Deviation(currentX,currentY, 6, 0, level);
                break;
            case 390:
                SquareObstacle = new Deviation(currentX,currentY, 4, 0, level);
                break;
            case 391:
                SquareObstacle = new Deviation(currentX,currentY, 8, 0, level);
                break;
            case 392:
                SquareObstacle = new Deviation(currentX,currentY, 2, 0, level);
                break;
            case 393:
                SquareObstacle = new Deviation(currentX,currentY, 1, 0, level);
                break;
            case 394:
                SquareObstacle = new Deviation(currentX,currentY, 3, 0, level);
                break;
            case 395:
                SquareObstacle = new Deviation(currentX,currentY, 7, 0, level);
                break;
            case 396:
                SquareObstacle = new Deviation(currentX,currentY, 9, 0, level);
                break;
        }

        //Si l'obstacle est != 0 on va devoir traiter le cas de deviation
        if(SquareObstacle != 0)
        {
            //qDebug() << "OBSTACLE JEUNE BLANC";
            //Si l'obstacle est une déviation

            if(typeid(*SquareObstacle) == typeid(Deviation))
            {
                //Vu que l'objet est une déviation, il faut traiter le chemin secondaire
                //On génére donc le chemin alternatif que l'on génère ici
                SecondaryNextSquare = generatePath(xFromOrientation(currentX,dynamic_cast<Deviation*>(SquareObstacle)->getOrientation()),yFromOrientation(currentY,dynamic_cast<Deviation*>(SquareObstacle)->getOrientation()),level);
                addItem(dynamic_cast<Deviation*>(SquareObstacle));
            }
            else if(typeid(*SquareObstacle) == typeid(Caillot))
            {
                addItem(dynamic_cast<Caillot*>(SquareObstacle));
                //dynamic_cast<Caillot*>(SquareObstacle)->setPos(currentX*level->getTileWidth(),currentY*level->getTileHeight());
            }
            else if(typeid(*SquareObstacle) == typeid(Boost))
            {
                addItem(dynamic_cast<Boost*>(SquareObstacle));
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
                if(!isEndSquare)
                {
                    square = new MapSquare(PrimaryNextSquare,currentX,currentY,SquareObstacle);
                }
                else
                {
                    square = new MapSquare(PrimaryNextSquare,currentX,currentY,SquareObstacle,true);
                }
            }
            return square;



    }
    return 0;
}



void Render::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_1:
            mainUnit->setAbility(1);
        break;
        case Qt::Key_2:
            mainUnit->setAbility(2);
            break;
        case Qt::Key_3:
            mainUnit->setAbility(3);
        break;
        case Qt::Key_4:
            mainUnit->setAbility(4);
            break;
        case Qt::Key_5:
            mainUnit->setAbility(5);
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

void Render::calculateScore()
{
    int scoreCalc = ((unitCount-unitMinima)/(unitCount-unitUsed-unitDead))*1000 - 50 * unitDead;
    emit updateScore(QString::number(scoreCalc));
}


void Render::unitUse(Unit *unit)
{
    unitCount--;
    unitUsed++;
    listUnit->removeOne(unit);
    //listUnit->removeFirst();
    if(listUnit->size() >0)
    {
        mainUnit = listUnit->first();
    }

    calculateScore();
}

void Render::unitDie(Unit *unit)
{
    unitCount--;
    unitDead++;
    listUnit->removeOne(unit);
    //listUnit->removeFirst();
    if(listUnit->size() > 0)
    {
        mainUnit = listUnit->first();
    }
    calculateScore();

}



void Render::updateCenter()
{
    if(listUnit->size() > 0)
    {
        view->centerOn(mainUnit);
        //advance();
        emit moveUnits();
    }
}

void Render::startGame()
{
    view->centerOn(mainUnit);
    if(startCountDown == 0)
    {

        mainTimer->start(1000/60);//60fps

        startCountDown--;
    }
    else if(startCountDown < 0)
    {
        if(unitToInit > 0)
        {
            connect(this,SIGNAL(moveUnits()),dynamic_cast<QObject*>(listUnit->at(unitCount-unitToInit)),SLOT(moveUnit()));
            unitToInit--;
        }
        else
        {
            startTimer->stop();
        }
    }
    else
    {
        //view->scale(3,3);
        startCountDown--;
    }
}

void Render::toggleGame()
{

}





