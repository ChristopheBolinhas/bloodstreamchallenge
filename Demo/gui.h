#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include "level.h"
#include "menucontainer.h"
#include "gameview.h"
#include "gamesoundplayer.h"

class Level;
class QGraphicsScene;
class QGraphicsView;
class Render;
class Option;
class EndGameScreen;
class Gui : public QWidget
{
    Q_OBJECT

public:
    explicit Gui(QWidget *parent = 0);

private:
    QList<Level> *levels;
    void startLevel(Level *level);
    Option *option;
    GameView *view;
    MenuContainer *menuContainer;
    Render *render;
    EndGameScreen *endGameInfos;
    Level *currentLevel;
    void initTraduction();
    QString fichierTraduction;
    QTranslator translator;
    GameSoundPlayer *player;
    QList<Level*> *listLevels;

signals:
    void updateLocks(Level *level);
public slots:
    void loadLevel(Level* lvl);
    void closeRender();
    void retryLevel();
    void endLevel(QString score, bool victory);
};

#endif // GUI_H
