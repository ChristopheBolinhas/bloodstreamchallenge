#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsObject>
#include <QGraphicsItem>

class Obstacle : public QGraphicsObject
{
    Q_OBJECT
public:
    Obstacle(int _x, int _y, int _orientation);
    bool isEnabled();
    virtual ~Obstacle();

    int getOrientation();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
protected:
    bool enabled;
    int x;
    int y;
    int orientation;
    int width;
    int height;
    int rotation; //0 - 0, 1-45°, 2-90°, 3-135°

private:

};

#endif // OBSTACLE_H
