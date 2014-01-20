#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsObject>
#include <QGraphicsItem>

class Level;
class Obstacle : public QGraphicsObject
{
    Q_OBJECT
public:
    Obstacle(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);
    bool isEnabled();
    ~Obstacle();

    int getOrientation();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void disable();
public slots:
    void disableAnim();


protected:
    bool enabled;
    int x;
    int y;
    int orientation;
    int width;
    int height;
    int rotation;
    QList<QPixmap*> *images;
    int etat = 0;
    QTimer *timerAnim;

private:

};

#endif // OBSTACLE_H
