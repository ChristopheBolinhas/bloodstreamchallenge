#ifndef RENDER_H
#define RENDER_H

#include <QWidget>
class QGraphicsScene;
class QGraphicsView;
class QGraphicsItemGroup;
class QTimer;
class MapSquare;
class Level;
class Unit;
class Render : public QWidget
{
    Q_OBJECT

public:
    explicit Render(QGraphicsView *_view, Level *level, QWidget *parent = 0);

signals:
    void moveUnits();
public slots:

private slots:
    void updateCenter();


private:
    //QGraphicsItemGroup *units;
    MapSquare* generatePath(int currentX, int currentY, Level *level);
    MapSquare* generatePath(int currentX, int currentY, int* PathTab, int PathTabSize, int* SecondaryPathTab, int SecondaryPathTabSize, int map_width, int map_height);
    Level *renderedLevel;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QList<Unit*> *listUnit;
    Unit *mainUnit;

};

#endif // RENDER_H
