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
    virtual ~Unit();
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int getAbility() const;
    void setAbility(int value);

    void destroy();
private:
    MapSquare *currentSquare;
    QPropertyAnimation *animation;
    QList<QPixmap*> *pixmapList;
    qreal xmove;
    qreal ymove;
    bool deathMode;
    void calcultateNextMove(int _speed, int _paces);
    int ability;
    int speed;
    int paces;
    int deathAnimationState;
    QTimer *deathTimer;
    bool isAlive;
    bool won;
    int paceMax;
    void die();
    void use();
    void finish();
    void initUnit();

signals:
    void useUnit(Unit *unit);
    void killUnit(Unit *unit);
    void switchNext(int ability);
    void winUnit(Unit *unit);
public slots:
    void moveUnit();
private slots:
    void animateDeath();


};

#endif // UNIT_H
