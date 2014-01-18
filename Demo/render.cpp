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
#include "bacterie.h"
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
#include <QtAlgorithms>

Render::Render(GameView *_view, Level *level, QWidget *parent) :
    QGraphicsScene(parent)
{
    view = _view;
    connect(view,SIGNAL(sendAbility(int)),this,SLOT(setAbilitySlot(int)));
    loadImages();
    play = true;

    //Génération de la map (Layer 1)
    Map m(this,level);
    qDebug() << "Map";
    qDebug() << m.getStartPoint()->x() << " | " << m.getStartPoint()->y();
    qDebug() << *(level->getMapObstacle() + m.getStartPoint()->x()+m.getStartPoint()->y()*level->getMapWidth());
    qDebug() << *(level->getMapRoad() + m.getStartPoint()->x()+m.getStartPoint()->y()*level->getMapWidth());
    MapSquare *path = generatePath(m.getStartPoint()->x(),m.getStartPoint()->y(),level);
    qDebug() << "Path";
    view->setScene(this);

    qDebug() << level->getNbUnite();
    unitCount = level->getNbUnite();
    unitToInit = unitCount;
    unitMinima = 1;
    listUnit = new QList<Unit*>();

    for(int i = 0;i < unitCount;i++)
    {
        Unit *unit = new Unit(unitsImages,path);
        this->addItem(dynamic_cast<QGraphicsItem*>(unit));
        listUnit->append(unit);
        connect(unit,SIGNAL(killUnit(Unit*)),this,SLOT(unitDie(Unit*)));
        connect(unit,SIGNAL(useUnit(Unit*)),this,SLOT(unitUse(Unit*)));
        connect(unit,SIGNAL(winUnit(Unit*)),this,SLOT(unitWin(Unit*)));
        connect(unit,SIGNAL(switchNext()),this,SLOT(switchNext()));
        qDebug() << "Unit " << i;
    }
    qDebug() << "Units";
    mainUnit = listUnit->first();
    connect(this, SIGNAL(updateScore(QString)),view,SIGNAL(setScore(QString)));
    connect(this, SIGNAL(updateUnitCount(QString)),view,SIGNAL(setUnitCount(QString)));
    connect(view,SIGNAL(pauseGame(bool)),this,SLOT(toggleGame(bool)));
    emit updateUnitCount(QString::number(unitCount));

    startTimer = new QTimer(this);
    connect(startTimer,SIGNAL(timeout()),this,SLOT(startGame()));
    //Initialisation du timer
    mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(gameTimer()));
    startTimer->start(1000);
    calculateScore();
}

void Render::destroy()
{
    mainTimer->stop();
    startTimer->stop();
    delete(mainTimer);
    delete(startTimer);
    view->setStartInfo(0);
    qDeleteAll(*listUnit);
    delete(listUnit);
    qDeleteAll(items());
}

Render::~Render()
{
    destroy();
}

void Render::initializeGame()
{
    //connect(this,SIGNAL(moveUnits()),dynamic_cast<QObject*>(unit),SLOT(moveUnit()));
}

void Render::deleteImages(QList<QPixmap *> *list)
{
    for(int i=0;i<list->count();i++)
    {
        delete(list->takeAt(0));
    }

}

void Render::deleteUnits(QList<Unit *> *list)
{
    for(int i=0;i<list->count();i++)
    {
        list->takeAt(0)->destroy();
        delete(list->takeAt(0));
    }
    delete(list);

}


/**********************************
 *  void loadImages()
 *  Cette fonction s'occupe de charger les images en mémoire pour leur utilisation dans les parties
 *
 *  Note importante : Images 0-3 doivent concerne l'affichage vertical (affichage de haut en bas) puis 4-7
 * concernent l'affichage horizontal (gauche à droite)
 *
 * *******************************/
