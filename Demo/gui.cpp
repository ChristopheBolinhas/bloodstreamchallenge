#include "gui.h"
#include "level.h"
#include "render.h"
#include "gamesoundplayer.h"

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
#include <QTranslator>

Gui::Gui(QWidget *parent) :
    QWidget(parent)
{
    setFixedSize(960,540);
    parent->setFixedSize(960,540); // Pour la fenetre principale, ou le faire dans MainWindow.cpp

    view = new GameView(this);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setMode(0, true);

    option = new Option();
    listLevels = Level::loadLevels();
	initTraduction();
    menuContainer = new MenuContainer(view, option, listLevels);
    player = new GameSoundPlayer(option);
    connect(menuContainer, SIGNAL(startLevelToGUI(Level*)), this, SLOT(loadLevel(Level*)));
    connect(view,SIGNAL(closeRender()),this,SLOT(closeRender()));
    endGameInfos = new EndGameScreen(this);
    endGameInfos->setGeometry(160,90,640,360);
    endGameInfos->hide();
    connect(endGameInfos,SIGNAL(homeSignal()),this,SLOT(closeRender()));
    connect(endGameInfos,SIGNAL(retrySignal()),this,SLOT(retryLevel()));
}
void Gui::startLevel(Level *level)
{
    view->setFixedSize(960,540);
    view->setSceneRect(0,0,0,0);
    view->setMode(1,true);
    player->setMode(GameSoundPlayer::in_game);
    currentLevel = level;
    render = new Render(view,level,this);
    connect(render,SIGNAL(endGame(QString,bool)),this,SLOT(endLevel(QString,bool)));
    destroy(menuContainer);

}

void Gui::initTraduction()
{
    switch(option->getLanguage())
    {
    case Option::english:
        fichierTraduction = ":/translation/ressources/translation/traduction_en.qm";
        break;

    case Option::french:
        fichierTraduction = ":/translation/ressources/translation/traduction_fr.qm";
        break;

    default:
        fichierTraduction = ":/translation/ressources/translation/traduction_en.qm";
        break;
    }
    translator.load(fichierTraduction);
    qApp->installTranslator(&translator);
}

void Gui::loadLevel(Level *lvl)
{
    startLevel(lvl);
}

void Gui::endLevel(QString score, bool victory)
{
    endGameInfos->setScreen(score,victory);
    if(victory)
    {
        currentLevel->setScore(score.toInt());
        Level::saveLevels(*listLevels);
    }
    endGameInfos->show();
}

void Gui::retryLevel()
{
    closeRender();
    startLevel(currentLevel);
}

void Gui::closeRender()
{
    endGameInfos->hide();
    menuContainer = new MenuContainer(view, option, listLevels);
    view->centerOn(0,0); // recentre la vue car elle a été modifiée par Render
    connect(menuContainer, SIGNAL(startLevelToGUI(Level*)), this, SLOT(loadLevel(Level*)));
    view->setMode(0,true);
    player->setMode(GameSoundPlayer::menu);
    delete(render);
}
