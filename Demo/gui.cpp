#include "gui.h"
#include "level.h"
#include "render.h"

//#include "menucontainer.h"
#include <QDebug>

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRect>
#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include "option.h"
#include "endgamescreen.h"

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    //On récupère la liste des niveaux

    //QList<Level*> leveltest = Level::loadLevels();

    setFixedSize(960,540);
    parent->setFixedSize(960,540); // Pour la fenetre principale, ou le faire dans MainWindow.cpp

    //view2 = new GameView(this);
    view2 = new GameView(this);
    view2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view2->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view2->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //view2->setSceneRect(0,0,960,540);
    view2->setMode(0);
    //view->setSi
    //view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);




    option = new Option();
    menuContainer = new MenuContainer(view2, option);
    connect(menuContainer, SIGNAL(startLevel(Level*)), this, SLOT(loadLevel(Level*)));
    connect(view2,SIGNAL(closeRender()),this,SLOT(closeRender()));
    endGameInfos = new EndGameScreen(this);
    endGameInfos->setGeometry(160,90,640,360);
    endGameInfos->hide();
    connect(endGameInfos,SIGNAL(homeSignal()),this,SLOT(closeRender()));
    connect(endGameInfos,SIGNAL(retrySignal()),this,SLOT(retryLevel()));


}
void Gui::startLevel(Level *level)
{
    render = new Render(view2,level,this);
    connect(render,SIGNAL(endGame(QString,bool)),this,SLOT(endLevel(QString,bool)));
    destroy(menuContainer);

}

//TODO: a modifier selon tes envies. Je voulais pas trop dénaturer ton code
void Gui::loadLevel(Level *lvl)
{
    view2->setFixedSize(960,540);
    view2->setSceneRect(0,0,0,0);
    view2->setMode(1);
    currentLevel = lvl;
    startLevel(lvl);
}

void Gui::endLevel(QString score, bool victory)
{
    endGameInfos->setScreen(score,victory);
    currentLevel->setScore(score.toInt());//SES ICI LA SCORE
    endGameInfos->show();

}

void Gui::retryLevel()
{
    closeRender();
    loadLevel(currentLevel);

}


void Gui::closeRender()
{
    endGameInfos->hide();
    menuContainer = new MenuContainer(view2, option);
    //view->centerOn(menuContainer->);
    connect(menuContainer, SIGNAL(startLevel(Level*)), this, SLOT(loadLevel(Level*)));
    view2->setMode(0);
    //view2->scale((qreal)10/8,(qreal)10/8);
    destroy(render);
}
