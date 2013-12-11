#ifndef UNIT_H
#define UNIT_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include "mapsquare.h"
#include "enumobstacle.h"
class QPropertyAnimation;

class Unit : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Unit(QList<QPixmap*> *_pixmapList, MapSquare *path,QGraphicsItem *parent = 0);
    void advance (int phase);
    virtual ~Unit();
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    MapSquare *currentSquare;
    QPropertyAnimation *animation;
    QList<QPixmap*> *pixmapList;
    qreal xmove;
    qreal ymove;
    void calcultateNextMove();
    EnumObstacle::TypeObstacle capaciteUnit;

    void unlockObstacle();
signals:

public slots:
    void moveUnit();


};

#endif // UNIT_H