void Render::loadImages()
{
    //Units images
    unitsImages = new QList<QPixmap*>();
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Normal/unit_1.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Normal/unit_2.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Normal/unit_3.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Normal/unit_4.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Normal/unit_5.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Normal/unit_6.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Caillot/unit_1.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Caillot/unit_2.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Caillot/unit_3.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Caillot/unit_4.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Caillot/unit_5.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Caillot/unit_6.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Bacterie/unit_1.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Bacterie/unit_2.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Bacterie/unit_3.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Bacterie/unit_4.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Bacterie/unit_5.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Bacterie/unit_6.png"));

    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Deviation/unit_1.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Deviation/unit_2.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Deviation/unit_3.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Deviation/unit_4.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Deviation/unit_5.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Deviation/unit_6.png"));

    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Boost/unit_1.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Boost/unit_2.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Boost/unit_3.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Boost/unit_4.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Boost/unit_5.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Boost/unit_6.png"));

    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Chute/unit_1.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Chute/unit_2.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Chute/unit_3.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Chute/unit_4.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Chute/unit_5.png"));
    unitsImages->append(new QPixmap(":/units/ressources/img/Unites/Chute/unit_6.png"));




    //Boost images
    boostImages = new QList<QPixmap*>();
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/updown/trap_on.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/updown/trap_anim1.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/updown/trap_anim2.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/updown/trap_anim3.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/leftright/trap_on.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/leftright/trap_anim1.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/leftright/trap_anim2.png"));
    boostImages->append(new QPixmap(":/boost/ressources/img/Boost/leftright/trap_anim3.png"));

    //Caillot images
    caillotImages = new QList<QPixmap*>();
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/updown/trap_on.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/updown/trap_anim1.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/updown/trap_anim2.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/updown/trap_anim3.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/leftright/trap_on.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/leftright/trap_anim1.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/leftright/trap_anim2.png"));
    caillotImages->append(new QPixmap(":/caillot/ressources/img/Caillot/leftright/trap_anim3.png"));


    //Deviation
    deviationImages = new QList<QPixmap*>();
    deviationImages->append(new QPixmap(":/deviation/ressources/img/Deviation/1.png"));
    deviationImages->append(new QPixmap(":/deviation/ressources/img/Deviation/2.png"));
    deviationImages->append(new QPixmap(":/deviation/ressources/img/Deviation/3.png"));
    deviationImages->append(new QPixmap(":/deviation/ressources/img/Deviation/4.png"));

    //Bacteries images
    bacterieImages = new QList<QPixmap*>();
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/updown/trap_on.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/updown/trap_anim1.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/updown/trap_anim2.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/updown/trap_anim3.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/leftright/trap_on.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/leftright/trap_anim1.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/leftright/trap_anim2.png"));
    bacterieImages->append(new QPixmap(":/bacterie/ressources/img/Bacterie/leftright/trap_anim3.png"));

    //Chute images
    chuteImages = new QList<QPixmap*>();
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/updown/trap_on.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/updown/trap_anim1.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/updown/trap_anim2.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/updown/trap_anim3.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/leftright/trap_on.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/leftright/trap_anim1.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/leftright/trap_anim2.png"));
    chuteImages->append(new QPixmap(":/chute/ressources/img/Chute/leftright/trap_anim3.png"));




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
        qDebug() << "obtsacle est: " << obstacle;
        bool isEndSquare = false;

        Obstacle *SquareObstacle = 0;
        MapSquare *PrimaryNextSquare = 0;
        MapSquare *SecondaryNextSquare = 0;

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
                SquareObstacle = new Caillot(currentX,currentY,orientationPrimary,caillotImages,level);
                break;
            case 363:
                SquareObstacle = new Bacterie(currentX,currentY,orientationPrimary,bacterieImages,level);
                break;
            case 364:
                SquareObstacle = new Chute(currentX,currentY,orientationPrimary,chuteImages,level);
                break;
            case 366:
                isEndSquare = true;
                break;
            case 389:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 6, deviationImages, level);
                break;
            case 390:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 4, deviationImages, level);
                break;
            case 391:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 8, deviationImages, level);
                break;
            case 392:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 2, deviationImages, level);
                break;
            case 393:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 1, deviationImages, level);
                break;
            case 394:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 3, deviationImages, level);
                break;
            case 395:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 7, deviationImages, level);
                break;
            case 396:
                SquareObstacle = new Deviation(currentX,currentY,orientationPrimary, 9, deviationImages, level);
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
            else if(typeid(*SquareObstacle) == typeid(Bacterie))
            {
                addItem(dynamic_cast<Bacterie*>(SquareObstacle));
            }
            else if(typeid(*SquareObstacle) == typeid(Chute))
            {
                addItem(dynamic_cast<Chute*>(SquareObstacle));
            }

        }

        //Il faut maintenant lancer la generation récursive du principal et retourner l'objet actuel MapSquare

            PrimaryNextSquare = generatePath(xFromOrientation(currentX,orientationPrimary),yFromOrientation(currentY,orientationPrimary),level);
            MapSquare *square;
            if(SecondaryNextSquare != 0)
            {
                square = new MapSquare(PrimaryNextSquare,SecondaryNextSquare,currentX,currentY,SquareObstacle);
                qDebug() << "Deviation @" << currentX << "|" <<currentY;

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
    score = (1+unitWon)*(100-unitDead-unitUsed/2);
    emit updateScore(QString::number(score));
}


void Render::unitUse(Unit *unit)
{
    unitCount--;
    unitUsed++;
    listUnit->removeOne(unit);
    //listUnit->removeFirst();
    emit updateUnitCount(QString::number(unitCount));
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
    emit updateUnitCount(QString::number(unitCount));
    /*if(listUnit->size() > 0)
    {
        mainUnit = listUnit->first();
    }*/
    calculateScore();

}

void Render::unitWin(Unit *unit)
{
    unitCount--;
    unitWon++;
    listUnit->removeOne(unit);
    emit updateUnitCount(QString::number(unitCount));
    calculateScore();
}

void Render::switchNext()
{
    if(listUnit->size() > 1)
    {
        mainUnit = listUnit->at(1);
    }
}


void Render::gameTimer()
{
    if(play)
    {
        if(listUnit->size() > 0)
        {
            if(unitWon == 0)
                view->centerOn(mainUnit);
            //advance();
            emit moveUnits();
        }
        else
        {
            if(unitWon > 0)
            {
                emit endGame(QString::number(score),true);
            }
            else
            {
                emit endGame(QString::number(score),false);
            }
            mainTimer->stop();
        }
    }
}

void Render::startGame()
{
    view->centerOn(mainUnit);
    if(startCountDown == 0)
    {

        mainTimer->start(1000/60);//60fps

        startCountDown--;
        view->setStartInfo(startCountDown);
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
        view->setStartInfo(startCountDown);
        startCountDown--;
    }
}

void Render::toggleGame(bool _play)
{
    play = _play;

}





