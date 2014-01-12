#ifndef MENUSLIDERCIRCLE_H
#define MENUSLIDERCIRCLE_H

#include <QGraphicsItem>

class MenuSliderCircle : public QGraphicsItem
{
public:
    MenuSliderCircle(QPoint position, int size, int minimum, int maximum, int lenght, QGraphicsScene *scene);
    virtual ~MenuSliderCircle();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getValue() const;
    void setValue(int value);

    int getMinimum() const;
    void setMinimum(int value);

    int getMaximum() const;
    void setMaximum(int value);

    QPoint getPosition() const;
    void setPosition(const QPoint &value);

    int getSize() const;
    void setSize(int value);

    int getLenght() const;
    void setLenght(int value);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF rect;
    int minimum;
    int maximum;
    int size;
    int lenght;
    QPoint position;
    QGraphicsScene *scene;
};

#endif // MENUSLIDERCIRCLE_H
