#ifndef DEVIATION_H
#define DEVIATION_H
#include "obstacle.h"
#include "mapsquare.h"
#include "level.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>

class Deviation : public Obstacle
{
    Q_OBJECT
public:
    Deviation(int _x, int _y, int _orientationPrimary, int _orientationSecondary, QList<QPixmap *> *_images, Level *level);
    void switchPath(MapSquare *currentSquare);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    ~Deviation();
private slots:
    void animation();
private:
    int secondaryOrientation;
    int anim;
    QTimer *deviationTimer;
    int angleFromOrientation(int orientation);
};




#endif // DEVIATION_H
