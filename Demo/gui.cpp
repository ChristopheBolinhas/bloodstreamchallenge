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
    view2->setMode(0);
    //view->setSi
    //view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    menuContainer = new MenuContainer(view2);
    connect(menuContainer, SIGNAL(startLevel(Level*)), this, SLOT(loadLevel(Level*)));
    connect(view2,SIGNAL(closeRender()),this,SLOT(closeRender()));
    /*

    //QRect r(0,0,960,540);
    view->setFixedSize(960,540);
    //view->setViewport(this);
    view->show();
    if(!leveltest.isEmpty())
    {
    Level *first = &leveltest.first();
    startLevel(first);
    }
    else
    {
        qDebug() << "Pas de levels dispo";
    }

    */

}
void Gui::startLevel(Level *level)
{
    render = new Render(view2,level,this);
    destroy(menuContainer);

}

//TODO: a modifier selon tes envies. Je voulais pas trop dénaturer ton code
void Gui::loadLevel(Level *lvl)
{
    view2->setFixedSize(960,540);
    view2->setSceneRect(0,0,0,0); // FILS DE PUTE DE QT !!! 4 heures a debug cette merde ! // Reset la taille de la view au minimum à cause des animations du menu
    view2->setMode(1);
    startLevel(lvl);
}

void Gui::closeRender()
{
    menuContainer = new MenuContainer(view2);
    connect(menuContainer, SIGNAL(startLevel(Level*)), this, SLOT(loadLevel(Level*)));
    view2->setMode(0);
    destroy(render);
}
