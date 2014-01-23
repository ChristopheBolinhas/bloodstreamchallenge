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
    //Fixe la taille de la fenêtre à 960x540
    setFixedSize(960,540);
    parent->setFixedSize(960,540); // Pour la fenetre principale, ou le faire dans MainWindow.cpp

    //On instancie la vue du jeu
    view = new GameView(this);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //Désactivation des scrolls
    view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    //En mode menu
    view->setMode(0, true);

    //Chargement des options
    option = new Option();

    //On charge la liste des niveaux
    listLevels = Level::loadLevels();

    //On lance la traduction
	initTraduction();

    //On instancie notre scène des menus
    menuContainer = new MenuContainer(view, option, listLevels);
    //On instancie la gestion du son
    player = new GameSoundPlayer(option);

    //On connecte le lancement des niveaux au menus
    connect(menuContainer, SIGNAL(startLevelToGUI(Level*)), this, SLOT(loadLevel(Level*)));
    //On connecte le bouton quitter de l'hud
    connect(view,SIGNAL(closeRender()),this,SLOT(closeRender()));

    //On crée le popup de fin de partie et on le cache
    endGameInfos = new EndGameScreen(this);
    endGameInfos->setGeometry(160,90,640,360);
    endGameInfos->hide();
    //Connexion des choix de fin de niveau
    connect(endGameInfos,SIGNAL(homeSignal()),this,SLOT(closeRender()));
    connect(endGameInfos,SIGNAL(retrySignal()),this,SLOT(retryLevel()));
    connect(view,SIGNAL(setSound(bool)),player,SLOT(setMuted(bool)));
    connect(menuContainer,SIGNAL(updateSound(int,bool)),player,SLOT(setSound(int,bool)));
}
void Gui::startLevel(Level *level)
{
    //Lancement d'un niveau et destruction des menus
    view->setFixedSize(960,540);
    view->setSceneRect(0,0,0,0);
    view->setMode(1,true);
    view->setSound(option->isMute());
    player->setMode(GameSoundPlayer::in_game);
    currentLevel = level;

    //Instanciation de render
    render = new Render(view,level, player,this);
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

    //On affiche l'écran de fin de partie en mettant à jour les valeurs
    endGameInfos->setScreen(score,victory);
    //En condition de victoire
    if(victory)
    {
        //On modifie le score si il est meilleur que le précédent
        if(score.toInt() > currentLevel->getScore())
            currentLevel->setScore(score.toInt());
        Level::saveLevels(*listLevels);
        emit updateLocks(currentLevel);
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
    //Fermeture d'une partie
    endGameInfos->hide();
    player->setMuted(option->isMute());
    //On recrée la scène des menus
    menuContainer = new MenuContainer(view, option, listLevels);
    view->centerOn(0,0); // recentre la vue car elle a été modifiée par Render
    connect(menuContainer, SIGNAL(startLevelToGUI(Level*)), this, SLOT(loadLevel(Level*)));
    connect(menuContainer,SIGNAL(updateSound(int,bool)),player,SLOT(setSound(int,bool)));
    //On cache le hud
    view->setMode(0,true);
    player->setMode(GameSoundPlayer::menu);
    delete(render);
}
