#ifndef UNIT_H
#define UNIT_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include "mapsquare.h"

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
    int getAbility() const;
    void setAbility(int value);

private:
    MapSquare *currentSquare;
    QPropertyAnimation *animation;
    QList<QPixmap*> *pixmapList;
    qreal xmove;
    qreal ymove;
    void calcultateNextMove();
    void unlockObstacle();
    int ability;
    bool isAlive = true;
    void die();
signals:

public slots:
    void moveUnit();


};

#endif // UNIT_H
