#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include "level.h"
#include "menucontainer.h"
#include "gameview.h"

class Level;
class QGraphicsScene;
class QGraphicsView;
class Render;
class Option;
class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = 0);
private:
    QList<Level> *levels;
    void startLevel(Level *level);
    Option *option;
    QGraphicsView *view;
    GameView *view2;
    MenuContainer *menuContainer;
    Render *render;
signals:

public slots:
    void loadLevel(Level* lvl);
    void closeRender();

};

#endif // GUI_H
