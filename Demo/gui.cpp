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
    //On récupère la liste des niveaux

    //QList<Level*> leveltest = Level::loadLevels();

    setFixedSize(960,540);
    parent->setFixedSize(960,540); // Pour la fenetre principale, ou le faire dans MainWindow.cpp

    view2 = new GameView(this);
    view2->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view2->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view2->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //view2->setSceneRect(0,0,960,540);
    view2->setMode(0, true);
    //view->setSi
    //view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);



    option = new Option();
	initTraduction();
    menuContainer = new MenuContainer(view2, option);
    player = new GameSoundPlayer(option);
    connect(menuContainer, SIGNAL(startLevelToGUI(Level*)), this, SLOT(loadLevel(Level*)));
    connect(view2,SIGNAL(closeRender()),this,SLOT(closeRender()));
    endGameInfos = new EndGameScreen(this);
    endGameInfos->setGeometry(160,90,640,360);
    endGameInfos->hide();
    connect(endGameInfos,SIGNAL(homeSignal()),this,SLOT(closeRender()));
    connect(endGameInfos,SIGNAL(retrySignal()),this,SLOT(retryLevel()));
}
void Gui::startLevel(Level *level)
{
    view2->setFixedSize(960,540);
    view2->setSceneRect(0,0,0,0);
    view2->setMode(1,true);
    player->setMode(GameSoundPlayer::in_game);
    currentLevel = level;
    render = new Render(view2,level,this);
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
	//on arrete la musique du menu
    //player->stop();
    startLevel(lvl);
}

void Gui::endLevel(QString score, bool victory)
{
    endGameInfos->setScreen(score,victory);
    currentLevel->setScore(score.toInt());
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
    menuContainer = new MenuContainer(view2, option);
    //view->centerOn(menuContainer->);
    connect(menuContainer, SIGNAL(startLevelToGUI(Level*)), this, SLOT(loadLevel(Level*)));
    view2->setMode(0,true);
    player->setMode(GameSoundPlayer::menu);
    //view2->scale((qreal)10/8,(qreal)10/8);
    delete(render);
    //render->destroy();
}
