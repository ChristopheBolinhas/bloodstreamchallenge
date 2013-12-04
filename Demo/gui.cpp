#include "gui.h"
#include "level.h"
#include "render.h"
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

    QList<Level> leveltest = Level::loadLevels();
    setFixedSize(960,540);

    Level *first = &leveltest.first();
    view = new QGraphicsView(this);
    view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

    //view->setSi
    //view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    startLevel(first);
    //QRect r(0,0,960,540);
    view->setFixedSize(960,540);
    //view->setViewport(this);
    view->show();


}
void Gui::startLevel(Level *level)
{
    Render *render = new Render(view,level,this);
}
