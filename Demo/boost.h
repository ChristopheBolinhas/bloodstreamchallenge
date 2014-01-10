#ifndef BOOST_H
#define BOOST_H


#include "obstacle.h"
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>
class Level;
class Boost : public Obstacle
{

    Q_OBJECT
public:
    Boost(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
    ~Boost();

    void disable();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
public slots:
    void disableAnim();
private:
    QList<QPixmap*> *images;
    int etat = 0;
    QTimer *timerAnim;
};

#endif // BOOST_H
